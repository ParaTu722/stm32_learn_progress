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
#include "show_inform.h"


/*

引脚说明：
--------------------------------------------
	蜂鸣器：				PA4
	底板LED：				PA1,PA2,PA3
	核心板LED：			PC13
	底板按键：			未使用
	中断按键：			PB4,PB5
	中断按键优先级：PB5 > PB4
	OLED显示器：		PB8,PB9
	DHT11:					PA11
	HC_SR04:				PA12(Echo),PB3(Trig),TIM2
	PWM舵机:				PA6,TIM3
	旋钮编码器：		PB0,PB1
	ADC：						ADC1
	雨滴：					PA7，通道7
	光敏：					PA3，通道3
--------------------------------------------

*/


uint16_t  Cnt;			//系统开启百分百显示
uint8_t KeyNum = 0;	//按键判断
uint8_t flag = 1;		//舵机运行标志	1运行 0停止
extern int16_t encoder_function_Num;


//系统初始化界面
void show_init()
{
	OLED_ShowString(1,1,"---------------");
	OLED_ShowString(2,1,"|    welcome  |");
	OLED_ShowString(3,1,"|    system   |");
	OLED_ShowString(4,1,"--   ");
	OLED_ShowString(4,10,"    -- ");
	for(Cnt=0;Cnt<=100;Cnt++)
	{
		Delay_ms(20);
		OLED_ShowNum(4,6,Cnt,3);
		OLED_ShowString(4,9,"%");
	}
}


//超声波：此功能由中断触发按键读值 
//key2触发中断，令KeyNum = 3 以此进入程序;
void keyctrl()
{
	int j=0;
	float length;
	char strff[10];
	
	if(KeyNum == 3)
	{
		OLED_Clear();
		
		for(j=0 ; j<=20 ; j++)
		{
			OLED_ShowString(1,1,"SonicDetection");
			length=Hcsr04GetLength();
			Delay_ms(50);
			length = length/2;
			sprintf(strff,"%.3f",length);
			OLED_ShowString(2,3,strff);
//			if(length > 40)
//			{
//				while(flag)
//				{
//					int i = 180;
//					for(i=180 ; i>=0 ; i--)
//					{
//						SERVER_SetAngle(i);
//						i--;
//					}
//				}
//			}
		}
		j=0;
		Delay_ms(200);
		encoder_function_Num=0;
	}
}


int main(void)
{
	//1.开机启动，舵机运行
	init();
	show_init();
	while(flag)
	{
		SERVER();
	}
	//2.中断舵机。查看设备状态
	OLED_Clear();
	while(1)
	{
		flag=1;
		while(KeyNum != 3)
		{
			flag=1;
			Delay_ms(100);
			encoder_function();
		}
		keyctrl();
		KeyNum=0;
	}
}
