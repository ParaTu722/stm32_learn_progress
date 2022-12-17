#include "stm32f10x.h"

void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA
    
  GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;             
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_SetBits(GPIOA,  GPIO_Pin_4);
}

void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}
