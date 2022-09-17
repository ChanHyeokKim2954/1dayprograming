#include <stdio.h>

double array[] = { 0.0, };

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
double Ave(int size)
{
	double sum = 0.0;
	for (int i = 0; i < size ; i++)	sum += array[i];
	return sum / (double)size;
}

double LowPassFilter(double average_old, double data, int size)
{
	double average = 0.0;
	double alpha = 0.0;

	alpha = ((double)size - 1) / (double)size;
	printf("alpha : %.2lf \n\n", alpha);

	average = (alpha * average_old) + ((1 - alpha) * data);

	return average;
}

void Show_Data(double calculation, int size, double average_old)
{
	printf("DATA_Array = ");
	for (int i = 0; i < size; i++)	printf("%.2lf ", array[i]);
	printf("\n");
	printf("Average : %.2lf \n\n", calculation);
	printf("Average_old : %.2lf \n\n", average_old);
}

int main(void)
{
	int count = 0;
	double average_old = 0.0;
	double calculation = 0.0;

	int size = Input_Size();
	while (1)
	{
		double data = Input_Data();
		array[count] = data;
		if (count < size)
		{
			calculation = Ave(size);
			if(count == size - 1)	average_old = calculation;
		}
		else {
			
			average_old = calculation;
			for (int i = 0; i < size; i++)	array[i] = array[i + 1];
			calculation = LowPassFilter(average_old, data, size);
			count = size - 1;
		}
		count++;
		Show_Data(calculation, size, average_old);
	}

	return 0;
}