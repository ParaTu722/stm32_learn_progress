#include "stm32f10x.h"                  // Device header
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

uint16_t yudi = 0;
uint16_t guangm = 0;

void init(void)
{
	LedCore_Init();
	LedBottom_Init();
	Buzzer_Init();      //蜂鸣器初始化
	KEY_Init();
	OLED_Init();				//oled初始化
	AD_Init();
	HC_SR04_init();
	SERVER_Init();
}



void test11(void)
{
	while(1)
	{
		yudi = Get_ADValue(ADC_Channel_3);
		guangm = Get_ADValue(ADC_Channel_7);
		OLED_ShowNum(1,1,yudi,5);
		OLED_ShowNum(2,1,guangm,5);
	}
}




//温湿度
extern uint8_t dat[5];
void test12(void)
{
	OLED_ShowString(1,1,"T:");
	OLED_ShowString(1,5,"^C");
	OLED_ShowString(1,8,"H:");
	OLED_ShowString(1,12,"%");
	while (1)
	{
		DHT_Read();
		OLED_ShowNum(1,3,dat[2],2);
		OLED_ShowNum(1,10,dat[0],2);
	}
}




void test13(void)
{
	float length;
	char strff[10];
	
	while(1)
	{
		length=Hcsr04GetLength();	//获取距离
		length = length/2;
		sprintf(strff,"%.3f",length);
		OLED_ShowString(1,1,strff);
		Delay_ms(50);
	}
}


void test14(void)
{
	float i=1;
	SERVER_SetAngle(i);
	while(1)
	{
		for(i=1 ; i<=180 ; i++)
		{
			SERVER_SetAngle(i);
			i++;
		}
		i=1;
	}
	
}

void show_all(void)
{
//	float length;
//	char strff[10];
//	
	float i=1;
	SERVER_SetAngle(i);
	OLED_ShowString(1,1,"T:");
	OLED_ShowString(1,5,"^C");
	OLED_ShowString(1,8,"H:");
	OLED_ShowString(1,12,"%");
	while(1)
	{
		yudi = Get_ADValue(ADC_Channel_3);
		guangm = Get_ADValue(ADC_Channel_7);
		DHT_Read();
//		length=Hcsr04GetLength();	//获取距离
//		length = length/2;
//		sprintf(strff,"%.3f",length);
		
//		OLED_ShowString(2,1,strff);
		OLED_ShowNum(1,3,dat[2],2);
		OLED_ShowNum(1,10,dat[0],2);
		OLED_ShowNum(3,1,yudi,5);
		OLED_ShowNum(4,1,guangm,5);
		for(i=1 ; i<=180 ; i++)
		{
			SERVER_SetAngle(i);
			i++;
		}
		i=1;
	}
}












