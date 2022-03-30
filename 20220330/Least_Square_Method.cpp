#include <stdio.h>
#include <math.h>
#define DATA 4

double x[DATA],y[DATA];
double X_avg, Y_avg, X_sum, Y_sum;
double a_denominator, a_numerator, a, b;
int i;

void calculate(void);

int main(void)
{
	printf("x값을 입력하시오: ");
	for(i=0;i<DATA;i++)	scanf("%lf",&x[i]);
	printf("y값을 입력하시오: ");
	for(i=0;i<DATA;i++)	scanf("%lf",&y[i]);
	calculate();
	printf("최소차승법으로 구한 직선방정식 은 y = %.1lfx + %.1lf 입니다.\n",a,b);
}
void calculate(void)
{
	for(i=0;i<DATA;i++)
	{
		X_sum += x[i];
		Y_sum += y[i];
	}
	X_avg = X_sum / DATA;
	Y_avg = Y_sum / DATA;
	
	for(i=0;i<DATA;i++)
	{
		a_numerator += ((x[i]-X_avg)*(y[i]-Y_avg));
		a_denominator += pow(x[i]-X_avg,2);
	}
	
	a = a_numerator / a_denominator;
	b = Y_avg - (X_avg * a);
}
