#ifndef __CONTROL_H
#define __CONTROL_H
#include "system.h"



void EXTI9_5_IRQHandler(void);
int balance_UP(float Angle,float Mechanical_balance,float Gyro);
int velocity(int encoder_left,int encoder_right,int target);
int Turn_UP(int gyro_Z, int RC);

extern float pitch,roll,yaw; 								  			 //欧拉角(姿态角)
extern short aacx,aacy,aacz;													 //加速度传感器原始数据
extern short gyrox,gyroy,gyroz;											 //陀螺仪原始数据
extern float Encoder_Left,Encoder_Right;         		 //左右编码器的脉冲计数
extern int Moto1,Moto2;												 //计算出来的最终赋给电机的PWM




#endif
