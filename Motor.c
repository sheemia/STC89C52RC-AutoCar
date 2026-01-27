#include <REGX52.H>
#include "GrayscaleSensor.h"
#include "Delay.h"
#include "Gyro_PID.h"
#include "UART_JY61P.h"

sbit PWMA = P1^1;
sbit AIN1 = P1^3;
sbit AIN2 = P1^2;

sbit PWMB = P1^7;
sbit BIN1 = P1^5;
sbit BIN2 = P1^6;

sbit STBY = P1^4;

unsigned char Base_Speed;

unsigned char speedA;
unsigned char speedB;
unsigned char pwmCountA,pwmCountB;

/*********** 定时器0初始化（PWM用） ***********/
void Timer0_Init(void)//100us
{
  TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0xA4;				//设置定时初始值
	TH0 = 0xFF;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时

	ET0=1;
	EA=1;
	PT0=0;
}

/*********** 定时器0中断函数（PWM输出） ***********/
void Timer0_Routine(void) interrupt 1
{
	TL0 = 0xA4;		//设置定时初值
	TH0 = 0xFF;		//设置定时初值
	pwmCountA++;
	pwmCountB++;
	if(pwmCountA >= 100) pwmCountA = 0;
	if(pwmCountB >= 100) pwmCountB = 0;
	PWMA = (pwmCountA < speedA) ? 1 : 0;
	PWMB = (pwmCountB < speedB) ? 1 : 0;
}

//A电机：正转
void MotorA_Forward(void)
{
    AIN1 = 1;
    AIN2 = 0;
}

//A电机：反转
void MotorA_Backward(void)
{
    AIN1 = 0;
    AIN2 = 1;
}

//A电机：刹车
void MotorA_Brake(void)
{
    AIN1 = 1;
    AIN2 = 1;
}

//A电机：停止
void MotorA_Stop(void)
{
    AIN1 = 0;
    AIN2 = 0;
}

//B电机：正转
void MotorB_Forward(void)
{
    BIN1 = 1;
    BIN2 = 0;
}

//B电机：反转
void MotorB_Backward(void)
{
    BIN1 = 0;
    BIN2 = 1;
}

//B电机：刹车
void MotorB_Brake(void)
{
    BIN1 = 1;
    BIN2 = 1;
}

//B电机：停止
void MotorB_Stop(void)
{
    BIN1 = 0;
    BIN2 = 0;
}

//电机初始化
void Motor_Init()
{
	STBY = 1;
  Timer0_Init();
}

