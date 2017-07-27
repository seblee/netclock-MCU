#ifndef __INITIAL_H__
#define __INITIAL_H__
#include "type_def.h"
/***********************************************************************/
/*  FILE        :initial.h                                             */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
/***********************ϵͳԤ����**********************/
#define UINT8 unsigned char
#define INT8 char
#define UINT16 unsigned int
#define INT16 int
#define UINT32 unsigned long
#define INT32 long

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define _NOP() asm(" nop ")
#define _EI() asm(" rim ")
#define _DI() asm(" sim ")

// ������ƼĴ���1��1=�����0=���룩
#define Input 0
#define Output 1
/*******************ϵͳԤ����  end**********************/

typedef union {
  UINT32 whole_reg;
  UINT8 byte[4]; // Warning: Be endian-specific when accessing bytes

} ADF70XX_REG_T;

typedef union { // ID No.
  UINT32 IDL;
  UINT8 IDB[4];
} uni_rom_id;

extern u16 X_COUNT;
extern u16 X_ERR; //��¼����ĸ���

void LED_GPIO_Init(void);      //��ʼ��LED
void LCD_GPIO_Init(void);      //��ʼ��LCD IO
void KEY_GPIO_Init(void);      //KEY IO
void CG2214M6_GPIO_Init(void); //CG2214M6 IO
void ADF7030_GPIO_INIT(void);  //ADF7030 IO(REST & GPIO3)
u8 KEY_SCAN(u8 mode);          //����ɨ��
void RAM_clean(void);          // ���RAM
void VHF_GPIO_INIT(void);      // CPU�˿�����
void SysClock_Init(void);      // ϵͳʱ�ӣ��ⲿʱ�ӣ�
void beep_init(void);
void Delayus(unsigned char timer);
void WDT_init(void);
void ClearWDT(void);
void RF_BRE_Check(void);
void LEDCtr(u8 keyval);

#endif
