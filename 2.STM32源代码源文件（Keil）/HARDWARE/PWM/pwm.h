#ifndef __pwm_H
#define __pwm_H

#include "sys.h"

void TIMx_PWM_Init(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x,u8 Channel,float Frequency);//TIMx_PWM初始化,TIMx:TIM1~TIM8,GPIOx:GPIOA~GPIOG,GPIO_Pin_x:GPIO_Pin_0~GPIO_Pin_15,Channel:1~4,Frequency:频率(0.019KHz~65535KHz)
void TIMx_PWM_Out(TIM_TypeDef* TIMx,u8 Channel,float Duty_Cycle);                                        //TIMx_PWM输出,TIMx:TIM1~TIM8,Channel:1~4,占空比Duty_Cycle:1~100

#endif
