#include <REGX52.H>
#include "oled.h"
#include "Key.h"
#include "Motor.h"
#include "Delay.h"
#include "Motor_PID.h"
#include "Gyro_PID.h"
#include "GrayscaleSensor.h"
#include "Driving.h"

unsigned char Task4_KeyNumber;

unsigned char Task4()
{
	last_error = 0;
	Base_Speed=18;
	
	OLED_Clear();
	OLED_ShowString(44,0,"Task5",16);
	OLED_ShowString(36,3,"Calib..",16);
	Motor_Init();
	Delay(100);
	Reset_Gyro_PID();
	
	OLED_ShowString(36,3,"       ",16);
	OLED_ShowString(36,3,"Running",16);
	
	while(1)
	{
		Task4_KeyNumber=Key();
		if(Task4_KeyNumber)
		{
			switch(Task4_KeyNumber)
			{
				case 4:Motor_Set(0,0);return 1;break;
				case 5:Motor_Set(0,0);return 0;break;
			}
		}
		
		Get_NewVal();
		while(All_White_Flag())
		{
			Get_NewVal();
			PID_Gyro_Straight_Loop();
		}
		//到达B点	
		AV_Prompt();
		
		Get_NewVal();
		while(!All_Black_Flag())
		{
			PID_Control_Loop();
		}
		//到达C点
		AV_Prompt();
		Forward_ABit();
		
		Base_Speed=12;
		
		Get_NewVal();
		while(!All_Black_Flag())
		{
			PID_Control_Loop();
		}
		//到达D点
		AV_Prompt();
		Forward_ABit();
		
		Base_Speed=18;
		
		Get_NewVal();
		while(!All_White_Flag())
		{
			PID_Control_Loop();
		}
		//到达A点
		AV_Prompt();
		
		while(1)
		{
			Task4_KeyNumber=Key();
			if(Task4_KeyNumber)
			{
				switch(Task4_KeyNumber)
				{
					case 4:Motor_Set(0,0);return 1;break;
					case 5:Motor_Set(0,0);return 0;break;
				}
			}
		}
		
	}
}


