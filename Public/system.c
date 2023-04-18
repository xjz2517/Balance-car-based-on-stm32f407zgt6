#include "system.h"
 /**************************************************************************
 作  者 ：大鱼电子
淘宝地址：https://shop119207236.taobao.com
**************************************************************************/
//设置NVIC 
//NVIC_PreemptionPriority:抢占优先级
//NVIC_SubPriority       :响应优先级
//NVIC_Channel           :中断编号
//NVIC_Group             :中断分组 0~4
//注意优先级不能超过设定的组的范围!否则会有意想不到的错误
//组划分:
//组0:0位抢占优先级,4位响应优先级
//组1:1位抢占优先级,3位响应优先级
//组2:2位抢占优先级,2位响应优先级
//组3:3位抢占优先级,1位响应优先级
//组4:4位抢占优先级,0位响应优先级
//NVIC_SubPriority和NVIC_PreemptionPriority的原则是,数值越小,越优先	   
void NVIC_Configuration(void)
{
	  NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级

		//////////////////定时器4的中断优先级配置//////////////////		
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM4中断
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级1级
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;  //从优先级1级
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
		NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 
	
//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器	

	
	
	//////////////////Usart1 NVIC 中断优先级配置////////////////////////////////////

//编码器 NVIC 配置
	 NVIC_InitStructure.NVIC_IRQChannel=TIM8_UP_TIM13_IRQn;//定时器8中断通道
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	 NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	 //Usart1 NVIC 配置
	 NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;//定时器3中断通道
	 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
	 NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;		//子优先级3
	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	 NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}


