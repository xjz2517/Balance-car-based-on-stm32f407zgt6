#include "motor.h"
//方向控制端口初始化函数
void Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //使能PB端口时钟
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;//输出模式
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//管脚设置
	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;//速度为100M
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
	AIN1=0,AIN2=0;
	BIN1=0,BIN2=0;
}
/**************************************************************************
函数功能：正反转控制，占空比控制
入口参数：左轮PWM、右轮PWM
返回  值：无
**************************************************************************/
void Set_Pwm(int moto1,int moto2)
{
	if(moto1<0)			AIN2=1,			AIN1=0;
	else 	          AIN2=0,			AIN1=1;
	PWMA=myabs(moto1);
	if(moto2<0)	BIN1=0,			BIN2=1;
	else        BIN1=1,			BIN2=0;
	PWMB=myabs(moto2);	
}

/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
目    的：PWM有可能为负值，而只能赋给定时器PWM寄存器只能是正值。故需要对PWM进行绝对值处理
**************************************************************************/
int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}
/**************************************************************************
函数功能：限制PWM赋值 
入口参数：无
返回  值：无
**************************************************************************/
void Xianfu_Pwm(void)
{
	 //===PWM满幅是8400 限制在8200
    if(Moto1<-8200 ) Moto1=-8200 ;
		if(Moto1>8200 )  Moto1=8200 ;
	  if(Moto2<-8200 ) Moto2=-8200 ;
		if(Moto2>8200 )  Moto2=8200 ;
}
