#include <stdio.h>

double M, B, K;
double V0, Y0, t0, t1, h;

double v[] = { 0.0, };
double y[] = { 0.0, };

struct RungeKuttaValue {
	double dy;
	double dv;
};

// y''+(B/M)*y'+(K/M)*y = 0 

void InputData(void)
{
	printf("=================================\n");
	printf("M = ");		// M = Mass
	scanf_s("%lf", &M);

	printf("B = ");		// B = Damper const
	scanf_s("%lf", &B);

	printf("K = ");		// K = Spring const
	scanf_s("%lf", &K);

	printf("V0 = ");	// V0 = First Velocity Value
	scanf_s("%lf", &V0);
	v[0] = V0;

	printf("Y0 = ");	// X0 = First Y_Function Value
	scanf_s("%lf", &Y0);
	y[0] = Y0;

	printf("t0 = ");	// t0 = t(0)
	scanf_s("%lf", &t0);

	printf("t1 = ");	// t1 = t(1)
	scanf_s("%lf", &t1);

	printf("h = ");		
	scanf_s("%lf", &h);
	printf("=================================\n");
}

double Y2Prime_Function(double B, double M, double K, double Yn, double Vn)
{
	return -(B * Vn / M) - (K * Yn / M);
}
double dy_Function(double h, double Ky1, double Ky2, double Ky3, double Ky4)
{
	return h * (Ky1 + (2 * Ky2) + (2 * Ky3) + Ky4) / 6;
}
double dv_Function(double h, double Kv1, double Kv2, double Kv3, double Kv4)
{
	return h * (Kv1 + (2 * Kv2) + (2 * Kv3) + Kv4) / 6;
}

RungeKuttaValue RungeKutta_Function(int num, double B, double M, double K)
{
	struct RungeKuttaValue RK;

	double Ky1 = 0, Ky2 = 0, Ky3 = 0, Ky4 = 0;
	double Kv1 = 0, Kv2 = 0, Kv3 = 0, Kv4 = 0;

	double Yn = y[num];
	double Vn = v[num];


	Ky1 = v[num];
	Kv1 = Y2Prime_Function(B, M, K, Yn, Vn);

	Ky2 = v[num] + (h/2) * Kv1;
	Kv2 = Y2Prime_Function(B, M, K, Yn + (h * Ky1 / 2), Vn + (h * Kv1 / 2));

	Ky3 = v[num] + (h/2) * Kv2;
	Kv3 = Y2Prime_Function(B, M, K, Yn + (h * Ky2 / 2), Vn + (h * Kv2 / 2));

	Ky4 = v[num] + h * Kv3;
	Kv4 = Y2Prime_Function(B, M, K, Yn + (h * Ky3), Vn + (h * Kv3));

	RK.dy = dy_Function(h, Ky1, Ky2, Ky3, Ky4);
	RK.dv = dv_Function(h, Kv1, Kv2, Kv3, Kv4);

	//printf("%.5lf %.5lf %.5lf %.5lf %.5lf %.5lf \n", Ky1, Kv1, Ky2, Kv2, RK.dy, RK.dv);
	return RK;
}


int main(void)
{
	int SIZE = 0;
	InputData();
	SIZE = (t1 - t0) / h;
	for (int i = 0; i < SIZE; i++)
	{
		printf("Calculation Value Y = %.5lf \t", y[i]);
		printf("Calculation Value V = %.5lf \n", v[i]);
		RungeKuttaValue RKF = RungeKutta_Function(i, B, M, K);
		v[i + 1] = v[i] + RKF.dv;
		y[i + 1] = y[i] + RKF.dy;
	}

	return 0;
}