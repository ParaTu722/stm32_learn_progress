#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include <string.h>
#include <stdio.h>
#include "Led_Core.h"
#include "Led_Bottom.h"
#include "Buzzer.h"
#include "Key.h"
#include "Lightsensor.h"
#include "OLED.h"
#include "encoder.h"
#include "cntsensor.h"
#include "timer.h"
#include "ad.h"


/*
# define ch1on = "LED1_ON";
# define ch1off = "LED1_OFF";
*/
uint8_t KeyNum = 0;	

void init(void)
{
	LedCore_Init();
	LedBottom_Init();
	Buzzer_Init();      //蜂鸣器初始化
	KEY_Init();
	LIGHTSENSOR_Init(); //光敏传感器初始化
	OLED_Init();				//oled初始化
	CNTSENSOR_Init();   //光电中断初始化
  ENCODER_Init();     //旋转编码器中断初始化
	TIMER_Init();				//定时器初始化
	AD_Init();
}

//底板，核心板led闪烁
void test01(void)
{
	LedCore_ON();
	Delay_ms(500);
	//LedCore_Blink(200);
	while(1)
	{
		KeyNum = KEY_GetNum();
		if(KeyNum == 1)
		{
			Led01Bottom_ON();
			Buzzer_ON();
			Delay_ms(500);
			Led01Bottom_OFF();
			Buzzer_OFF();
			Delay_ms(500);
		}
		if(KeyNum == 2)
		{
			Led02Bottom_ON();
			Delay_ms(500);
			Led02Bottom_OFF();
			Delay_ms(500);
		}
		if(KeyNum == 3)
		{
			Led03Bottom_ON();
			Delay_ms(500);
			Led03Bottom_OFF();
			Delay_ms(500);
		}
	}
	//LedBottom_RunningWaterLamps(300);
}



//光敏传感器测试
//周末作业2，光敏控制流水灯开关并蜂鸣器响（遮挡住就开灯响铃）
void test02(void)
{
	while(1)
	{
		if(LIGHTSENSOR_Get() == 1)
		{
			Buzzer_ON();
			OLED_ShowString(1,1,"Buzzer_ON");
			LedBottom_RunningWaterLamps(200);
			OLED_Clear();
		}
		else
		{
			Buzzer_OFF();
			OLED_ShowString(1,1,"Buzzer_OFF");
		}
	}
}


//oled显示测试
void test03(void)
{
	OLED_ShowChar(1,1,'S');
	OLED_ShowString(1,3,"HelloWorld");
	
	OLED_ShowNum(2,1,12345,5);//只能显示无符号数
  OLED_ShowSignedNum(2,7,-66,2);	//十进制，带符号数
	
  OLED_ShowHexNum(3,1,0xAA55,4);	//十六进制，正数
  OLED_ShowBinNum(4,1,0xAA55,16);//显示二进制 16表示16位
	
}



//周末作业1，key1,2,3控制led1,2,3，按下开关后：开变成关 关变成开
//周末作业3，显示屏根据led状态  在第一行第二行第三行显示led on or off
//周末作业4，oled最后一行显示姓名缩写加学号
void test04(void)
{
	Led01Bottom_OFF();
	Led02Bottom_OFF();
	Led03Bottom_OFF();
	while(1)
	{
		KeyNum = KEY_GetNum();
		if(KeyNum == 1)
		{
			Delay_ms(200);
			Led01Bottom_Turn();
		}
		if(KeyNum == 2)
		{
			Delay_ms(200);
			Led02Bottom_Turn();
		}
		if(KeyNum == 3)
		{
			Delay_ms(200);
			Led03Bottom_Turn();
		}
		OLED_ShowString(1,1,"HelloWorld");
	}
}



//周末作业3，显示屏根据led状态  在第一行第二行第三行显示led on or off
//周末作业4，oled最后一行显示姓名缩写加学号
void test05(void)
{
	Led01Bottom_OFF();
	Led02Bottom_OFF();
	Led03Bottom_OFF();
	
	char ch1[10],ch2[10],ch3[10];
	OLED_ShowString(1,1,"GO");
	OLED_ShowString(2,1,"GO");
	OLED_ShowString(3,1,"GO");
	OLED_ShowString(4,1,"scc_061");
	while(1)
	{
		KeyNum = KEY_GetNum();
		if(KeyNum == 1)
		{
			Delay_ms(200);
			Led01Bottom_Turn();
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
			{
				strcpy(ch1,"LED1_O N");
			}
			else
			{
				strcpy(ch1,"LED1_OFF");
			}
			OLED_ShowString(1,1,ch1);
		}
		if(KeyNum == 2)
		{
			Delay_ms(200);
			Led02Bottom_Turn();
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)
			{
				strcpy(ch2,"LED2_O N");
			}
			else
			{
				strcpy(ch2,"LED2_OFF");
			}
			OLED_ShowString(2,1,ch2);
		}
		if(KeyNum == 3)
		{
			Delay_ms(200);
			Led03Bottom_Turn();
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) == 0)
			{
				strcpy(ch3,"LED3_O N");
			}
			else
			{
				strcpy(ch3,"LED3_OFF");
			}
			OLED_ShowString(3,1,ch3);	
		}
	}
}



