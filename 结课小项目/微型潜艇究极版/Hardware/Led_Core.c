#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void LedCore_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
    
  GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;             
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	
  GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);	//不将灯初始化灭掉，可能会判断错误，例如io占用等
}

//led亮
void LedCore_ON(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

//led灭
void LedCore_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}


//led闪烁，x为延时毫秒数
void LedCore_Blink(int x)
{
	while(1)
	{
		LedCore_ON();
		Delay_ms(x);
		LedCore_OFF();
		Delay_ms(x);
	}
}
