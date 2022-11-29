#include <stdio.h>

#define MAX_RPM	3000
double RPM = 0.0,RPM_DATA = 0.0, PULSE = 0.0, HZ = 0.0, PERIOD = 0.0;

int main(void)
{
	printf("Input RPM Data : ");
	scanf_s("%lf", &RPM);
	printf("Input PULSE Data : ");
	scanf_s("%lf", &PULSE);
	printf("\n");

	RPM_DATA = (RPM > 3000) ? 3000 : RPM;
	printf("RPM_DATA : %.2lf \n", RPM_DATA);

	HZ = RPM_DATA / 60;
	PERIOD = (1 / (HZ * PULSE)) * 1000;

	printf("1pulse¿« Period(ms) : %.2lf \n", PERIOD);

	return 0;
}