//周末作业汇总
void test06(void)
{
	Led01Bottom_OFF();
	Led02Bottom_OFF();
	Led03Bottom_OFF();
	
	//字符串初始化
	char ch1[10],ch2[10],ch3[10];
	OLED_ShowString(1,1,"GO");
	OLED_ShowString(2,1,"GO");
	OLED_ShowString(3,1,"GO");
	OLED_ShowString(4,1,"scc_061");
	
	while(1)
	{
		KeyNum = KEY_GetNum();
		//按键1
		if(KeyNum == 1)
		{
			Delay_ms(200);
			Led01Bottom_Turn();
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
			{
				strcpy(ch1,"LED1_O N");
			}
			else
			{
				strcpy(ch1,"LED1_OFF");
			}
			OLED_ShowString(1,1,ch1);
		}
		//按键2
		if(KeyNum == 2)
		{
			Delay_ms(200);
			Led02Bottom_Turn();
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)
			{
				strcpy(ch2,"LED2_O N");
			}
			else
			{
				strcpy(ch2,"LED2_OFF");
			}
			OLED_ShowString(2,1,ch2);
		}
		//按键3
		if(KeyNum == 3)
		{
			Delay_ms(200);
			Led03Bottom_Turn();
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) == 0)
			{
				strcpy(ch3,"LED3_O N");
			}
			else
			{
				strcpy(ch3,"LED3_OFF");
			}
			OLED_ShowString(3,1,ch3);	
		}
		
		//光敏模块
		if(LIGHTSENSOR_Get() == 1)
		{
			Buzzer_ON();
			OLED_ShowString(1,1,"Buzzer_ON");
			LedBottom_RunningWaterLamps(200);
			
			//光敏流水灯执行完进行led判断
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
			{
				strcpy(ch1,"LED1_O N");
			}
			else
			{
				strcpy(ch1,"LED1_OFF");
			}
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)
			{
				strcpy(ch2,"LED2_O N");
			}
			else
			{
				strcpy(ch2,"LED2_OFF");
			}
			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_3) == 0)
			{
				strcpy(ch3,"LED3_O N");
			}
			else
			{
				strcpy(ch3,"LED3_OFF");
			}
			OLED_ShowChar(1,9,' ');
			OLED_ShowChar(2,9,' ');
			OLED_ShowChar(3,9,' ');
			OLED_ShowString(1,1,ch1);
			OLED_ShowString(3,1,ch3);
			OLED_ShowString(2,1,ch2);
		}
		else
		{
			Buzzer_OFF();
		}
	}
}





//光电中断计次
void test07(void)
{
	OLED_ShowString(1,1,"Cnt:"); 
  while(1)
  {
		OLED_ShowNum(1,4, CNTSENSOR_Get(),5);  
  }
}



//旋钮中断计次
int16_t Num;
void test08(void)
{
	OLED_ShowString(1,1,"Num:");
  while(1)
  {
		//OLED_ShowNum(1,4, CNTSENSOR_Get(),5);
		Num += ENCODER_Get();
		OLED_ShowSignedNum(1,5, Num,5);
	}
}




//test09 定时器定时中断
uint16_t test09_Num;

void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        test09_Num++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}


void test09(void)
{
	OLED_ShowString(1,1,"Time_Num:");
    
  while(1)
  {
		OLED_ShowNum(1,10,test09_Num,5);
    OLED_ShowNum(3,5,TIM_GetCounter(TIM2),5);
  }
	
}


// 11-外部时钟定时器
void test10(void)
{
	OLED_ShowString(1,1,"Num:");
  OLED_ShowString(2,1,"Cnt:");
  while(1)
  {
		OLED_ShowNum(1,5,Num,5);
    OLED_ShowNum(2,5,TIMER_GetCount(),5);
	}
}


uint16_t ADValue = 0;
void test11(void)
{
	OLED_ShowString(1,1,"-ADValue:");
	while(1)
	{
		ADValue = Get_ADValue();
		OLED_ShowNum(2,5,ADValue,5);
	}
}











