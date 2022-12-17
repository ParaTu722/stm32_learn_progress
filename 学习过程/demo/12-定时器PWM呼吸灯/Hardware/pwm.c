#include "stm32f10x.h"                  // Device header
#include "pwm.h"

//PWM频率：	Freq = CK_PSC / (PSC + 1) / (ARR + 1)
//PWM占空比：	Duty = CCR / (ARR + 1)
//PWM分辨率：	Reso = 1 / (ARR + 1) 
//产生：频率1Khz  占空比50  分辨率1%的pwm   
//ARR = 100-1   ccr = 50   psc = 720-1

//LED呼吸灯效果
//定时器2的通道2  固定连接PA1  开发板LED1就是接的这个引脚
void PWM_Init(void)
{
    //1、RCC开启时钟
    //2、配置时基单元
    //3、配置输出比较单元
    //4、配置GPIO
    //5、配置定时器运行
    
    //1、RCC开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   //使能GPIOA
    
    //引脚重映射的使用方式
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
    //GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);//看afio章节表43  TIM2复用功能重映射
    //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,DISABLE);//如果需要解除引脚功能 使用这种方式（谨慎使用）
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;   //复用推挽输出（看说明图，引脚需要由定时器控制）
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;          //定时器2通道2         
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOA, &GPIO_InitStruct);             
    
    
	//2、选择时基单元的时钟源
	TIM_InternalClockConfig(TIM2);	//选择内部时钟（不写也行，默认就是内部时钟）
	
	//3、配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;		//外部时钟滤波单元的分频系数，没用，随便配置一个就行
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; 	//向上计数
	//时间公式CK_PSC / (PSC + 1) / (ARR + 1)  CK_PSC=72MHZ
    TIM_TimeBaseInitStruct.TIM_Period = 100-1;						//周期，ARR自动重装器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720-1;					//psc分频值
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter =0;				//重复计数器的值，高级定时器才有，给0就行
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
    //没里列出来的为高级定时器才需要用到的
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCStructInit(&TIM_OCInitStruct);//结构体初始化
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;              //设置输出模式
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;      //设置输出比较的极性
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  //设置输出使能
    TIM_OCInitStruct.TIM_Pulse = 0;      //设置ccr的值（翻转值）
    TIM_OC2Init(TIM2,&TIM_OCInitStruct);    //定时器2的通道2
    
    
	
	//6、配置运行控制
	TIM_Cmd(TIM2, ENABLE);	//启动定时器2
}

//修改ccr的值
void PWM_Setcompare2(uint16_t Compare2)
{
    TIM_SetCompare2(TIM2, Compare2);
}
