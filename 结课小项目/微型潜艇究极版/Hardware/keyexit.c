#include "stm32f10x.h"                  // Device header
#include "Led_Bottom.h"
#include "OLED.h"
#include "Delay.h"


extern uint8_t flag;
extern int16_t encoder_function_Num;		//旋转编码器转动数字以此进入对于功能

void keyexit_init()
{
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
    
		GPIO_InitTypeDef GPIO_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;			
		NVIC_InitTypeDef NVIC_InitStruct;
	
	
		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource4); 


		
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5); 


		EXTI_InitStruct.EXTI_Line = EXTI_Line4;						
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;						
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;					
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;								
    EXTI_Init(&EXTI_InitStruct);
		
	
		EXTI_InitStruct.EXTI_Line = EXTI_Line5;						
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;						
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;					
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;								
    EXTI_Init(&EXTI_InitStruct);

		
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);				
    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;		
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;		
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;				
    NVIC_Init(&NVIC_InitStruct);	


		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				
    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;		
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;	
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;		
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;				
    NVIC_Init(&NVIC_InitStruct);	
		
}



void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) == SET)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4) == 0)
        {
					flag = 0;
					encoder_function_Num = 0;
				}
        EXTI_ClearITPendingBit(EXTI_Line4);
    } 
}

extern uint8_t KeyNum;
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) == SET)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5) == 0)
        {
					KeyNum = 3;
				}
        EXTI_ClearITPendingBit(EXTI_Line5);
    } 
}
