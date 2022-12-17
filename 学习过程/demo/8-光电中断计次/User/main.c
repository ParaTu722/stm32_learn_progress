#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "cntsensor.h"
int main(void)
{
    OLED_Init();
    CNTSENSOR_Init();//中断初始化
    OLED_ShowString(1,1,"Cnt:");
    
    while(1)
    {
        OLED_ShowNum(1,4, CNTSENSOR_Get(),5);
        
    }
}

