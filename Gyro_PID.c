#include <REGX52.H>
#include "Motor.h"
#include "UART_JY61P.h"
#include "Driving.h"

int Gyro_Z_Raw;

//陀螺仪直线 PID 专用参数
// 使用整数运算优化性能
int Gyro_Kp_Mult = 3;    // P 分子
int Gyro_Kd_Mult = 25;   // D 分子
int Gyro_Divisor = 1000;  // 公共分母

// 陀螺仪 PID 过程变量
static short idata gyro_last_error = 0;

// 重置陀螺仪PID状态
void Reset_Gyro_PID()
{
    gyro_last_error = 0;
    Reset_Yaw_Reference();
}

//陀螺仪直线 PID 控制循环
void PID_Gyro_Straight_Loop()
{
    short error;
    long p_term, d_term;
    char pid_output;
    char final_speed_L, final_speed_R;

    //获取误差
    error = 0 - Get_Relative_Yaw(); 

    //计算 P 项
    p_term = (long)error * Gyro_Kp_Mult;

    //计算 D 项
    d_term = (long)(error - gyro_last_error) * Gyro_Kd_Mult;

    //计算总输出
    pid_output = (int)((p_term + d_term) / Gyro_Divisor);

    //更新历史误差
    gyro_last_error = error;

    //输出限幅
    if(pid_output > 45) pid_output = 45;
    if(pid_output < -45) pid_output = -45;

    //执行电机控制
    final_speed_L = Base_Speed - pid_output;
    final_speed_R = Base_Speed + pid_output;

    Motor_Set(final_speed_L, final_speed_R);
}