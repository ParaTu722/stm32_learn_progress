#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "cntsensor.h"
#include "encoder.h"
#include "timer.h"


uint16_t Num;

int main(void)
{
    OLED_Init();
    TIMER_Init();//定时器初始化
    
    OLED_ShowString(1,1,"Num:");
    
    while(1)
    {
        OLED_ShowNum(1,5,Num,5);
        OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);
        
    }
}

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        Num++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
