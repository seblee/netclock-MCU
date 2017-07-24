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

#define TXD1_enable (USART1_CR2 = 0x08) // ������
#define RXD1_enable (USART1_CR2 = 0x24) // ������ռ����ж�
//********************************************
void UART1_INIT(void)
{
	USART1_CR1 = 0; // 1����ʼλ,8������λ
	USART1_CR3 = 0; // 1��ֹͣλ
	USART1_CR4 = 0;
	USART1_CR5 = 0x00;  //0x08;						// ��˫��ģʽ
	USART1_BRR2 = 0x03; // ���ò�����9600
	USART1_BRR1 = 0x68; // 3.6864M/9600 = 0x180
						//16.00M/9600 = 0x683
						//USART1_CR2 = 0x08;	// ������
	USART1_CR2 = 0x24;
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

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void PC_PRG(void) // ��������
{

	//	unsigned int  i,j;
	//unsigned char  d3,d2,d1,d0;
	/*
	if (BIT_SIO){
		BIT_SIO = 0;
		//SIO_TOT = 20;
		switch (SIO_DATA[1]){
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%                 д����               %
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		case 'W':
			//==================================== ADF7012
			if (SIO_DATA[2]=='I')				// (WIxd0d1d2d3)
			{
			        i = asc_hex_2(0x30,SIO_buff[3]);
				d0 = asc_hex_2(SIO_buff[4],SIO_buff[5]);
				d1 = asc_hex_2(SIO_buff[6],SIO_buff[7]);
				d2 = asc_hex_2(SIO_buff[8],SIO_buff[9]);
				d3 = asc_hex_2(SIO_buff[10],SIO_buff[11]);

	                        //write Rx
                                ROM_adf7012_value[i].byte[0] = d0;
				ROM_adf7012_value[i].byte[1] = d1;
				ROM_adf7012_value[i].byte[2] = d2;
				ROM_adf7012_value[i].byte[3] = d3;
                                dd_write_7021_reg(&ROM_adf7012_value[i].byte[0]);
                                Delayus(122);		//delay 40us

				//-------------------------------- ����
				if(i==1){
				     j=0x380+i*4;
				     UnlockFlash( UNLOCK_EEPROM_TYPE );
				     WriteByteToFLASH(addr_eeprom_sys+j,d0);
				     WriteByteToFLASH(addr_eeprom_sys+j+1,d1);
				     WriteByteToFLASH(addr_eeprom_sys+j+2,d2);
				     WriteByteToFLASH(addr_eeprom_sys+j+3,d3);
				     LockFlash( UNLOCK_EEPROM_TYPE );

				     ClearWDT(); // Service the WDT
				}
				//-------------------------------����  (WHx)
				d1 = '(';
				d2 = 'W';
				Send_char(d1);
				Send_char(d2);
				d1 = 'I';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
				Send_char(SIO_buff[3]);

			}

			//==================================== ADF7012 TX/RX����
			if (SIO_DATA[2]=='J')				// (WJx)
			{
			        Tx_Rx_mode = asc_hex_2(0x30,SIO_buff[3]);
				//-------------------------------����  (WHx)
				d1 = '(';
				d2 = 'W';
				Send_char(d1);
				Send_char(d2);
				d1 = 'J';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
				Send_char(SIO_buff[3]);

			}
		        break;
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//%                 ������               %
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		case 'R':
			//==================================== ADF7012   //(RIx)
			if (SIO_DATA[2]=='I')				// (RI)d0d1d2d3
			{
			        i = asc_hex_2(0x30,SIO_buff[3]);
			  	d1 = '(';
				d2 = 'R';
				Send_char(d1);
				Send_char(d2);
				d1 = 'I';
				d2 = ')';
				Send_char(d1);
				Send_char(d2);
				for (j=0;j<4;j++){
			  	   d1 = hex_asc(ROM_adf7012_value[i].byte[j] / 16);
				   d2 = hex_asc(ROM_adf7012_value[i].byte[j] % 16);
				   Send_char(d1);
				   Send_char(d2);
				}
                        }
		        break;
		default:
			break;

		}
	}
*/
}
