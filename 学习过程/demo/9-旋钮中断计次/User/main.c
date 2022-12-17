#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "cntsensor.h"
#include "encoder.h"

int16_t Num;
int main(void)
{
    OLED_Init();
    CNTSENSOR_Init();   //光电中断初始化
    ENCODER_Init();     //旋转编码器中断初始化

    OLED_ShowString(1,1,"Num:");
    
    while(1)
    {
        //OLED_ShowNum(1,4, CNTSENSOR_Get(),5);
        Num += ENCODER_Get();
        OLED_ShowSignedNum(1,5, Num,5);
    }
}

