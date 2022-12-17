#include "stm32f10x.h"                  // Device header

int16_t  encodeCnt;
void ENCODER_Init()
{
    //外部中断配置步骤，看EXTI基本结构图
    //1、开启RCC时钟
    //2、配置GPIO
    //3、配置AFIO选择中断引脚
    //4、配置EXIT选择触发方式
    //5、配置NVIC：优先级
    
    //1、开启RCC时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //AFIO时钟
    //EXIT不需要开启时钟，NVIC内核外设（不需要开启时钟）不是挂载在APB2总线的
    

    //2、配置GPIO
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//技术手册表31 EXTI输入线配置模式
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    //3、配置AFIO选择中断引脚（stm32f10x_gpio.h中）
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);//AFIO中断选择函数，外部中断线0
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);//AFIO中断选择函数，外部中断线1
    
    //4、配置EXIT选择触发方式
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line0 | EXTI_Line1;            //中断线路10
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;    //中断还是事件选择
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;              //开启中断线
    EXTI_Init(&EXTI_InitStruct);
    
    //5、配置NVIC：优先级（内核外设都在杂项  misc.h里面）
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //NVIC优先级分组,整个工程只能配置一次（放main最好）
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;           //中断通道选择
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级（多个中断才有作用）
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;         //响应优先级（多个中断才有作用）
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;             //通道开启
    NVIC_Init(&NVIC_InitStruct);
    
    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;           //中断通道选择
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级（多个中断才有作用）
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;         //响应优先级（多个中断才有作用）
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;             //通道开启
    NVIC_Init(&NVIC_InitStruct);
}

void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
        {
            encodeCnt--;
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

int16_t ENCODER_Get(void)
{
    int16_t temp;
    
    temp = encodeCnt;
    encodeCnt = 0;
    return temp;
}
void EXTI1_IRQHandler()
{
    if(EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
        {
            encodeCnt++;
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}
