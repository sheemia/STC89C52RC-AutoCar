#include <REGX52.H>
#include "Oled.h"
#include "Home.h"
#include "Key.h"

unsigned char Page,Menu_KeyNumber;

unsigned char Menu()
{
	P0_0=1;
	OLED_Clear();
	Page=1;
	while(1)
	{
		Menu_KeyNumber=Key();
		if(Menu_KeyNumber)
		{
			switch(Menu_KeyNumber)
			{
				case 1:
				{
					Page++;
					if(Page>7) Page=1;
					break;
				}
				case 2:
				{
					Page--;
					if(Page<1) Page=7;
					break;
				}
				case 3:
				{
					switch(Page)
					{
						case 1:return 2;break;
						case 2:return 3;break;
						case 3:return 4;break;
						case 4:return 5;break;
						case 5:return 6;break;
						case 6:return 7;break;
						case 7:return 8;break;
					}
					break;
				}
				case 4:return 0;break;
				case 5:return 0;break;
			}
		}
		
		switch(Page)
			{
				case 1:OLED_ShowString(44,3,"Task1",16);break;
				case 2:OLED_ShowString(44,3,"Task2",16);break;
				case 3:OLED_ShowString(44,3,"Task3",16);break;
				case 4:OLED_ShowString(44,3,"Task4",16);break;
				case 5:OLED_ShowString(44,3,"Task5",16);break;
				case 6:OLED_ShowString(44,3,"Task6",16);break;
				case 7:OLED_ShowString(44,3,"Task7",16);break;
			}
	}
}