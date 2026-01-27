#include <REGX52.H>
#include "I2C.h"

#define GRAYSCALESENSOR_ADDRESS 0x98

char val;

unsigned char GrayscaleSensor_ReadByte()
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(GRAYSCALESENSOR_ADDRESS);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(GRAYSCALESENSOR_ADDRESS|0x01);
	I2C_ReceiveAck();
	Data=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}

//更新val
void Get_NewVal()
{
	val = GrayscaleSensor_ReadByte();
	val = ~val;
}