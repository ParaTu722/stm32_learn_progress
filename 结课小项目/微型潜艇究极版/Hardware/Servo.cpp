#include "stm32f10x.h"                  // Device header
#include "pwm.h"


void SERVER_Init(void)
{
    PWM_Init();
}

void SERVER_SetAngle(float Angle)
{

    PWM_Setcompare1(Angle / 180 *2000+500);
}
