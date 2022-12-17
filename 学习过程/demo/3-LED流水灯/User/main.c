#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//底板流水灯  接PA1 PA2 PA3 低电平点亮
int main(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	//使能打开
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);	//GPIO初始化

	GPIO_SetBits(GPIOA,GPIO_Pin_1);	//GPIO_Write方法可删除
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	Delay_ms(1000);
	
	while(1)
	{
		/*
		Delay_ms(300);
		GPIO_Write(GPIOA, ~0x00000008);
		Delay_ms(300);
		GPIO_Write(GPIOA, ~0x00000004);
		Delay_ms(300);
		GPIO_Write(GPIOA, ~0x00000002);
		
		*/
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
		
	}
}

