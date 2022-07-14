
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <termios.h>                   
#include <fcntl.h>                    
#include <time.h>
#include <math.h>
#include <errno.h> 
#include <unistd.h> 

#define _USE_MATH_DEFINES
typedef unsigned char BYTE;

union
{
    short data ;
    char  bytedata[2];
} m_crc;
 
static int uart_fd;


int crc_sumdata = 0;

void write_serial(unsigned char *buf, int len)
{
	write(uart_fd, &buf[0], len);
}

int init_serial_port(void)
{
  int serial_port = open("/dev/ttyUSB0", O_RDWR);
  struct termios tty;
  if(tcgetattr(serial_port, &tty) != 0) {
      printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
      return 1;
  }
  tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
  tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
  tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
  tty.c_cflag |= CS8; // 8 bits per byte (most common)
  tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
  tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO; // Disable echo
  tty.c_lflag &= ~ECHOE; // Disable erasure
  tty.c_lflag &= ~ECHONL; // Disable new-line echo
  tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
  tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
  tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
  tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
  tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed
  // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
  // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON LINUX)
  tty.c_cc[VTIME] = 100;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
  tty.c_cc[VMIN] = 0;
  // Set in/out baud rate to be 9600
  cfsetispeed(&tty, B115200);
  cfsetospeed(&tty, B115200);
  // Save tty settings, also checking for error
  if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
      printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
      return -1;
  }
  else
  {
      return serial_port;
  }
}

unsigned char buf_array[20]={0,};
unsigned char buf_copy[10]={0,};
unsigned char crc_copy[2]={0,};

int crc_checksum(void)
{
	for(int i = 1; i < 6; i++)	crc_sumdata += buf_copy[i];
	return crc_sumdata;
}

void *readserial_thread(void *pt)
{
    int num = -1;
    unsigned char buffer;
    unsigned char pre_buffer;

    while(1)
    {
     	while( (num = read(uart_fd, &buffer, 1)   ) > 0 )	
        {
		int buf_Count = 0;
		if(buffer == '#' ) 	buf_array[buf_Count] = buffer ; 
		else if( buffer == 'I' && pre_buffer =='#')
		{
			buf_array[0] = '#' ;
			buf_Count = 1 ;
			buf_array[buf_Count] = buffer ;                  
		}	
		else if(buf_Count = 2 || buf_Count = 3 || buf_Count = 4 || buf_Count = 5)
			buf_array[buf_Count] = buffer ;
		else if(buf_Count = 6 || buf_Count = 7)
			buf_array[buf_Count] = buffer ;
		else if( buffer == '*' ) 
		{
			buf_array[buf_Count] = buffer ;
			if( buf_array[0] == '#'  && buf_array[1] == 'I' )     
			{
				memcpy(buf_copy, buf_array, buf_Count) ;
				printf("Received Data:%x %x %x %x %x %x %x %x %x %x\t", 
				       buf_copy[0],buf_copy[1],buf_copy[2],buf_copy[3],
				       buf_copy[4],buf_copy[5],buf_copy[6],buf_copy[7],
				       buf_copy[8],buf_copy[9]);
				m_crc.data = crc_checksum();
				//printf("%x	%x \n",m_crc.bytedata[1],m_crc.bytedata[0]);
				if(m_crc.bytedata[1] == copy_readbuf[6] && m_crc.bytedata[0] == copy_readbuf[7])
					printf("NORMAL \n");
				else
					printf("ERROR \n");
			}
		}                  
		else	buf_array[buf_Count] = buffer ;
		buf_Count++ ;
		pre_buffer =  buffer;
	}
    }
}


int main(void)
{
  uart_fd = init_serial_port();
  pthread_t id_1;
  int ret1=pthread_create(&id_1,NULL,readserial_thread,NULL);
  close(uart_fd);

  return 0;
}
