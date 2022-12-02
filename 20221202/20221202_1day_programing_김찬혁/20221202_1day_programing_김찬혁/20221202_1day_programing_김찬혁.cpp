#include <stdio.h>
#define SIZE 12

int BPS_num = 0;
double byte = 0.0, One_Byte_Time = 0.0, Byte_Time = 0.0;
double BPS[SIZE] = {1200,2400,4800,9600,14400,19200,38400,57600,115200,230400,460800,921600};
int main(void)
{
	printf("======================SELECT=BPS======================\n");
	printf("(1) 1200   (2)  2400   (3)  4800   (4)  9600 \n");
	printf("(5) 14400  (6)  19200  (7)  38400  (8)  57600 \n");
	printf("(9) 115200 (10) 230400 (11) 460800 (12) 921600 \n");
	printf("======================================================\n");
	printf("Select BPS(bit per second) : ");
	scanf_s("%d", &BPS_num);
	printf("BPS is %.0lf \n", BPS[BPS_num - 1]);
	printf("======================================================\n");
	printf("Input Byte : ");
	scanf_s("%lf", &byte);
	printf("\n");

	One_Byte_Time = (1 / BPS[BPS_num-1]) * 1000;
	Byte_Time = byte * One_Byte_Time;

	printf("Communication Time of 1 byte (ms) : %.3lf msec \n", One_Byte_Time);
	printf("Communication Time of Input Byte (ms) : %.3lf msec \n", Byte_Time);

	return 0;
}