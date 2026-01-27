#ifndef __MOTOR_PID_H__
#define __MOTOR_PID_H__

extern int last_error;

int Get_Error();
void PID_Control_Loop();

#endif