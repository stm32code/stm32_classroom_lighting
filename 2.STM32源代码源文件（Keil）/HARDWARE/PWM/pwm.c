#include "pwm.h"

uint16_t PWM_Cycle;//PWM周期

void TIMx_PWM_Init(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x,u8 Channel,float Frequency)//TIMx_PWM初始化,TIMx:TIM1~TIM8,GPIOx:GPIOA~GPIOG,GPIO_Pin_x:GPIO_Pin_0~GPIO_Pin_15,Channel:1~4,Frequency:频率(0.019KHz~65535KHz)
{
	uint16_t Arr,Psc;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	if(Frequency>=0.019 && Frequency<0.039)                      //0.019KHz~0.039KHz
		Psc=57599;                                               //TIMx时钟频率除数预分频值
	else if(Frequency>=0.039 && Frequency<0.05)                  //0.039KHz~0.05KHz
		Psc=28799;                                               //TIMx时钟频率除数预分频值
	else if(Frequency>=0.05 && Frequency<10)                     //0.05KHz~10KHz
		Psc=7199;                                                //TIMx时钟频率除数预分频值
	else if(Frequency>=10 && Frequency<100)                      //10KHz~100KHz
		Psc=719;                                                 //TIMx时钟频率除数预分频值
	else if(Frequency>=100 && Frequency<1000)                    //100KHz~1000KHz
		Psc=71;                                                  //TIMx时钟频率除数预分频值
	else if(Frequency>=1100 && Frequency<65535)                  //1100KHz~65535KHz
		Psc=0;                                                   //TIMx时钟频率除数预分频值
	
	Arr=(72000/((Psc+1)*Frequency));                             //自动重装载寄存器周期值
	PWM_Cycle=Arr;                                               //PWM周期
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);          //使能AFIO时钟(使能功能复用IO)
	
	if(TIMx==TIM1)                                               //高级定时器1
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);      //使能TIM1时钟
	else if(TIMx==TIM2)                                          //通用定时器2
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);      //使能TIM2时钟
	else if(TIMx==TIM3)                                          //通用定时器3
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);      //使能TIM3时钟
	else if(TIMx==TIM4)                                          //通用定时器4
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);      //使能TIM4时钟
	else if(TIMx==TIM5)                                          //通用定时器5
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);      //使能TIM5时钟
	else if(TIMx==TIM8)                                          //高级定时器8
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);      //使能TIM8时钟
	
	if(GPIOx==GPIOA)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);     //使能PA端口时钟
	else if(GPIOx==GPIOB)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);     //使能PB端口时钟
	else if(GPIOx==GPIOC)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);     //使能PC端口时钟
	else if(GPIOx==GPIOD)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);     //使能PD端口时钟
	else if(GPIOx==GPIOE)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);     //使能PE端口时钟
	else if(GPIOx==GPIOF)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);     //使能PF端口时钟
	else if(GPIOx==GPIOG)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);     //使能PG端口时钟
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);      //JTAG-DP失能+SW-DP使能
	
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,DISABLE);            //TIM1没有重映像,TIM1_CH1_ETR(PA12),TIM1_CH1(PA8),TIM1_CH2(PA9),TIM1_CH3(PA10),TIM1_CH4(PA11),TIM1_BKIN(PB12),TIM1_CH1N(PB13),TIM1_CH2N(PB14),TIM1_CH3N(PB15)
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,ENABLE);          //TIM1部分重映像1,TIM1_CH1_ETR(PA12),TIM1_CH1(PA8),TIM1_CH2(PA9),TIM1_CH3(PA10),TIM1_CH4(PA11),TIM1_BKIN(PA6),TIM1_CH1N(PA7),TIM1_CH2N(PB0),TIM1_CH3N(PB1)
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);             //TIM1完全重映像,TIM1_CH1_ETR(PE7),TIM1_CH1(PE9),TIM1_CH2(PE11),TIM1_CH3(PE13),TIM1_CH4(PE14),TIM1_BKIN(PE15),TIM1_CH1N(PE8),TIM1_CH2N(PE10),TIM1_CH3N(PE12)
	
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,DISABLE);            //TIM2没有重映像,TIM2_CH1_ETR(PA0),TIM2_CH2(PA1),TIM2_CH3(PA2),TIM2_CH4(PA3)
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);         //TIM2部分重映像1,TIM2_CH1_ETR(PA15),TIM2_CH2(PB3),TIM2_CH3(PA2),TIM2_CH4(PA3)
//	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);         //TIM2部分重映像2,TIM2_CH1_ETR(PA0),TIM2_CH2(PA1),TIM2_CH3(PB10),TIM2_CH4(PB11)
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);             //TIM2完全重映像,TIM2_CH1_ETR(PA15),TIM2_CH2(PB3),TIM2_CH3(PB10),TIM2_CH4(PB11)
	
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,DISABLE);            //TIM3没有重映像,TIM3_CH1(PA6),TIM3_CH2(PA7),TIM3_CH3(PB0),TIM3_CH4(PB1)
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);          //TIM3部分重映像,TIM3_CH1(PB4),TIM3_CH2(PB5),TIM3_CH3(PB0),TIM3_CH4(PB1)
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);             //TIM3完全重映像,TIM3_CH1(PC6),TIM3_CH2(PC7),TIM3_CH3(PC8),TIM3_CH4(PC9)
	
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4,DISABLE);                //TIM4没有重映像,TIM4_CH1(PB6),TIM4_CH2(PB7),TIM4_CH3(PB8),TIM4_CH4(PB9)
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);                 //TIM4重映像,TIM4_CH1(PD12),TIM4_CH2(PD13),TIM4_CH3(PD14),TIM4_CH4(PD15)
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;            //IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;                    //设置GPIO_Pin_x引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //复用推挽输出
	GPIO_Init(GPIOx,&GPIO_InitStructure);                        //初始化GPIOx
	
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)Arr-1;	         //自动重装载寄存器周期值
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)Psc;         //TIMx时钟频率除数预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;            //TIM脉冲宽度调制1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//使能比较输出
	TIM_OCInitStructure.TIM_Pulse = 0;                           //待装入捕获比较寄存器脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //TIM比较输出极性高
	if(Channel==1)
		TIM_OC1Init(TIMx,&TIM_OCInitStructure);                  //TIMx通道1,功能设置
	else if(Channel==2)
		TIM_OC2Init(TIMx,&TIM_OCInitStructure);                  //TIMx通道2,功能设置
	else if(Channel==3)
		TIM_OC3Init(TIMx,&TIM_OCInitStructure);                  //TIMx通道3,功能设置
	else if(Channel==4)
		TIM_OC4Init(TIMx,&TIM_OCInitStructure);                  //TIMx通道4,功能设置
	
	if(Channel==1)
		TIM_OC1PreloadConfig(TIMx,TIM_OCPreload_Enable);     //使能TIMx在CCR1上的预装载寄存器
	else if(Channel==2)
		TIM_OC2PreloadConfig(TIMx,TIM_OCPreload_Enable);     //使能TIMx在CCR2上的预装载寄存器
	else if(Channel==3)
		TIM_OC3PreloadConfig(TIMx,TIM_OCPreload_Enable);     //使能TIMx在CCR3上的预装载寄存器
	else if(Channel==4)
		TIM_OC4PreloadConfig(TIMx,TIM_OCPreload_Enable);     //使能TIMx在CCR4上的预装载寄存器
	
	if(TIMx==TIM1 || TIMx==TIM8)
	{
		TIM_CtrlPWMOutputs(TIMx,ENABLE);                         //主输出使能
		TIM_ARRPreloadConfig(TIMx,ENABLE);                       //使能TIMx在ARR上的预装载寄存器
	}
	
	TIM_Cmd(TIMx,ENABLE);                                        //使能TIMx外设
}

void TIMx_PWM_Out(TIM_TypeDef* TIMx,u8 Channel,float Duty_Cycle)//TIMx_PWM输出,TIMx:TIM1~TIM8,Channel:1~4,占空比Duty_Cycle:1~100
{
	TIM_SetCompare4(TIMx,(uint16_t)((Duty_Cycle/10)*PWM_Cycle));//TIMx通道4
}
