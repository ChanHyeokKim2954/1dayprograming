#include <stdio.h>

double array[] = {0.0, };

int Input_Size(void)
{
	int size = 0;
	printf("INPUT DATA SIZE : ");
	scanf_s("%d", &size);
	printf("=================================\n");
	return size;
}
double Input_Data(void)
{
	double data = 0.0;
	printf("INPUT DATA : ");
	scanf_s("%lf", &data);

	return data;
}
double MovingAverage(int size)
{
	double sum = 0.0;
	for (int i = 0; i < size ; i++)	sum += array[i];
	return sum / (double)size;
}

void Show_Data(double calculation, int size)
{
	printf("DATA_Array = ");
	for (int i = 0; i < size; i++)	printf("%.2lf ", array[i]);
	printf("\n");
	printf("Average : %.2lf \n\n", calculation);
}

int main(void)
{
	int count = 0;
	double average_old = 0.0;
	double calculation = 0.0;
	double data = 0.0;
	int size = Input_Size();
	while (1)
	{
		data = Input_Data();
		array[count] = data;

		if (count < size) {
			calculation = MovingAverage(size);
		}
		else {
			for (int i = 0; i < size; i++)	array[i] = array[i + 1];
			calculation = MovingAverage(size);
			count = size - 1;
		}

		Show_Data(calculation, size);
		count++;
	}

	return 0;
}