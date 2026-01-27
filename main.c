#include <REGX52.H>
#include "Delay.h"
#include "I2C.h"
#include "GrayscaleSensor.h"
#include "Oled.h"
#include "Home.h"
#include "Menu.h"
#include "Timer2.h"
#include "Task.h"
#include "Motor.h"
#include "UART_JY61P.h"

unsigned char Status=0;

void main()
{
	Motor_Init();
	OLED_Init();
	Timer2Init();
	UART_Init();
	while(1)
	{
		switch(Status)
		{
			case 0:Status=Home();break;
			case 1:Status=Menu();break;
			case 2:Status=Task1();break;
			case 3:Status=Task2();break;
			case 4:Status=Task3();break;
			case 5:Status=Task4();break;
			case 6:Status=Task5();break;
			case 7:Status=Task6();break;
			case 8:Status=Task7();break;
		}
	}
}
