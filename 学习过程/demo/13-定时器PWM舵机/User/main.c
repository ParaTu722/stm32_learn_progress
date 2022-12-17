#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "pwm.h"
#include "Delay.h"
#include "servo.h"
#include "key.h"

uint8_t KeyNum;
float Agle=1;
int main(void)
{
    OLED_Init();
    //PWM_Init();
    SERVER_Init();
    KEY_Init();
    //PWM_Setcompare1(500);//0.5ms舵机0度位置
    //PWM_Setcompare1(2500);//2.5ms舵机180度位置
    SERVER_SetAngle(Agle);
    OLED_ShowString(1,1,"Angle:");
    while(1)
    {
       KeyNum = KEY_GetNum();
        if(KeyNum==1)
        {
            Agle+=30;
            if(Agle > 180)
            {
                Agle = 1;
            }
        }
        SERVER_SetAngle(Agle);
        OLED_ShowNum(1,7,Agle,3);
    }
}

