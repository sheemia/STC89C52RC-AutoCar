#include <REGX52.H>

// 接收缓冲区
unsigned char idata Re_buf[11];
unsigned char counter = 0;

volatile short Raw_Yaw = 0;       
short Raw_Yaw_Offset = 0; // 初始偏差值

void UART_Init()
{
	// 配置波特率 9600 (晶振 11.0592MHz)
	TMOD |= 0x20;   // 定时器1 模式2 (8位自动重装)
	PCON &= 0x7F;   // 波特率不倍增
	SCON = 0x50;    // 模式1，允许接收
	TH1 = 0xFD;     
	TL1 = 0xFD;
	TR1 = 1;        // 启动定时器1
	ES = 1;         // 开串口中断
	EA = 1;         // 开总中断
}

// 读取当前的原始值
short Get_Raw_Yaw()
{
	return Raw_Yaw;
}

// 记录当前的朝向作为“0点”
void Reset_Yaw_Reference()
{
	Raw_Yaw_Offset = Raw_Yaw;
}

// 获取相对偏差 (这就是 PID 的输入 Error)
short Get_Relative_Yaw()
{
	return Raw_Yaw - Raw_Yaw_Offset;
}

// 串口中断接收
void UART_Routine() interrupt 4
{
	unsigned char i, check_sum;
	
	if (RI)
	{
		RI = 0;
		if (counter == 0 && SBUF != 0x55) return; // 检查
		
		Re_buf[counter] = SBUF;
		counter++;
		
		if (counter == 11)
		{
			counter = 0;
			// 校验和
			check_sum = 0;
			for(i=0; i<10; i++) check_sum += Re_buf[i];
			
			if(check_sum == Re_buf[10])
			{
				// 0x53 是角度包
				if(Re_buf[1] == 0x53)
				{
					//合成 short
					Raw_Yaw = (short)((Re_buf[7]<<8) | Re_buf[6]);
				}
			}
		}
	}
}