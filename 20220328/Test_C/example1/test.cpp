#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	printf("argc = %d\n",argc);
	for(int i = 0; i < argc ; i++)	printf("argv[%d] = %s\n",i,argv[i]);
	
	float x = atof(argv[1]);
	float y = atof(argv[2]);
	
	printf("%.2f + %.2f = %.2f \n",x,y,x+y);
	printf("%.2f - %.2f = %.2f \n",x,y,x-y);
	printf("%.2f * %.2f = %.2f \n",x,y,x*y);
	printf("%.2f / %.2f = %.2f \n",x,y,x/y);
	
	return 1;
 
}
