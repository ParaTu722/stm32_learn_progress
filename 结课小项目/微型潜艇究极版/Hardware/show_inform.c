#include "stm32f10x.h"  
#include "Delay.h"
#include <string.h>
#include <stdio.h>
#include "Led_Core.h"
#include "Led_Bottom.h"
#include "Buzzer.h"
#include "Key.h"
#include "OLED.h"
#include "ad.h"
#include "DHT11.h"
#include "HC_SR04.h"
#include "Servo.h"
#include "encoder.h"
#include "keyexit.h"



uint16_t ADvalue1 = 0;//雨滴值
uint16_t ADvalue2 = 0;//光敏值
int16_t encoder_function_Num = 0;		//旋转编码器转动数字以此进入对于功能

extern uint8_t dat[5];//温湿度值
extern uint8_t flag;


//系统初始化
void init(void)
{
	LedCore_Init();
	LedBottom_Init();
	Buzzer_Init();      
	//KEY_Init();
	OLED_Init();
	AD_Init();
	HC_SR04_init();
	SERVER_Init();
	ENCODER_Init();     //旋转编码器中断初始化
	keyexit_init();
}


//蜂鸣器警报
void bwarm1()
{
		Buzzer_ON();
		Delay_ms(50);
		Buzzer_OFF();
}


//湿度警报
void warming1()
{
	while(1)
	{	
	OLED_ShowString(1,1,"--------------- ");
	OLED_ShowString(2,1,"|H is too high| ");
	OLED_ShowString(3,1,"| turn it down| ");
	OLED_ShowString(4,1,"--------------- ");
	
	Led01Bottom_Turn();
	bwarm1();
	DHT_Read();
	
	if(dat[0]<70)
		{
			OLED_Clear();
			break;
		}
	}	
}

//温度警报
void warming2()
{
	while(1)
	{	
		OLED_ShowString(1,1,"--------------- ");
		OLED_ShowString(2,1,"|T is too high| ");
		OLED_ShowString(3,1,"| turn it down| ");
		OLED_ShowString(4,1,"--------------- ");
		
		Led01Bottom_Turn();
		bwarm1();
		DHT_Read();
		
		if(dat[2]<30)
		{
			OLED_Clear();
			break;
		}
	}
}


//温湿度获取，显示
void TorH(void)
{
	DHT_Read();
	Delay_ms(500);
	
	OLED_ShowString(1,1,"T:");
	OLED_ShowNum(1,3,dat[2],2);
	OLED_ShowString(1,5,"^C ");
	
	OLED_ShowString(1,8,"H:");
	OLED_ShowNum(1,10,dat[0],2);
	OLED_ShowString(1,12,"%    ");
	
	OLED_ShowString(2,1,"----Everything  ");
	OLED_ShowString(3,1,"------Works     ");
	OLED_ShowString(4,1,"--------Fine    ");	 
	if(dat[0]>70)			
	{
		OLED_Clear();
		warming1();
	}
	if(dat[2]>30)			
	{
		OLED_Clear();
		warming2();
	}
}


//雨滴值获取，显示
void rain()
{
	uint16_t rval;
	OLED_ShowString(1,1,"Flow intensity  ");
	ADvalue1 = Get_ADValue(ADC_Channel_7);
	rval = 99-((float)ADvalue1*3.3/4096)*2*99.0/5.0;
	OLED_ShowString(2,1,"  ");
	OLED_ShowNum(2,3,rval,2);
	OLED_ShowString(2,5,"%           ");
	OLED_ShowString(3,1,"                ");
	OLED_ShowString(4,1,"                ");
	if(rval >= 70)
	{
		OLED_ShowString(3,1,"   Water Large  ");
		Led01Bottom_Turn();
		bwarm1();
	}
	Delay_ms(100);
}


//光敏获取，显示
void light()
{
	ADvalue2 = Get_ADValue(ADC_Channel_3);
	Delay_ms(100);
	OLED_ShowString(1,1,"Light intensity ");
	OLED_ShowString(2,1,"  ");
	int light_intensity = 99-((float)ADvalue2*3.3/4096)*2*99.0/5.0;
	OLED_ShowNum(2,3,light_intensity,2);
	OLED_ShowString(2,5,"%           ");
	OLED_ShowString(3,1,"                ");
	OLED_ShowString(4,1,"                ");
	if(light_intensity < 40)
	{
		OLED_ShowString(3,1,"It^s too dark   ");
		Led01Bottom_Turn();
		bwarm1();
	}
	if(light_intensity > 70)
	{
		OLED_ShowString(3,1,"It^s so bright  ");
		Led01Bottom_Turn();
		bwarm1();
	}
}


//正常报告显示
void show()
{
	OLED_ShowString(1,1,"--------------- ");
	OLED_ShowString(2,1,"|  submarine  | ");
	OLED_ShowString(3,1,"|  In action  | ");
	OLED_ShowString(4,1,"--------------- ");
	Delay_ms(20);
}


//舵机前进运行
void SERVER()
{
	int i=0;
	for(i=1 ; i<=180 ; i++)
	{
		SERVER_SetAngle(i);
		i++;
	}
}



//旋转编码器功能显示界面
void encoder_show()
{
	OLED_ShowString(1,1,"1.T or H        ");
	OLED_ShowString(2,1,"2.Rain          ");
	OLED_ShowString(3,1,"3.Light         ");
	OLED_ShowString(4,1,"4.Show and Run  ");
}



//旋转编码器对应功能对应界面
void encoder_function(void)
{
	encoder_function_Num += ENCODER_Get();
	
	if(encoder_function_Num <= -1)
	{
		encoder_function_Num = 0;
	}
	if(encoder_function_Num == 0)
	{
		encoder_show();
	}
	if(encoder_function_Num == 1)
	{
		TorH();
	}
	if(encoder_function_Num == 2)
	{
		rain();
	}
	if(encoder_function_Num == 3)
	{
		light();
	}
	if(encoder_function_Num == 4)
	{
		show();
	}
	if(encoder_function_Num == 5)
	{
		OLED_ShowString(1,1,"                ");
		OLED_ShowString(2,1," Speed is normal");
		OLED_ShowString(3,1,"                ");
		OLED_ShowString(4,1,"                ");
		while(flag)
		{
			SERVER();
		}
	}
	if(encoder_function_Num >= 6)
	{
		encoder_function_Num = 0;
	}
}


