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

unsigned char Task6_KeyNumber,Laps=1;

unsigned char Task6()
{
	unsigned int i;
	last_error = 0;
	Base_Speed=0;
	Motor_Set(Base_Speed,Base_Speed);
	
	OLED_Clear();
	OLED_ShowString(44,0,"Task6",16);
	
	OLED_ShowString(8, 2, "Number of laps", 16);
	
	while(Task6_KeyNumber!=3)
	{
		OLED_ShowNum(60,4,Laps,1,16);
		Task6_KeyNumber=Key();
		if(Task6_KeyNumber==1)
		{
			Laps++;
			if(Laps==6) Laps=1;
		}
		if(Task6_KeyNumber==2)
		{
			Laps--;
			if(Laps==0) Laps=5;
		}
	}
	
	OLED_ShowString(8, 2, "              ", 16);
	OLED_ShowString(60, 4, " ", 16);
	
	//陀螺仪校准
	OLED_ShowString(36,3,"Calib..",16);
	Motor_Init();
	Delay(100);
	Reset_Gyro_PID();
	
	OLED_ShowString(36,3,"       ",16);
	OLED_ShowString(36,3,"Running",16);
	
	while(1)
	{
	Task6_KeyNumber=Key();
		if(Task6_KeyNumber)
		{
			switch(Task6_KeyNumber)
			{
				case 4:Motor_Set(0,0);return 1;break;
				case 5:Motor_Set(0,0);return 0;break;
			}
		}
		while(Laps--)
		{
			Base_Speed=20;
			i=0;
			Get_NewVal();
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
			Base_Speed=18;
			PID_Control_Loop();
			while(!All_White_Flag())
			{
				PID_Control_Loop();
			}
			//到达B点	
			AV_Prompt();
			
			while(All_White_Flag())
			{
				Get_NewVal();
				PID_Gyro_Straight_Loop();
			}
			AV_Prompt();
		}
		while(1)
		{
			Task6_KeyNumber=Key();
			if(Task6_KeyNumber)
			{
				switch(Task6_KeyNumber)
				{
					case 4:Motor_Set(0,0);return 1;break;
					case 5:Motor_Set(0,0);return 0;break;
				}
			}
		}
	}
}


