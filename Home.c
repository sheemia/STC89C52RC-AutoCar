#include <REGX52.H>
#include <INTRINS.H>
#include <oled.h>
#include "GrayscaleSensor.h"
#include "Key.h"

unsigned char Home()
{
	unsigned char i;
	unsigned char SensorSum=0;
	unsigned char Sensor[8];
	
	unsigned char Home_KeyNumber=0;
	
	OLED_Clear();
	
	OLED_ShowString(48,0,"Home",16);
	OLED_ShowString(24,2,"GS Sensor:",16);
	OLED_ShowString(0,6,"Press to Menu...",16);
	
	while(1)
	{
		Home_KeyNumber=Key();
		if(Home_KeyNumber==3)
		{
			return 1;
		}
		
		SensorSum=GrayscaleSensor_ReadByte();
		for(i=8;i>0;i--)
		{
			Sensor[i-1]=(SensorSum>>(i-1))&0x01;
			OLED_ShowNum(17*(i-1)+1,4,Sensor[i-1],1,16);
			//显示八个灰度传感器的状态
		}
	}
}