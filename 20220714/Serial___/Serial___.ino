
#define MAX_RECEIVE_DATA 20
#define SIZE_PACKET  9

union
{
    short data ;
    char  bytedata[2];    
} d_int, d_crc;

union
{
    float data ;
    char  bytedata[4];    
} d_float;

char r_buffer[MAX_RECEIVE_DATA] ={0,};
char s_buffer[SIZE_PACKET+1] ={0,};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  
}

int crc_check(void)
{
  int crc_data = 0;
  for(int i=1;i<6;i++)
  {
     s_buffer[i];
     crc_data += s_buffer[i];
  }
  return crc_data;
}
void send_int_data(int input)
{
   d_int.data = input;
   s_buffer[0] = '#';
   s_buffer[1] = 'I';
   s_buffer[2] = d_int.bytedata[1];
   s_buffer[3] = d_int.bytedata[0];
   s_buffer[4] = 0;
   s_buffer[5] = 0;   
   s_buffer[8] = '*';
   
   d_crc.data= crc_check();
   //Serial.println(d_crc.data);
   s_buffer[6] = d_crc.bytedata[1];
   s_buffer[7] = d_crc.bytedata[0];  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(s_buffer[i]);
     s_buffer[i] = 0; 
   }
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data2(int input)
{
   d_int.data = input;
   Serial.print("#I");
   s_buffer[0] = '#';
   s_buffer[1] = 'I';
   s_buffer[2] = d_int.bytedata[1];
   s_buffer[3] = d_int.bytedata[0];
   s_buffer[4] = 0;
   s_buffer[5] = 0;   
   s_buffer[8] = '*';
   
   d_crc.data= crc_check();
   s_buffer[6] = d_crc.bytedata[1];
   s_buffer[7] = d_crc.bytedata[0];  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(s_buffer[i]);
     s_buffer[i] = 0; 
   }
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data3(int input)
{
   d_int.data = input;
   Serial.print("#I");
   s_buffer[0] = '#';
   s_buffer[1] = 'I';
   s_buffer[2] = d_int.bytedata[1];
   s_buffer[3] = d_int.bytedata[0];
   s_buffer[4] = 0;
   s_buffer[5] = 0;   
   s_buffer[8] = '*';
   
   s_buffer[6] = 0x00;
   s_buffer[7] = 0x4e;  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(s_buffer[i]);
     s_buffer[i] = 0; 
   }
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data4(int input)
{
   d_int.data = input;
   Serial.print("#I");
   s_buffer[0] = '#';
   s_buffer[1] = 'I';
   s_buffer[2] = d_int.bytedata[1];
   s_buffer[3] = d_int.bytedata[0];
   s_buffer[4] = 0;
   s_buffer[5] = 0;   
   s_buffer[8] = '*';
   
   d_crc.data= crc_check();
   s_buffer[6] = d_crc.bytedata[1];
   s_buffer[7] = d_crc.bytedata[0];  
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(s_buffer[i]);
     s_buffer[i] = 0; 
   }
   Serial.print("*");
   Serial.println();  // 보기쉽게 줄바꿈
}

void send_int_data5(int input)
{
   d_int.data = input;
   Serial.print("#***");
   s_buffer[0] = '#';
   s_buffer[1] = 'I';
   s_buffer[2] = d_int.bytedata[1];
   s_buffer[3] = d_int.bytedata[0];
   s_buffer[4] = 0;
   s_buffer[5] = 0;   
   s_buffer[8] = '*';
   
   d_crc.data= crc_check();
   s_buffer[6] = d_crc.bytedata[1];
   s_buffer[7] = d_crc.bytedata[0];  
   s_buffer[7] = 0x4d;
   for(int i=0;i<SIZE_PACKET;i++)
   {
     Serial.print(s_buffer[i]);
     s_buffer[i] = 0; 
   }
   Serial.print("*");
   Serial.println();  // 보기쉽게 줄바꿈
}

int data = 0;

void loop() {
  // put your main code here, to run repeatedly:

  send_int_data(2);
  delay(1000);

  send_int_data2(2);
  delay(1000);

  send_int_data3(2);
  delay(1000);

  send_int_data4(5);
  delay(1000);

  send_int_data5(5);
  delay(1000);

}
