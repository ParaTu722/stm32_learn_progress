#include "stm32f10x.h"                  // Device header

int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//启动GPIOC的时钟
        
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;         
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC,&GPIO_InitStruct);
    //GPIO_SetBits(GPIOC,GPIO_Pin_13);              //设置GPIO为高电平 （LED灭）
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);              //设置GPIO为低电平（LED亮）
    while(1)
    {
        
    }
}

