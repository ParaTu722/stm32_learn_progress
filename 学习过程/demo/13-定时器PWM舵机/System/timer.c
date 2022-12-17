#include "stm32f10x.h"                  // Device header

//extern int Num;

void TIMER_Init(void)
{
	//1、RCC开启时钟
	//2、选择时基单元的时钟源
	//3、配置时基单元
	//4、配置中断输出控制
	//5、配置NVIC
	//6、配置运行控制
	
	//1、RCC开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//2、选择时基单元的时钟源
	TIM_InternalClockConfig(TIM2);	//选择内部时钟（不写也行，默认就是内部时钟）
	
	//3、配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//外部时钟滤波单元的分频系数，没用，随便配置一个就行
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	//时间公式CK_PSC / (PSC + 1) / (ARR + 1)  CK_PSC=72MHZ
	//定时1S = 72MHZ/7200/10000
	TIM_TimeBaseInitStruct.TIM_Prescaler = 10000-1;					//分频值
	TIM_TimeBaseInitStruct.TIM_Period = 7200-1;						//周期，ARR自动重装器的值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter =0;				//重复计数器的值，高级定时器才有，给0就行
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	//TIM_TimeBaseInit设置自动更新会进一次中断，这边清除中断解决刚上电就会进一次中断的问题
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
    
    
	//4、配置中断输出控制
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//更新中断到NVIC使能
	
	//5、配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		//选择优先级分组2
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	//6、配置运行控制
	TIM_Cmd(TIM2, ENABLE);	//启动定时器2
	
}

//void TIM2_IRQHandler(void)
//{
//    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
//    {
//        Num++;
//        TIM_ClearITPendingBit(TIM2, TIM_IT_Update)
//    }
//}
