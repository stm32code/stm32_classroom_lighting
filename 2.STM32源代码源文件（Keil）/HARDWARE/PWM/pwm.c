#include "pwm.h"

uint16_t PWM_Cycle;//PWM����

void TIMx_PWM_Init(TIM_TypeDef* TIMx,GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin_x,u8 Channel,float Frequency)//TIMx_PWM��ʼ��,TIMx:TIM1~TIM8,GPIOx:GPIOA~GPIOG,GPIO_Pin_x:GPIO_Pin_0~GPIO_Pin_15,Channel:1~4,Frequency:Ƶ��(0.019KHz~65535KHz)
{
	uint16_t Arr,Psc;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	if(Frequency>=0.019 && Frequency<0.039)                      //0.019KHz~0.039KHz
		Psc=57599;                                               //TIMxʱ��Ƶ�ʳ���Ԥ��Ƶֵ
	else if(Frequency>=0.039 && Frequency<0.05)                  //0.039KHz~0.05KHz
		Psc=28799;                                               //TIMxʱ��Ƶ�ʳ���Ԥ��Ƶֵ
	else if(Frequency>=0.05 && Frequency<10)                     //0.05KHz~10KHz
		Psc=7199;                                                //TIMxʱ��Ƶ�ʳ���Ԥ��Ƶֵ
	else if(Frequency>=10 && Frequency<100)                      //10KHz~100KHz
		Psc=719;                                                 //TIMxʱ��Ƶ�ʳ���Ԥ��Ƶֵ
	else if(Frequency>=100 && Frequency<1000)                    //100KHz~1000KHz
		Psc=71;                                                  //TIMxʱ��Ƶ�ʳ���Ԥ��Ƶֵ
	else if(Frequency>=1100 && Frequency<65535)                  //1100KHz~65535KHz
		Psc=0;                                                   //TIMxʱ��Ƶ�ʳ���Ԥ��Ƶֵ
	
	Arr=(72000/((Psc+1)*Frequency));                             //�Զ���װ�ؼĴ�������ֵ
	PWM_Cycle=Arr;                                               //PWM����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);          //ʹ��AFIOʱ��(ʹ�ܹ��ܸ���IO)
	
	if(TIMx==TIM1)                                               //�߼���ʱ��1
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);      //ʹ��TIM1ʱ��
	else if(TIMx==TIM2)                                          //ͨ�ö�ʱ��2
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);      //ʹ��TIM2ʱ��
	else if(TIMx==TIM3)                                          //ͨ�ö�ʱ��3
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);      //ʹ��TIM3ʱ��
	else if(TIMx==TIM4)                                          //ͨ�ö�ʱ��4
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);      //ʹ��TIM4ʱ��
	else if(TIMx==TIM5)                                          //ͨ�ö�ʱ��5
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);      //ʹ��TIM5ʱ��
	else if(TIMx==TIM8)                                          //�߼���ʱ��8
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);      //ʹ��TIM8ʱ��
	
	if(GPIOx==GPIOA)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);     //ʹ��PA�˿�ʱ��
	else if(GPIOx==GPIOB)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);     //ʹ��PB�˿�ʱ��
	else if(GPIOx==GPIOC)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);     //ʹ��PC�˿�ʱ��
	else if(GPIOx==GPIOD)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);     //ʹ��PD�˿�ʱ��
	else if(GPIOx==GPIOE)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);     //ʹ��PE�˿�ʱ��
	else if(GPIOx==GPIOF)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);     //ʹ��PF�˿�ʱ��
	else if(GPIOx==GPIOG)
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);     //ʹ��PG�˿�ʱ��
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);      //JTAG-DPʧ��+SW-DPʹ��
	
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,DISABLE);            //TIM1û����ӳ��,TIM1_CH1_ETR(PA12),TIM1_CH1(PA8),TIM1_CH2(PA9),TIM1_CH3(PA10),TIM1_CH4(PA11),TIM1_BKIN(PB12),TIM1_CH1N(PB13),TIM1_CH2N(PB14),TIM1_CH3N(PB15)
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1,ENABLE);          //TIM1������ӳ��1,TIM1_CH1_ETR(PA12),TIM1_CH1(PA8),TIM1_CH2(PA9),TIM1_CH3(PA10),TIM1_CH4(PA11),TIM1_BKIN(PA6),TIM1_CH1N(PA7),TIM1_CH2N(PB0),TIM1_CH3N(PB1)
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);             //TIM1��ȫ��ӳ��,TIM1_CH1_ETR(PE7),TIM1_CH1(PE9),TIM1_CH2(PE11),TIM1_CH3(PE13),TIM1_CH4(PE14),TIM1_BKIN(PE15),TIM1_CH1N(PE8),TIM1_CH2N(PE10),TIM1_CH3N(PE12)
	
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,DISABLE);            //TIM2û����ӳ��,TIM2_CH1_ETR(PA0),TIM2_CH2(PA1),TIM2_CH3(PA2),TIM2_CH4(PA3)
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);         //TIM2������ӳ��1,TIM2_CH1_ETR(PA15),TIM2_CH2(PB3),TIM2_CH3(PA2),TIM2_CH4(PA3)
//	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2,ENABLE);         //TIM2������ӳ��2,TIM2_CH1_ETR(PA0),TIM2_CH2(PA1),TIM2_CH3(PB10),TIM2_CH4(PB11)
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);             //TIM2��ȫ��ӳ��,TIM2_CH1_ETR(PA15),TIM2_CH2(PB3),TIM2_CH3(PB10),TIM2_CH4(PB11)
	
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,DISABLE);            //TIM3û����ӳ��,TIM3_CH1(PA6),TIM3_CH2(PA7),TIM3_CH3(PB0),TIM3_CH4(PB1)
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);          //TIM3������ӳ��,TIM3_CH1(PB4),TIM3_CH2(PB5),TIM3_CH3(PB0),TIM3_CH4(PB1)
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);             //TIM3��ȫ��ӳ��,TIM3_CH1(PC6),TIM3_CH2(PC7),TIM3_CH3(PC8),TIM3_CH4(PC9)
	
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4,DISABLE);                //TIM4û����ӳ��,TIM4_CH1(PB6),TIM4_CH2(PB7),TIM4_CH3(PB8),TIM4_CH4(PB9)
//	GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);                 //TIM4��ӳ��,TIM4_CH1(PD12),TIM4_CH2(PD13),TIM4_CH3(PD14),TIM4_CH4(PD15)
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;            //IO���ٶ�Ϊ50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;                    //����GPIO_Pin_x����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;              //�����������
	GPIO_Init(GPIOx,&GPIO_InitStructure);                        //��ʼ��GPIOx
	
	TIM_TimeBaseStructure.TIM_Period = (uint16_t)Arr-1;	         //�Զ���װ�ؼĴ�������ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)Psc;         //TIMxʱ��Ƶ�ʳ���Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;            //TIM�����ȵ���1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//ʹ�ܱȽ����
	TIM_OCInitStructure.TIM_Pulse = 0;                           //��װ�벶��ȽϼĴ�������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;    //TIM�Ƚ�������Ը�
	if(Channel==1)
		TIM_OC1Init(TIMx,&TIM_OCInitStructure);                  //TIMxͨ��1,��������
	else if(Channel==2)
		TIM_OC2Init(TIMx,&TIM_OCInitStructure);                  //TIMxͨ��2,��������
	else if(Channel==3)
		TIM_OC3Init(TIMx,&TIM_OCInitStructure);                  //TIMxͨ��3,��������
	else if(Channel==4)
		TIM_OC4Init(TIMx,&TIM_OCInitStructure);                  //TIMxͨ��4,��������
	
	if(Channel==1)
		TIM_OC1PreloadConfig(TIMx,TIM_OCPreload_Enable);     //ʹ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
	else if(Channel==2)
		TIM_OC2PreloadConfig(TIMx,TIM_OCPreload_Enable);     //ʹ��TIMx��CCR2�ϵ�Ԥװ�ؼĴ���
	else if(Channel==3)
		TIM_OC3PreloadConfig(TIMx,TIM_OCPreload_Enable);     //ʹ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���
	else if(Channel==4)
		TIM_OC4PreloadConfig(TIMx,TIM_OCPreload_Enable);     //ʹ��TIMx��CCR4�ϵ�Ԥװ�ؼĴ���
	
	if(TIMx==TIM1 || TIMx==TIM8)
	{
		TIM_CtrlPWMOutputs(TIMx,ENABLE);                         //�����ʹ��
		TIM_ARRPreloadConfig(TIMx,ENABLE);                       //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	}
	
	TIM_Cmd(TIMx,ENABLE);                                        //ʹ��TIMx����
}

void TIMx_PWM_Out(TIM_TypeDef* TIMx,u8 Channel,float Duty_Cycle)//TIMx_PWM���,TIMx:TIM1~TIM8,Channel:1~4,ռ�ձ�Duty_Cycle:1~100
{
	TIM_SetCompare4(TIMx,(uint16_t)((Duty_Cycle/10)*PWM_Cycle));//TIMxͨ��4
}
