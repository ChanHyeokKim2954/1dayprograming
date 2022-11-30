#include <stdio.h>

double BPS = 0.0, byte = 0.0, One_Byte_Time = 0.0, Byte_Time = 0.0;
int main(void)
{
	printf("Input BPS(bit per second) : ");
	scanf_s("%lf", &BPS);
	printf("Input Byte : ");
	scanf_s("%lf", &byte);
	printf("\n");

	One_Byte_Time = (1 / BPS) * 1000;
	Byte_Time = byte * One_Byte_Time;

	printf("Communication Time of 1 byte (ms) : %.3lf \n", One_Byte_Time);
	printf("Communication Time of Input Byte (ms) : %.3lf \n", Byte_Time);

	return 0;
}