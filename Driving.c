#include <REGX52.H>
#include "GrayscaleSensor.h"
#include "Delay.h"
#include "Gyro_PID.h"
#include "UART_JY61P.h"
#include "Motor.h"
#include "Motor_PID.h"
#include "Gyro_PID.h"

//控制左右轮的函数
void Motor_Set(char sL, char sR) 
{
	// 左轮
	if (sL >= 0) 
	{ 
		MotorB_Forward();  speedB = sL; 
	}
	else
	{ 
		MotorB_Backward(); speedB = -sL; 
	}
	
	// 右轮
	if (sR >= 0) 
	{ 
		MotorA_Forward();  speedA = sR; 
	}
	else
	{
		MotorA_Backward(); speedA = -sR; 
	}

	// 限幅
	if(speedB > 100) speedB = 100;
	if(speedA > 100) speedA = 100;
}

//判断是否遇到全黑
unsigned char All_Black_Flag()
{
	if ((val & 0x7E) == 0x7E) return 1;
	else return 0;
}

//判断是否遇到全白
unsigned char All_White_Flag()
{
	if (val==0) return 1;
	else return 0;
}

//遇到横黑线之后向前冲一段距离离开横黑线
void Forward_ABit()
{
	Motor_Set(15,15);
	Delay(100);
}

//声光提示
void AV_Prompt()
{
	Motor_Set(0,0);
	P0_0=0;
	P0_3=0;
	Delay(200);
	P0_3=1;
	P0_0=1;
}

//掉头
void UTurn()
{
	Motor_Set(-25,25);
	Delay(250);
}

//向右转90°
void Turn_Right_90()
{
	short current_yaw;
	short remaining;
	
	while(1)
	{
		current_yaw = Get_Relative_Yaw();
		if(current_yaw < 0) current_yaw = -current_yaw; 
		
		// 90度对应的原始数值
		// 理论值是 16384。
		// 但考虑到刹车惯性，小车停下时会多转一点。
		// 目标值设小一点，比如 6500（测试后的数据），靠惯性滑到90度
		remaining = 6500 - current_yaw;
		
		if(remaining <= 0) break;
		
		Motor_Set(25, -25);
	}
	
	Motor_Set(-10, 10);
	Delay(50);
	Motor_Set(0, 0);
	Delay(200);
}