#include "stm32f10x.h"                  // Device header


//蜂鸣器  接PA4  低电平响
void BUZZER_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出（开漏输出没有驱动能力）
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;             
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //一般设置为50MHZ就可以
    GPIO_Init(GPIOA, &GPIO_InitStruct);             //初始化GPIO
    
    GPIO_SetBits(GPIOA,GPIO_Pin_4);                 //设置默认为高电平（蜂鸣器不响）
}

void BUZZER_On(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}


void BUZZER_Off(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_4);
}

//蜂鸣器翻转
void BUZZER_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_4) == 0) //读取输出寄存器某位的值
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_4);
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
    }
}
