/***********************************************************************/
/*  FILE        :Uart.c                                                */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
//#include <iostm8l151g4.h> // CPU型号
#include <iostm8l052c6.h> // CPU型号
#include "Pin_define.h"   // 管脚定义
#include "initial.h"	  // 初始化  预定义
#include "elanddata.h"
#include "uart.h"
#define TXD1_enable (USART1_CR2 = 0x08) // 允许发送
#define RXD1_enable (USART1_CR2 = 0x24) // 允许接收及其中断
//********************************************
void UART1_INIT(void)
{
    unsigned int baud_div = 0;
	USART1_CR1 = 1; // 1个起始位,8个数据位
	USART1_CR3 = 0; // 1个停止位
	USART1_CR4 = 0;
	USART1_CR5 = 0x00; //0x08;						// 半双工模式

	//USART1_BRR2 = 0x03; // 设置波特率9600
	//USART1_BRR1 = 0x68; // 3.6864M/9600 = 0x180
	//16.00M/9600 = 0x683

	//USART1_BRR2 = 0x01; // 设置波特率38400
	//USART1_BRR1 = 0xa1; // 16.00M/38400 = 0x1a1


    	/*设置波特率*/
	baud_div = 16000000 / 57600; /*求出分频因子*/
	USART1_BRR2 = baud_div & 0x0f;
	USART1_BRR2 |= ((baud_div & 0xf000) >> 8);
	USART1_BRR1 = ((baud_div & 0x0ff0) >> 4); /*先给BRR2赋值 最后再设置BRR1*/


	//USART1_CR2 = 0x08;	// 允许发送
	USART1_CR2 = 0x24;


    Send_String("12345632adf{}");
}
void UART1_end(void)
{ //
	//SYSCFG_RMPCR1_USART1TR_REMAP=0;
	USART1_CR1 = 0; // 1个起始位,8个数据位
	USART1_CR3 = 0; // 1个停止位
	USART1_CR4 = 0;
	USART1_CR5 = 0x00;  // 半双工模式
	USART1_BRR2 = 0x00; // 设置波特率9600
	USART1_BRR1 = 0x00; // 3.6864M/9600 = 0x180
						//16.00M/9600 = 0x683
	USART1_CR2 = 0x00;  //禁止串口
}
//--------------------------------------------
void UART1_RX_RXNE(void)
{ // RXD中断服务程序
	unsigned char dat;
	dat = USART1_DR; // 接收数据
	ReceiveFromEland(dat);
	//Send_char(dat);
}

//--------------------------------------------
void Send_char(unsigned char ch)
{				 // 发送字符
	TXD1_enable; // 允许发送
	while (!USART1_SR_TXE)
		;
	USART1_DR = ch; // 发送
	while (!USART1_SR_TC)
		;		 // 等待完成发送
	RXD1_enable; // 允许接收及其中断
}
//--------------------------------------------
void Send_String(unsigned char *string)
{ // 发送字符串
	unsigned char i = 0;
	TXD1_enable; // 允许发送
	while (string[i])
	{
		while (!USART1_SR_TXE)
			;				   // 检查发送OK
		USART1_DR = string[i]; // 发送
		i++;
	}
	while (!USART1_SR_TC)
		;		 // 等待完成发送
	RXD1_enable; // 允许接收及其中断
				 //	BIT_SIO = 0;							// 标志
}

/***********************************************************************/
unsigned char asc_hex(unsigned char asc) // HEX
{
	unsigned char i;
	if (asc < 0x3A)
		i = asc & 0x0F;
	else
		i = asc - 0x37;
	return i;
}

unsigned char hex_asc(unsigned char hex)
{
	unsigned char i;
	hex = hex & 0x0F;
	if (hex < 0x0A)
		i = hex | 0x30;
	else
		i = hex + 0x37;
	return i;
}

unsigned char asc_hex_2(unsigned char asc1, unsigned char asc0)
{
	unsigned char i;
	i = (asc_hex(asc1) << 4) + (asc_hex(asc0) & 0x0F);
	return i;
}
