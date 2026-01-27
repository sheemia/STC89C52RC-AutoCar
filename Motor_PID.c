#include <REGX52.H>
#include "Motor.h"
#include "GrayscaleSensor.h"
#include "Driving.h"

//PID 核心参数
char Kp = 4;  // P: 反应力度 (越大转向越猛)
char Ki = 0;   // I: 消除静差 (巡线通常设为0，除非走很慢)
char Kd = 25;  // D: 抑制震荡 (越大越平滑，但太大电机抖动)

// PID 过程变量
int last_error = 0;   // 上一次误差
int integral = 0;   // 积分累计

//获取误差
int Get_Error() 
{
    val = GrayscaleSensor_ReadByte();
    val = ~val; 

    if (val == 0) return last_error; 

    //急弯
    if ((val & 0xE0) == 0xE0 && (val & 0x01) == 0) return 80; 
    if ((val & 0x07) == 0x07 && (val & 0x80) == 0) return -80; 

    //普通巡线
    if (val & 0x80) return 30;   
    if (val & 0x01) return -30;  

    if (val & 0x40) return 20;   
    if (val & 0x02) return -20;  

    if (val & 0x20) return 10;   
    if (val & 0x04) return -10;  

    //轻微偏离
    if (val & 0x10) return 5;   
    if (val & 0x08) return -5;  

    // 直行
    if (val & 0x18) return 0;   

    return last_error;
}

void PID_Control_Loop() 
{
    int error;
    int P, I, D;
    int pid_out_temp; // 临时存储放大后的PID结果
    char pid_out;     // 最终输出给电机
    
    // 获取误差
    error = Get_Error();
    
    // 计算 P
    P = Kp * error;
    
    // 计算 I
    integral += error;
    if (integral > 1000) integral = 1000;
    if (integral < -1000) integral = -1000;
    I = Ki * integral;
    
    // 计算 D
    D = Kd * (error - last_error);
    
    // 计算总输出
    pid_out_temp = P + I + D;
    
    //比例还原
    pid_out = (char)(pid_out_temp / 10);
    
    // 更新历史误差
    last_error = error;
    
    // 执行电机控制
    Motor_Set(Base_Speed + pid_out, Base_Speed - pid_out);
}