#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//底板蜂鸣器  接PA4 低电平点响
int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA
    
    GPIO_InitTypeDef GPIO_InitStruct;
	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出（开漏输出没有驱动能力）
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;             
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //一般设置为50MHZ就可以
	
    GPIO_Init(GPIOA, &GPIO_InitStruct);             //初始化GPIO
    
    
    while(1)
    {
				GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);	//蜂鸣器响
				Delay_ms(200);
				GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_SET);
				GPIO_SetBits(GPIOA,  GPIO_Pin_4);	//蜂鸣器不响
			
				Delay_ms(200);
				GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);	//蜂鸣器响
				Delay_ms(200);
				GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_SET);
				GPIO_SetBits(GPIOA,  GPIO_Pin_4);	//蜂鸣器不响
			
				Delay_ms(200);
				GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_RESET);
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);	//蜂鸣器响
				Delay_ms(200);
				GPIO_WriteBit(GPIOA, GPIO_Pin_3, Bit_SET);
				GPIO_SetBits(GPIOA,  GPIO_Pin_4);	//蜂鸣器不响
			
				Delay_ms(200);
		}
			
}

