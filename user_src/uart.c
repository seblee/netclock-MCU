/***********************************************************************/
/*  FILE        :Uart.c                                                */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
//#include <iostm8l151g4.h> // CPU�ͺ�
#include <iostm8l052c6.h> // CPU�ͺ�
#include "Pin_define.h"   // �ܽŶ���
#include "initial.h"	  // ��ʼ��  Ԥ����
#include "elanddata.h"
#include "uart.h"
#define TXD1_enable (USART1_CR2 = 0x08) // ������
#define RXD1_enable (USART1_CR2 = 0x24) // ������ռ����ж�
//********************************************
void UART1_INIT(void)
{
    unsigned int baud_div = 0;
	USART1_CR1 = 1; // 1����ʼλ,8������λ
	USART1_CR3 = 0; // 1��ֹͣλ
	USART1_CR4 = 0;
	USART1_CR5 = 0x00; //0x08;						// ��˫��ģʽ

	//USART1_BRR2 = 0x03; // ���ò�����9600
	//USART1_BRR1 = 0x68; // 3.6864M/9600 = 0x180
	//16.00M/9600 = 0x683

	//USART1_BRR2 = 0x01; // ���ò�����38400
	//USART1_BRR1 = 0xa1; // 16.00M/38400 = 0x1a1


    	/*���ò�����*/
	baud_div = 16000000 / 57600; /*�����Ƶ����*/
	USART1_BRR2 = baud_div & 0x0f;
	USART1_BRR2 |= ((baud_div & 0xf000) >> 8);
	USART1_BRR1 = ((baud_div & 0x0ff0) >> 4); /*�ȸ�BRR2��ֵ ���������BRR1*/


	//USART1_CR2 = 0x08;	// ������
	USART1_CR2 = 0x24;


    Send_String("12345632adf{}");
}
void UART1_end(void)
{ //
	//SYSCFG_RMPCR1_USART1TR_REMAP=0;
	USART1_CR1 = 0; // 1����ʼλ,8������λ
	USART1_CR3 = 0; // 1��ֹͣλ
	USART1_CR4 = 0;
	USART1_CR5 = 0x00;  // ��˫��ģʽ
	USART1_BRR2 = 0x00; // ���ò�����9600
	USART1_BRR1 = 0x00; // 3.6864M/9600 = 0x180
						//16.00M/9600 = 0x683
	USART1_CR2 = 0x00;  //��ֹ����
}
//--------------------------------------------
void UART1_RX_RXNE(void)
{ // RXD�жϷ������
	unsigned char dat;
	dat = USART1_DR; // ��������
	ReceiveFromEland(dat);
	//Send_char(dat);
}

//--------------------------------------------
void Send_char(unsigned char ch)
{				 // �����ַ�
	TXD1_enable; // ������
	while (!USART1_SR_TXE)
		;
	USART1_DR = ch; // ����
	while (!USART1_SR_TC)
		;		 // �ȴ���ɷ���
	RXD1_enable; // ������ռ����ж�
}
//--------------------------------------------
void Send_String(unsigned char *string)
{ // �����ַ���
	unsigned char i = 0;
	TXD1_enable; // ������
	while (string[i])
	{
		while (!USART1_SR_TXE)
			;				   // ��鷢��OK
		USART1_DR = string[i]; // ����
		i++;
	}
	while (!USART1_SR_TC)
		;		 // �ȴ���ɷ���
	RXD1_enable; // ������ռ����ж�
				 //	BIT_SIO = 0;							// ��־
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
