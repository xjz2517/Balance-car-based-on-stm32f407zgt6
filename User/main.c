
#include "system.h"
float Encoder_Left,Encoder_Right;         		 //左右编码器的脉冲计数
int Moto1=0,Moto2=0;												 //计算出来的最终赋给电机的PWM

int i=0;
int main(void)	
{ 
  SysTick_Init(168);   	           //=====延时函数初始化	
	NVIC_Configuration();					 //=====中断优先级分组
	USART1_Init(115200);          //=====串口1初始化
	LED_Init();                    //=====初始化与 LED 连接的IO
	TIM1_PWM_Init(8400,0);     //=====初始化PWM 10KHZ,用于驱动电机。
  Encoder_Init_TIM8();					 //=====编码器2初始化
	Encoder_Init_TIM3();					 //=====编码器3初始化

	delay_ms(1000);								 //=====延时1s 解决小车上电轮子乱转的问题
	Motor_Init();									 //=====初始化与电机连接的硬件IO接口 
	TIM4_Init(100,8400-1);			 //=====10ms中断一次。电机全速运行时编码器最大值为90		
 // TIM4_Init(50,8400-1);			   //=====5ms中断一次。电机全速运行时编码器最大值为45
	 while(1)	
	{
		i++;
		if(i%20==0)
		{
			LED1=!LED1;
			printf("Encoder_Left=%.2f,Encoder_Right=%.2f\n",Encoder_Left,Encoder_Right);
		}
		delay_ms(10);
	}			
	}
	
