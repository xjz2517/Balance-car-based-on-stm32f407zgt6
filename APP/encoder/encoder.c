//编码器初始化
/*函数功能：把TIM2初始化为编码器接口模式
入口参数：无
返回  值：无*/


#include "encoder.h"
void Encoder_Init_TIM8(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);//使能定时器8的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能PA端口时钟
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);//管脚功能复用映射
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口PC6,PC7配置
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;//复用模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;//上拉输入
	GPIO_Init(GPIOC,&GPIO_InitStructure);//编码器对应端口初始化
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStructure);  //将结构体用默认值填充
  TIM_TimeBaseInitStructure.TIM_Period=ENCODER_TIM_PERIOD;; //自动装载值
  TIM_TimeBaseInitStructure.TIM_Prescaler=0x0; //分频系数，不分频
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
  TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStructure);
	TIM_EncoderInterfaceConfig(TIM8, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM8,&TIM_ICInitStructure);
  TIM_ClearFlag(TIM8,TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM8,TIM_IT_Update,ENABLE);
  //Reset counter
  TIM_SetCounter(TIM8,0);
  TIM_Cmd(TIM8,ENABLE); 

}


/**************************************************************************
函数功能：把TIM3初始化为编码器接口模式
入口参数：无
返回  值：无
**************************************************************************/
void Encoder_Init_TIM3(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;  
  TIM_ICInitTypeDef TIM_ICInitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能定时器2的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能PA端口时钟
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);//管脚功能复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//端口PA6,PA7配置
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;//复用模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;//上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//编码器对应端口初始化
	TIM_TimeBaseStructInit (&TIM_TimeBaseInitStructure);  //将结构体用默认值填充
  TIM_TimeBaseInitStructure.TIM_Period=ENCODER_TIM_PERIOD;; //自动装载值
  TIM_TimeBaseInitStructure.TIM_Prescaler=0x0; //分频系数，不分频
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;//选择时钟分频：不分频
  TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置向上计数模式
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	//TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 10;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
  TIM_ClearFlag(TIM3,TIM_FLAG_Update);//清除TIM的更新标志位
  TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);
  //Reset counter
  TIM_SetCounter(TIM3,0);
  TIM_Cmd(TIM3, ENABLE); 

}
/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
	   case 2:  Encoder_TIM= (short)TIM8 -> CNT;  TIM8 -> CNT=0;break;
		 case 3:  Encoder_TIM= (short)TIM3 -> CNT;  TIM3 -> CNT=0;break;	
		 case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=0;break;	
		 default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}
/*函数功能：TIM3中断服务函数
入口参数：无
返回  值：无
**************************************************************************/
void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0X0001)//溢出中断
	{
   TIM3->SR&=~(1<<0);//清除中断标志位 			
	}				   
	    
}
/**************************************************************************
函数功能：TIM8中断服务函数
入口参数：无
返回  值：无
**************************************************************************/
void TIM8_UP_TIM13_IRQHandler(void)
{
	if(TIM8->SR&0X0001)//溢出中断
	{
   TIM8->SR&=~(1<<0);//清除中断标志位		
	}				   
	 	    
}







