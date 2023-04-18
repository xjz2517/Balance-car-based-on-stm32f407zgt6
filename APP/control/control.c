#include "control.h"
#include "usart.h"	
#include <MPU6050.h>
#include "system.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

int Balance_Pwm,Velocity_Pwm,Turn_Pwm,Turn_Kp;

float Target_Speed=0;	//期望速度（俯仰）。用于控制小车前进后退及其速度。
float Turn_Speed=0;		//期望速度（偏航）

float balance_UP_KP=330;//550; 	 // 小车直立环PD参数
float balance_UP_KD=1.02;

float velocity_KP=105;     // 小车速度环PI参数
float velocity_KI=0.525;
 
float Turn_Kd=TURN_KD;//转向环KP、KD
float Turn_KP=TURN_KP;

float Mechanical_angle=0; 





/*******************************************************************************
* 函 数 名         : EXTI0_IRQHandler
* 函数功能		   : 外部中断0函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)==1)
	{
		
		mpu_dmp_get_data(&pitch,&roll,&yaw);										 //得到欧拉角（姿态角）的数据
		MPU6050_Get_Gyroscope(&gyrox,&gyroy,&gyroz);								 //得到陀螺仪数据
		Led_Flash(100);
		
		
		
		
		


		Encoder_Right= Read_Encoder(2); 
		Encoder_Left =-Read_Encoder(3);
		
		Balance_Pwm =balance_UP(roll,Mechanical_angle,gyrox);   							//===直立环PID控制	
	  Velocity_Pwm=velocity(Encoder_Left,Encoder_Right,Target_Speed);       //===速度环PID控制	 
		//Turn_Pwm =Turn_UP(gyroz,Turn_Speed);        													//===转向环PID控制
		
		
		Moto1=Balance_Pwm+Velocity_Pwm;//+Turn_Pwm;  	            	//===计算左轮电机最终PWM
		Moto2=Balance_Pwm+Velocity_Pwm;//-Turn_Pwm;                  //===计算右轮电机最终PWM

		
		Xianfu_Pwm();  				 																	  //===PWM限幅
		Set_Pwm(Moto1,Moto2);                                     //===赋值给PWM寄存器
		
		
		
		}
    EXTI_ClearITPendingBit(EXTI_Line0);	
	}
	



/**************************************************************************
函数功能：直立PD控制
入口参数：角度、机械平衡角度（机械中值）、角速度
返回  值：直立控制PWM
作    者：大鱼电子
**************************************************************************/
int balance_UP(float Angle,float Mechanical_balance,float Gyro)
{  
   float Bias;
	 int balance;
	
	 Bias=Angle-Mechanical_balance;
	 balance=balance_UP_KP*Bias+balance_UP_KD*Gyro;  //===计算平衡控制的电机PWM  PD控制   kp是P系数 kd是D系数 
	 return balance;
}

/**************************************************************************
函数功能：速度PI控制
入口参数：电机编码器的值
返回  值：速度控制PWM
作    者：大鱼电子
**************************************************************************/
int velocity(int encoder_left,int encoder_right,int Target_Speed)
{  
    static float Velocity,Encoder_Least,Encoder;
	  static float Encoder_Integral;
   //=============速度PI控制器=======================//	
    Encoder_Least=(Encoder_Left+Encoder_Right)-Target_Speed;//-target;                    //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度 
		Encoder *= 0.8f;		                                                //===一阶低通滤波器       
		Encoder += Encoder_Least*0.2f;	                                    //===一阶低通滤波器    
		Encoder_Integral +=Encoder;                                       //===积分出位移 积分时间：10ms
		//Encoder_Integral=Encoder_Integral - Target_Speed;                       //===接收遥控器数据，控制前进后退
		if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===积分限幅
		if(Encoder_Integral<-10000)		Encoder_Integral=-10000;            //===积分限幅	
		Velocity=Encoder*velocity_KP+Encoder_Integral*velocity_KI;        //===速度控制	
	  if(pitch<-40||pitch>40) 			Encoder_Integral=0;     						//===电机关闭后清除积分
	  return Velocity;
}
/**************************************************************************
函数功能：转向PD控制
入口参数：电机编码器的值、Z轴角速度
返回  值：转向控制PWM
作    者：大鱼电子
**************************************************************************/

int Turn_UP(int gyro_Z, int RC)
{
	int PWM_out;
		/*转向约束*/
	if(RC==0)Turn_Kd=TURN_KD;//若无左右转向指令，则开启转向约束
	else Turn_Kd=0;//若左右转向指令接收到，则去掉转向约束
	
	PWM_out=Turn_Kd*gyro_Z + Turn_KP*RC;
	return PWM_out;
}


















