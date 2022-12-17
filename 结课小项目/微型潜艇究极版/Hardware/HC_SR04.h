#ifndef __HC_SR04_H_
#define __HC_SR04_H_


void HC_SR04_init(void);
void OpenTimer(void);
void CloseTimer(void);
void TIM2_IRQHandler(void);
uint32_t GetEchoTimer(void);
float Hcsr04GetLength(void );

#endif

