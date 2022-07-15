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

union
{
    short send_data ;
    char  send_bytedata[2];
} m_crc;
 
static int uart_fd;
void serial(buffer,buf_Count);
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
unsigned char buffer;
unsigned char pre_buffer;

int buf_Count = 0;
int num = -1;

int crc_sum(void)
{
	int crc_sumdata = 0;
	for(int i = 1; i < 6; i++)	crc_sumdata += buf_copy[i];
	return crc_sumdata;
}

void *readserial_thread(void *pt)
{
    while(1)	while((num = read(uart_fd, &buffer, 1)) > 0 )	serial(buffer);
}
void serial(buffer)
{
	if(buffer == '#' ) 
	{
		buf_array[buf_Count] = buffer ; 
		buf_Count++ ;  
	}
	else if( buffer == 'I' && pre_buffer =='#')
	{
		buf_array[0] = '#' ;
		buf_Count = 1 ;
		buf_array[buf_Count] = buffer ;
		buf_Count++ ;                  
	}	
	else if(buf_Count >1 && buf_Count < 8)
	{
		buf_array[buf_Count] = buffer ;
		buf_Count++ ;
	}
	else if( buffer == '*' ) 
	{
		buf_array[buf_Count] = buffer ;
		buf_Count++ ;
		if( buf_array[0] == '#'  && buf_array[1] == 'I' )     
		{
			memcpy(buf_copy, buf_array, buf_Count) ;
			for(int i = 0 ; i < 10 ; i++)	printf("%x ",buf_copy[i]);
			m_crc.send_data = crc_sum();
			if(m_crc.send_bytedata[1] == buf_copy[6] && m_crc.send_bytedata[0] == buf_copy[7])
				printf("NORMAL \n");
			else
				printf("ERROR \n");
		}
		buf_Count = 0;
	}                  
	else
	{
		buf_array[buf_Count] = buffer ;
		buf_Count++ ;
	}
	pre_buffer =  buffer;
}
int main(void)
{
  uart_fd = init_serial_port();
  pthread_t id_1;
  int ret1=pthread_create(&id_1,NULL,readserial_thread,NULL);
  while(1)	sleep(1);
  close(uart_fd);

  return 0;
}

