#include <REGX52.H>
#include <INTRINS.H>

sbit I2C_SDA=P0^1;
sbit I2C_SCL=P0^2;

void Delay5us()		//@11.0592MHz
{
	_nop_(); _nop_();
}

/**
  * @brief  I2C Start.
  * @param  None
  * @retval None
  */
void I2C_Start()
{
	I2C_SDA=1;
	I2C_SCL=1;
	Delay5us();
	I2C_SDA=0;
	Delay5us();
	I2C_SCL=0;
}

/**
  * @brief  I2C Stop.
  * @param  None
  * @retval None
  */
void I2C_Stop()
{
	I2C_SDA=0;
	I2C_SCL=1;
	Delay5us();
	I2C_SDA=1;
	Delay5us();
}

/**
  * @brief  Send a byte via I2C.
  * @param  Byte: Byte to be sent.
  * @retval None.
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;
		Delay5us();
		I2C_SCL=0;
		Delay5us();
	}
}

/**
  * @brief  I2C Receive one byte.
  * @param  None.
  * @retval One byte of data recieve.
  */
unsigned char I2C_ReceiveByte()
{
	unsigned char i,Byte=0x00;
	I2C_SDA=1;
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
		Delay5us();
		if(I2C_SDA) Byte|=(0x80>>i);
		I2C_SCL=0;
		Delay5us();
	}
	return Byte;
}

/**
  * @brief  I2C sends acknowledgement.
	* @param  AckBit: Acknowledgement bit, 0 indicates acknowledgement, 1 indicates no acknowledgement.
  * @retval None.
  */
void I2C_SendAck(unsigned char AckBit)
{
	I2C_SDA=AckBit;
	I2C_SCL=1;
	I2C_SCL=0;
}

/**
  * @brief  I2C receive acknowledgement bit.
  * @param  None.
  * @retval The acknowledgement bit received, 0 indicates acknowledgement, 1 indicates no acknowledgement.
  */
unsigned char I2C_ReceiveAck()
{
	unsigned char AckBit=0;
	I2C_SDA=1;
	I2C_SCL=1;
	Delay5us();
	AckBit=I2C_SDA;
	I2C_SCL=0;
	Delay5us();
	return AckBit;
}