#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Jeston_nano_GPIO.h"

int  io_test, i;
int value = 0;
char buff[256];
FILE *GPIO_LED;
 
int main(){
 printf("gp:");
 scanf("%d",&io_test);

 gpio_export(io_test);
 gpio_set_dir(io_test,1);

 while(1){
 gpio_set_value(io_test,value);
 if(value == 0)	value = 1;
 else	value = 0;
 sleep(2);
 }
 fclose(GPIO_LED);

 gpio_unexport(io_test);

 return 0;
}
