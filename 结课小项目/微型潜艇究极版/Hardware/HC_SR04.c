#include "stm32f10x.h"
#include "Delay.h"
#include "stdint.h"

 
void HC_SR04_init(void)
{
	//1.端口使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
	//2.gpio配置
	//GPIOB_Pin_3:Trig，输入
	//GPIOA_Pin_12:Echo，输出 
	GPIO_InitTypeDef  GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 	//浮空输入	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);						 						
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				//推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOB, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
 
	
	//3.选择时基单元的时钟源												
	TIM_InternalClockConfig(TIM2);
														
	//4.配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;			//外部时钟滤波单元的分频系数，没用，随便配置一个就行
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	//时间公式CK_PSC / (PSC + 1) / (ARR + 1)  CK_PSC=72MHZ
	//定时1S = 72MHZ/7200/10000
	//定时1ms = 1/72MHZ/7200/10  T=1/f
	TIM_TimeBaseInitStruct.TIM_Prescaler = 20-1;					//分频值
	TIM_TimeBaseInitStruct.TIM_Period = 7200-1;						//周期，ARR自动重装器的值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter =0;			//重复计数器的值，高级定时器才有，给0就行
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//TIM_TimeBaseInit设置自动更新会进一次中断，这边清除中断解决刚上电就会进一次中断的问题
  TIM_ClearFlag(TIM2,TIM_FLAG_Update);

	//5.配置中断输出控制
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//更新中断到NVIC使能
 
	//6.配置NVIC：优先级（内核外设都在杂项  misc.h里面）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置中断组为2

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;						//使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级（多个中断才有作用） 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;				//响应优先级（多个中断才有作用）
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);
 
  //7.配置运行控制
	TIM_Cmd(TIM2, DISABLE);	
}


//定时器中断产生次数
uint8_t msHcCount = 0;
void TIM2_IRQHandler(void)   //TIM2中断
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)//检查指定的 TIM 中断发生与否
	{
		msHcCount++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	//清除 TIMx 的中断待处理位
	}
}


 //打开定时器
void OpenTimer()       
{
	TIM_SetCounter(TIM2,0);	//重置 TIMx 计数器寄存器值
	msHcCount = 0;					//重置中断产生次数
	TIM_Cmd(TIM2,ENABLE);		//使能定时器
}

//关闭定时器
void CloseTimer()        
{
	TIM_Cmd(TIM2,DISABLE);
}



//获取路程时间
uint32_t GetEchoTimer(void)
{
  uint32_t time = 0;
	time = TIM_GetCounter(TIM2);//获取计TIM2数寄存器中的计数值，一边计算回响信号时间
	time += msHcCount*1000;//msHcCount毫秒，time微妙
	TIM2->CNT = 0;  //将TIM2计数寄存器的计数值清零
	return time;
}



float Hcsr04GetLength(void )
{
	float length = 0;
	float length_end = 0;
	float t = 0;
	float sum = 0;
	int i = 0;
	//测五次取平均值
	for(i = 0;i < 5;i++)
	{
		//1：trig拉高信号，发出高电平。输入方波后，模块会自动发射8个40KHz的声波
		GPIO_SetBits(GPIOB,GPIO_Pin_3);
		Delay_us(20);//持续时间超过10us，手册要求
		GPIO_ResetBits(GPIOB,GPIO_Pin_3);
		
		//回波信号检测
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == RESET);//echo等待回响
		/*开启定时器*/
		OpenTimer();
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 1);
		/*关闭定时器*/
		CloseTimer();
		
		//获取收发时间间隔
		t = GetEchoTimer();
		length = (float)t/58;		//单位时cm
		sum += length;
		i = i+1; //每收到一次回响信号+1，收到5次就计算均值
	}
	length_end = sum/5;//五次平均值
	return length_end;
}

