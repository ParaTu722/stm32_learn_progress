#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "pwm.h"
#include "Delay.h"

uint8_t i;

int main(void)
{
    OLED_Init();
    PWM_Init();
    
    while(1)
    {
        for(i = 0; i <= 100; i++)
        {
			
            PWM_Setcompare2(i);//修改占空比
            Delay_ms(10);
        }
        
        for(i = 100; i <= 0; i--)
        {

            PWM_Setcompare2(i);//修改占空比
            Delay_ms(10);
        }
    }
}

