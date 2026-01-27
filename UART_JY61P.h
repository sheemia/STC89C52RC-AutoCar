#ifndef __UART_JY61P_H__
#define __UART_JY61P_H__

void UART_Init();              // 初始化串口
short Get_Raw_Yaw();           // 获取原始Yaw值 (-32768 ~ 32767)
void Reset_Yaw_Reference();    // 重置参考点
short Get_Relative_Yaw();      // 获取相对于重置点的偏差值

#endif