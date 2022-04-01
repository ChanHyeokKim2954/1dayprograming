#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

typedef float TYPE;

class Vector
{
	public:
	TYPE x;
	TYPE y;
	TYPE z;
	
	private:
	TYPE pad;
};

class Matrix
{
	public:
	TYPE data[9]; 
	
	public:
	Matrix(){}
	Matrix(Vector v)
			 {
				 data[0] = v.x; data[1] = v.y; data[2] = v.z;
				 data[3] = v.y; data[4] = -0.01; data[5] = -0.01;
				 data[6] = v.z; data[7] = -0.01; data[8] = -0.01;
			 }
};

Vector Basis_V;
Vector Av, Bv;
Vector Result_VP, Result_VM;

void random_value(void);
Vector plus(Vector Av,Vector Bv);
Vector minus(Vector Av,Vector Bv);
TYPE magnitude(Vector Av);
TYPE inner_product(Matrix ma,Matrix mb);
TYPE cross_product(Vector Basis_V,Vector Av,Vector Bv);

int main(void)
{
	srand(time(NULL));
	random_value();
	
	printf("Basis-Vector = x[%.2lf], y[%.2lf], z[%.2lf]\n\n",Basis_V.x,Basis_V.y,Basis_V.z);
	printf("A-Vector = x[%.2lf], y[%.2lf], z[%.2lf]\n",Av.x,Av.y,Av.z);
	printf("B-Vector = x[%.2lf], y[%.2lf], z[%.2lf]\n\n",Bv.x,Bv.y,Bv.z);
	
	Result_VP = plus(Av, Bv);
	Result_VM = minus(Av, Bv);
	
	printf("PLUS = x[%.2lf], y[%.2lf], z[%.2lf]\n",Result_VP.x,Result_VP.y,Result_VP.z);
	printf("MINUS = x[%.2lf], y[%.2lf], z[%.2lf]\n\n",Result_VM.x,Result_VM.y,Result_VM.z);
	
	printf("MAGNITUDE = A[%.2lf]	B[%.2lf]\n",magnitude(Av),magnitude(Bv));
	Matrix ma(Av);
	Matrix mb(Bv);
	printf("INNER_PRODUCT = [%.2lf] \n",inner_product(ma,mb));
	printf("CROSS_PRODUCT = [%.2lf] \n",cross_product(Basis_V,Av,Bv));
}

void random_value(void)
{	
	Basis_V.x = rand()%20 + 1;
	Basis_V.y = rand()%20 + 1;
	Basis_V.z = rand()%20 + 1;
	
	Av.x = rand()%20 +1;
	Av.y = rand()%20 +1;
	Av.z = rand()%20 +1;
	
	Bv.x = rand()%20 +1;
	Bv.y = rand()%20 +1;
	Bv.z = rand()%20 +1;
}

Vector plus(Vector Av,Vector Bv)
{
	Vector p;
	p.x = Av.x + Bv.x;
	p.y = Av.y + Bv.y;
	p.z = Av.z + Bv.z;
	return p;
}
Vector minus(Vector Av,Vector Bv)
{
	Vector m;
	m.x = Av.x - Bv.x;
	m.y = Av.y - Bv.y;
	m.z = Av.z - Bv.z;
	return m;
}
TYPE magnitude(Vector Av)
{
	return sqrt(pow(Av.x,2)+pow(Av.y,2)+pow(Av.z,2));
}
TYPE inner_product(Matrix ma,Matrix mb)
{
	return (ma.data[0]*mb.data[0]) + (ma.data[1]*mb.data[3]) + (ma.data[2]*mb.data[6]);
}
TYPE cross_product(Vector Basis_V,Vector Av,Vector Bv)
{
	Matrix Cross_M;
	Cross_M.data[0] = Basis_V.x;
	Cross_M.data[1] = Basis_V.y;
	Cross_M.data[2] = Basis_V.z;
	Cross_M.data[3] = Av.x;
	Cross_M.data[4] = Av.y;
	Cross_M.data[5] = Av.z;
	Cross_M.data[6] = Bv.x;
	Cross_M.data[7] = Bv.y;
	Cross_M.data[8] = Bv.z;
	
	//[Bax,Bay,Baz]
	//[Avx,Avy,Avz]
	//[Bvx,Bvy,Bvz]
	
	return Cross_M.data[0]*(Cross_M.data[4]*Cross_M.data[8]- Cross_M.data[5]*Cross_M.data[7])
			+Cross_M.data[1]*(Cross_M.data[5]*Cross_M.data[6]- Cross_M.data[3]*Cross_M.data[8]) 
			+Cross_M.data[2]*(Cross_M.data[3]*Cross_M.data[7]- Cross_M.data[4]*Cross_M.data[6]);
	
}
