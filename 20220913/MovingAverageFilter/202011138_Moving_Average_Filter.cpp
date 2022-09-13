#include <stdio.h>
#define DATA_SIZE 5

double array[DATA_SIZE] = {0.0,};

int Input_Data(void)
{
	double data = 0;

	printf("DATA를 입력하시오 : ");
	scanf_s("%lf", &data);

	return data;
}

double MovingAverageFilter(double average_old, double data)
{
	double average = 0.0;

	average = average_old + (data - array[0]) / DATA_SIZE;

	return average;
}

void Show_Data(double calculation)
{
	printf("DATA_Array = ");
	for (int i = 0; i < DATA_SIZE; i++)	printf("%.2lf ", array[i]);
	printf("\n");
	printf("Average : %.2lf \n\n", calculation);
}

int main(void)
{
	int count = 1;
	double average_old = 0.0;
	double calculation = 0.0;
	while(1)
	{
		double data = Input_Data();
		array[count] = data;
		average_old = calculation;
		//printf("Average_old : %.2lf \n\n", average_old);
		calculation = MovingAverageFilter(average_old,data);
		Show_Data(calculation);
		count++;

		if (count >= DATA_SIZE)
		{
			count = 4;
			for (int i = 0; i < DATA_SIZE - 1; i++)	array[i] = array[i + 1];
		}
	}

	return 0;
}