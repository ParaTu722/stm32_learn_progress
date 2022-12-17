#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "buzzer.h"
#include "lightsensor.h"

int main(void)
{

    BUZZER_Init();      //蜂鸣器初始化
    LIGHTSENSOR_Init(); //光敏传感器初始化
    
    while(1)
    {
        if(LIGHTSENSOR_Get() == 1)
        {
            BUZZER_On();    
        }
        else
        {
            BUZZER_Off();
        }
    }
}

