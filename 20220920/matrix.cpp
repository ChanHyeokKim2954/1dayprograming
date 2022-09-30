#include <stdio.h>

#define ROW 3
#define COLUMN 3
#define SIZE 3

int x[ROW][COLUMN] = { {0,},{0,} };
int y[ROW][COLUMN] = { {0,},{0,} };
int z[ROW][COLUMN] = { {0,},{0,} };

int mode = 0;

void input_X(void)
{
	printf("INPUT A MATRiX : ");
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			scanf_s("%d", &x[i][j]);
		}
	}
}
void input_Y(void)
{
	printf("INPUT A MATRiX : ");
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			scanf_s("%d", &y[i][j]);
		}
	}
}
void input_mode(void)
{
	printf("choose mode (1.matrix \t 2.inverse matrix) : ");
	scanf_s("%d", &mode);
}
void MULTIPLE_MATRIX(int a[][3], int b[][3], int c[][3])
{
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			int temp = 0;
			for (int k = 0; k < SIZE; k++)
			{
				temp += (x[i][k] * y[k][j]);
			}
			z[i][j] = temp;
		}
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COLUMN; j++) {
			printf("%d\t", z[i][j]);
		}
		printf("\n");
	}

}
int cal2x2matrix(int a,int b,int c,int d)
{
	return (a * b) - (c * d);
}
int cal3x3matrix(int c[][3])
{
	return c[1][1] * cal2x2matrix(c[2][2], c[3][3], c[2][3], c[3][2]) - c[1][2] * cal2x2matrix(c[2][1], c[3][3], c[2][3], c[3][1]) + c[1][3] * cal2x2matrix(c[2][1], c[3][2], c[2][2], c[3][1]);
}

double INVERS_MATRIX(int a[][3], int c[][3])
{
	c[1][1] = cal2x2matrix(a[2][2], a[3][3], a[2][3], a[3][2]);
	c[1][2] = cal2x2matrix(a[1][3], a[3][2], a[1][2], a[3][3]);
	c[1][3] = cal2x2matrix(a[1][2], a[2][3], a[1][3], a[2][2]);

	c[2][1] = cal2x2matrix(a[2][3], a[3][1], a[2][1], a[3][3]);
	c[2][2] = cal2x2matrix(a[1][1], a[3][3], a[1][3], a[3][1]);
	c[2][3] = cal2x2matrix(a[1][3], a[2][1], a[1][1], a[2][3]);

	c[3][1] = cal2x2matrix(a[2][1], a[3][2], a[2][2], a[3][1]);
	c[3][2] = cal2x2matrix(a[1][2], a[3][1], a[1][1], a[3][2]);
	c[3][3] = cal2x2matrix(a[1][1], a[2][2], a[1][2], a[2][1]);


	int abs = cal3x3matrix(a);
	if (abs < 0)	abs = -cal3x3matrix(a);

	return cal3x3matrix(c) / abs;
}

int main(void)
{
	input_X();
	input_Y();
	input_mode();
	switch (mode) {
		case 1:
			MULTIPLE_MATRIX(x, y, z);
			printf("Multiple Matrix : %d \n",cal3x3matrix(z));
			break;
		case 2:
			printf("Invers Matrix : %lf \n",INVERS_MATRIX(x, z));
			break;
		default:
			printf("chosing mode again plz");
			break;
	}

}