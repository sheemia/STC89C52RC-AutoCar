#include <REGX52.H>

/**
  * @brief  Timer2 initialization,1ms@11.0592MHz.
  * @param  none
  * @retval none
  */

void Timer2Init()
{
	T2MOD = 0;		//初始化模式寄存器
	T2CON = 0;		//初始化控制寄存器
	TL2 = 0x66;		//设置定时初值
	TH2 = 0xFC;		//设置定时初值
	RCAP2L = 0x66;		//设置定时重载值
	RCAP2H = 0xFC;		//设置定时重载值
	TR2 = 1;		//定时器2开始计时
	ET2=1;
	EA=1;
	PT2=0;
}

/*Timer interrupt function template.
void Timer2_Routine() interrupt 5
{
	static unsigned int T0Count;
	TL2 = 0x18;
	TH2 = 0xFC;
	T2Count++;
	if(T2Count==1000)
	{
		T2Count=0;
		
	}
}
*/