#include "stm32f10x.h"                  // Device header
#include "pwm.h"

//PWM频率：	Freq = CK_PSC / (PSC + 1) / (ARR + 1)
//PWM占空比：	Duty = CCR / (ARR + 1)
//PWM分辨率：	Reso = 1 / (ARR + 1) 
//舵机要求：频率50hz  占空比0.5~2.5ms  分辨率1%的pwm   
//ARR = 20k-1  psc = 72-1(这两个可以调节的) 

//PWM驱动舵机
//定时器3的通道1  固定连接PA6  
void PWM_Init(void)
{
    //1、RCC开启时钟
    //2、配置时基单元
    //3、配置输出比较单元
    //4、配置GPIO
    //5、配置定时器运行
    
    //1、RCC开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA
    
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽输出（看说明图，引脚需要由定时器控制）
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;          //定时器3通道1接引脚PA6        
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA, &GPIO_InitStruct);             
    
    
	//2、选择时基单元的时钟源
	TIM_InternalClockConfig(TIM3);	//选择内部时钟（不写也行，默认就是内部时钟）
	
	//3、配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//外部时钟滤波单元的分频系数，没用，随便配置一个就行
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	//时间公式CK_PSC / (PSC + 1) / (ARR + 1)  CK_PSC=72MHZ
    TIM_TimeBaseInitStruct.TIM_Period = 20000-1;						//周期，ARR自动重装器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;					//psc分频值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter =0;				//重复计数器的值，高级定时器才有，给0就行
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
    //没里列出来的为高级定时器才需要用到的
    TIM_OCInitTypeDef TIM_OCInitStruct;
		
    TIM_OCStructInit(&TIM_OCInitStruct);//结构体初始化
		
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;              //设置输出模式
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;      //设置输出比较的极性
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  //设置输出使能
    
		TIM_OCInitStruct.TIM_Pulse = 0;      //设置ccr的值（翻转值）
    TIM_OC1Init(TIM3,&TIM_OCInitStruct);    //定时器3的通道1
		TIM_OC1PreloadConfig
    
    
	
	//6、配置运行控制
	TIM_Cmd(TIM3, ENABLE);	//启动定时器3
}

//修改ccr的值
void PWM_Setcompare1(uint16_t Compare1)
{
    TIM_SetCompare1(TIM3, Compare1);
}
