#include <REGX52.H>
#include "oled.h"
#include "Key.h"
#include "Motor.h"
#include "Delay.h"
#include "Motor_PID.h"
#include "Gyro_PID.h"
#include "GrayscaleSensor.h"
#include "Driving.h"

unsigned char Task2_KeyNumber;

unsigned char Task2()
{
	last_error = 0;
	Base_Speed=20;
	
	OLED_Clear();
	OLED_ShowString(44,0,"Task2",16);
	OLED_ShowString(36,3,"Running",16);
	Motor_Init();
	
	Motor_Set(Base_Speed,Base_Speed);
	
	while(1)
	{
		Task2_KeyNumber=Key();
		if(Task2_KeyNumber)
		{
			switch(Task2_KeyNumber)
			{
				case 4:Motor_Set(0,0);return 1;break;
				case 5:Motor_Set(0,0);return 0;break;
			}
		}
		
		PID_Control_Loop();
		
		if (All_Black_Flag())
		{
			AV_Prompt();
			while(1)
			{
				Task2_KeyNumber=Key();
				if(Task2_KeyNumber)
				{
					switch(Task2_KeyNumber)
					{
						case 4:Motor_Set(0,0);return 1;break;
						case 5:Motor_Set(0,0);return 0;break;
					}
				}
			}
		}
	}
}