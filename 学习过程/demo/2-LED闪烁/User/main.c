#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//点亮核心板的led  接PC13 低电平点亮
int main(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   //使能GPIOC
    
    GPIO_InitTypeDef GPIO_InitStruct;
	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;             
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  //一般设置为50MHZ就可以
	
	
    GPIO_Init(GPIOC, &GPIO_InitStruct);             //初始化GPIO
    
    //GPIO_ResetBits(GPIOC, GPIO_Pin_13);             //设置引脚为低电平
    GPIO_SetBits(GPIOC, GPIO_Pin_13);               //设置引脚为高电平（默认led熄灭）
    
    //作用同上
    //GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);   //设置引脚为低电平
    //GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);   //设置引脚为高电平
    
    while(1)
    {
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_RESET);   //led亮
        Delay_ms(500);                                  //延迟500ms
        GPIO_WriteBit(GPIOC, GPIO_Pin_13, Bit_SET);     //led灭
        Delay_ms(500);                                  //延迟500ms
    }
}

