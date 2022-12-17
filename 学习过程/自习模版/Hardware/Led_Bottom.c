#include "stm32f10x.h"                  // Device header
#include "Delay.h"


void LedBottom_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
    
  GPIO_InitTypeDef GPIO_InitStruct;
	
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;             
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
	
}

void Led01Bottom_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void Led01Bottom_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}


void Led02Bottom_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void Led02Bottom_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}


void Led03Bottom_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
}
void Led03Bottom_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
}


void LedBottom_RunningWaterLamps(int x)
{
		Led01Bottom_ON();
		Delay_ms(x);
		Led01Bottom_OFF();
		Delay_ms(x);
		Led02Bottom_ON();
		Delay_ms(x);
		Led02Bottom_OFF();
		Delay_ms(x);
		Led03Bottom_ON();
		Delay_ms(x);
		Led03Bottom_OFF();
		Delay_ms(x);
	
}
//LED1翻转
void Led01Bottom_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0) //读取输出寄存器某位的值
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_1);
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    }
}
//LED2翻转
void Led02Bottom_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0) //读取输出寄存器某位的值
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_2);
    }
    else
    {
        GPIO_ResetBits(GPIOA,GPIO_Pin_2);
    }
}

//LED3翻转
void Led03Bottom_Turn(void)
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
