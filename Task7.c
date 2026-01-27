#include <REGX52.H>
#include "oled.h"
#include "Key.h"
#include "Motor.h"
#include "Delay.h"
#include "GrayscaleSensor.h"
#include "UART_JY61P.h"
#include "Motor_PID.h"
#include "Gyro_PID.h"
#include "Driving.h"

unsigned char Task7_KeyNumber;

unsigned char Task7()
{
	unsigned int i=0;
	last_error = 0;
	Base_Speed=20;
	
	OLED_Clear();
	OLED_ShowString(44,0,"Task7",16);
	
	//陀螺仪校准
	OLED_ShowString(36,3,"Calib..",16);
	Motor_Init();
	Delay(100);
	Reset_Gyro_PID();
	
	OLED_ShowString(36,3,"       ",16);
	OLED_ShowString(36,3,"Running",16);
	
	Motor_Set(Base_Speed,Base_Speed);
	
	while(1)
	{
		Task7_KeyNumber=Key();
		if(Task7_KeyNumber)
		{
			switch(Task7_KeyNumber)
			{
				case 4:Motor_Set(0,0);return 1;break;
				case 5:Motor_Set(0,0);return 0;break;
			}
		}
		
		PID_Control_Loop();
		while(!All_Black_Flag())
		{
			Get_NewVal();
			PID_Gyro_Straight_Loop();
		}
		AV_Prompt();
		Motor_Set(15,15);
		Delay(200);
		//到达直线终点
		
		Turn_Right_90();
		
		Motor_Set(20,20);
		Delay(550);
		
		AV_Prompt();
		Forward_ABit();
		//到达A点
		
		Motor_Set(-20,20);
		Delay(230);
		
		PID_Control_Loop();
		
		Base_Speed=20;
		while(!All_Black_Flag())
		{
			PID_Control_Loop();
		}
		//到达D点
		AV_Prompt();
		Forward_ABit();
		Base_Speed=12;
		PID_Control_Loop();
		while(!All_Black_Flag())
		{
			PID_Control_Loop();
		}
		//到达C点
		AV_Prompt();
		Forward_ABit();
		Base_Speed=20;
		PID_Control_Loop();
		
		while(!All_White_Flag())
		{
			PID_Control_Loop();
		}
		//到达B点	
		AV_Prompt();
		
		Base_Speed=18;
		while(All_White_Flag())
		{
			Get_NewVal();
			PID_Gyro_Straight_Loop();
		}
		AV_Prompt();
		while(1)
		{
			Task7_KeyNumber=Key();
			if(Task7_KeyNumber)
			{
				switch(Task7_KeyNumber)
				{
					case 4:Motor_Set(0,0);return 1;break;
					case 5:Motor_Set(0,0);return 0;break;
				}
			}
		}
	}
}


