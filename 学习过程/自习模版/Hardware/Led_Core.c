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
	GPIO_SetBits(GPIOC,GPIO_Pin_13);	//�����Ƴ�ʼ����������ܻ��жϴ�������ioռ�õ�
}

//led��
void LedCore_ON(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

//led��
void LedCore_OFF(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}


//led��˸��xΪ��ʱ������
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
