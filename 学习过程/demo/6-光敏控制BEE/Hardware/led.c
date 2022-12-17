#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出（开漏输出没有驱动能力）
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3;             
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //一般设置为50MHZ就可以
    GPIO_Init(GPIOA, &GPIO_InitStruct);             //初始化GPIO
    
    GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2|GPIO_Pin_3); //设置默认为高电平（LED灭）
}

void LED1_On(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}


void LED1_Off(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void LED2_On(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}


void LED2_Off(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED3_On(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}


void LED3_Off(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_3);
}

//LED3翻转
void LED3_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) == 0) //读取输出寄存器某位的值
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_3);
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_3);
    }
}
