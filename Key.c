#include <REGX52.H>
#include "Delay.h"
#include "Timer2.h"

unsigned char Key_KeyNumber;

unsigned char Key()
{
	unsigned char Temp=0;
	Temp=Key_KeyNumber;
	Key_KeyNumber=0;
	return Temp;
}

unsigned char Key_GetState()
{
	unsigned char KeyNumber=0;
	
	if(P2_4==0) KeyNumber=1;
	if(P2_3==0) KeyNumber=2;
	if(P2_2==0) KeyNumber=3;
	if(P2_1==0) KeyNumber=4;
	if(P2_0==0) KeyNumber=5;
	
	return KeyNumber;
}

void Key_Loop()
{
	static unsigned char NowState,LastState;
	LastState=NowState;
	NowState=Key_GetState();
	
	if(LastState==1&&NowState==0) Key_KeyNumber=1;
	if(LastState==2&&NowState==0) Key_KeyNumber=2;
	if(LastState==3&&NowState==0) Key_KeyNumber=3;
	if(LastState==4&&NowState==0) Key_KeyNumber=4;
	if(LastState==5&&NowState==0) Key_KeyNumber=5;
}

void Timer2_Routine() interrupt 5
{
	static unsigned int T2Count;
	T2Count++;
	TF2 = 0;
	if(T2Count>=100)
	{
		T2Count=0;
		Key_Loop();
	}
}