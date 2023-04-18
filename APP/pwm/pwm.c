#include "pwm.h"

/*******************************************************************************
* 函 数 名         : TIM2_CH1_PWM_Init
* 函数功能		   : TIM2通道1 PWM初始化函数
* 输    入         : per:重装载值
					 psc:分频系数
* 输    出         : 无
PWM频率=per+psc+1/时钟频率
*******************************************************************************/
void TIM1_PWM_Init(u16 per,u16 psc)
{
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//使能TIM1时钟,挂在APB2上168MHz
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);//管脚复用
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF; //复用输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_11;//管脚设置
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度为100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化结构体
	
	
	TIM_TimeBaseInitStructure.TIM_Period=per;   //自动装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc; //分频系数
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);	
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	
	//TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
	//TIM_OCInitStructure.TIM_Pulse = per>>1;
	
	TIM_OC1Init(TIM1,&TIM_OCInitStructure); //输出比较通道1初始化
	TIM_OC4Init(TIM1,&TIM_OCInitStructure); //输出比较通道1初始化
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable); //使能TIMx在 CCR1 上的预装载寄存器
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable); //使能TIMx在 CCR1 上的预装载寄存器
	TIM_ARRPreloadConfig(TIM1,ENABLE);//使能预装载寄存器
	
	TIM_Cmd(TIM1,ENABLE); //使能定时器
		
}


