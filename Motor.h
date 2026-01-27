#ifndef __MOTOR_H__
#define __MOTOR_H__

extern unsigned char speedA;
extern unsigned char speedB;
extern unsigned char pwmCount;
extern unsigned char Base_Speed;

void MotorA_Forward(void);
void MotorA_Backward(void);
void MotorA_Brake(void);
void MotorA_Stop(void);
void MotorB_Forward(void);
void MotorB_Backward(void);
void MotorB_Brake(void);
void MotorB_Stop(void);
void Motor_Init();

#endif