#include "stm32f10x.h"

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	
	
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_Cmd(ADC1,ENABLE); //使能或者失能指定的 ADC
	
	ADC_ResetCalibration(ADC1);	//重置指定的 ADC 的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);	//获取 ADC 重置校准寄存器的状态
	ADC_StartCalibration(ADC1);	//开始指定 ADC 的校准程序
	while(ADC_GetCalibrationStatus(ADC1) == SET);//	获取指定 ADC 的校准状态
	
	
}
uint16_t Get_ADValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);	//使能或者失能指定的 ADC 的软件转换启动功能
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);	//检查制定 ADC 标志位置 1 与否
	
	return ADC_GetConversionValue(ADC1);	//返回最近一次 ADCx 规则组的转换结果
}

