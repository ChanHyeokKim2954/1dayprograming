#include "IfxPort.h"

#define LED_1   &MODULE_P00,5
#define LED_2   &MODULE_P00,6

#define IOport  &MODULE_P02,4

void init_GPIO_LED1(void)
{
    IfxPort_setPinMode(LED_1, IfxPort_Mode_outputPushPullGeneral); //INPUT
    IfxPort_setPinMode(IOport, IfxPort_Mode_inputPullUp); //OUTPUT
}

void init_GPIO_LED2(void)
{
    IfxPort_setPinMode(LED_2, IfxPort_Mode_outputPushPullGeneral); //INPUT
    IfxPort_setPinMode(IOport, IfxPort_Mode_inputPullUp); //OUTPUT
}

void control_LED(void)
{

    if(IfxPort_getPinState(IOport) == 1) //IF LOW
    {
        IfxPort_setPinState(LED_2, IfxPort_State_high); //LOW
        IfxPort_setPinState(LED_1, IfxPort_State_low);
    }
    else
    {
        IfxPort_setPinState(LED_1, IfxPort_State_high); //HIGH
        IfxPort_setPinState(LED_2, IfxPort_State_low);
    }

}
