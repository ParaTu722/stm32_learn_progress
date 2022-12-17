#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "key.h"

uint8_t KeyNum = 0;
//底板流水灯  接PA1 PA2 PA3 低电平点亮
int main(void)
{
    LED_Init(); //LED灯初始化
    KEY_Init();
    
    while(1)
    {
        KeyNum = KEY_GetNum();
        if(KeyNum == 1)
        {
            LED1_On();   //点亮第LED1
        }
        if(KeyNum == 2)
        {
            //LED2_On();   //点亮第LED2
            LED1_Off();
        }
        
        if(KeyNum == 3)
        {
            LED3_Turn();  
        }
        
    }
}

