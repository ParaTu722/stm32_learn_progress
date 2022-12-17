#include "stm32f10x.h"                  // Device header

//光敏的DO连接 PA0口
void LIGHTSENSOR_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint8_t LIGHTSENSOR_Get(void)
{
    return GPIO_ReadInputDataBit(GPIOA,  GPIO_Pin_7);
}
