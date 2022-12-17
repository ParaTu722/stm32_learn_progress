#include "stm32f10x.h"
#include "key.h"
#include "Delay.h"


void KEY_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
}

uint8_t KEY_GetNum(void)
{
    uint8_t KeyNum = 0;
    
    if(GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_4) == 0)//读取输入数据的某位
    {
        Delay_ms(20);   //消除按下抖动
        while(GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_4) == 0);   //循环直到松手
        Delay_ms(20);   //消除松手抖动
        KeyNum = 1;

    }
    
    if(GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_5) == 0)//读取输入数据的某位
    {
        Delay_ms(20);   //消除按下抖动
        while((KeyNum = GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_5)) == 0);   //循环直到松手
        Delay_ms(20);   //消除松手抖动
        KeyNum = 2;

    }
    
    if(GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_6) == 0)//读取输入数据的某位
    {
        Delay_ms(20);   //消除按下抖动
        while(GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_6) == 0);   //循环直到松手
        Delay_ms(20);   //消除松手抖动
        KeyNum = 3;

    }
    
    return KeyNum;
}
