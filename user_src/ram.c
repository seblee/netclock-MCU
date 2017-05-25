#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
#include <stdbool.h>        /* For true/false definition                      */
//#include "initial.h"		// 初始化  预定义
#include "type_def.h"

uFLAG FLAG_test1;

u8 SIO_cnt;
u8 SIO_buff[16];
u8 SIO_DATA[16];

u8  TIME_10ms=0;
u16  TIMER1s=0;
u16  TIMER300ms=0;
u16  TIMER18ms=0;
u8   TIMER250ms_STOP=0;
u16  TIME_auto_out=0;
u16  TIME_auto_close=0;
u16  time_3sec=0;
u32 ID_Receiver_DATA[256] = {0};//写入EEPROM ID的数据
u16 ID_DATA_PCS=0;

u8 Count_key_SW3 = 0;
u8 Display_key_SW3 = 0xff;


/*******LCD**************/
uFLAG FlagLCDUpdate = {0xff};
///**********RSSI*********************/
u16 LCDRSSI = 0;
u8 RAM_RSSI_AVG = 0;

const u8 ADF7030Cfg[] = {
#include "Settings_ADF7030-1.cfg"
};
/**
****************************************************************************
* @Function : u32 CFG_SIZE(void)
* @File     : ram.c
* @Program  :
* @Created  : 2017/4/24 by Xiaowine
* @Brief    :
* @Version  : V1.0
**/
u32 CFG_SIZE(void)
{
    return sizeof(ADF7030Cfg);
}
u8  CONST_TXPACKET_DATA_20000AF0[12]=
{
    0X95,0X55,0X55,0X55,
    0X55,0X55,0X56,0X55,
    0X95,0X55,0X56,0X55
};
u32 GENERIC_PKT_TEST_MODES0_32bit_20000548 = 0x00000000;
const u8 TEST_MODES0_para[5] = {0,1,2,4,6};
u32 RADIO_DIG_TX_CFG0_32bit_20000304 = 0x8838287e;
u16 PA_POWER_OUT[2][18] =
{
    {0x0382,0x02a3,0x02f3,0x0353,0x02d4,
     0x0295,0x02e5,0x02b6,0x0316,0x0376,
     0x03c6,0x0486,0x0536,0x05f6,0x05f6,
     0x05f6,0x05f6,0x05f6},
    {0x0382,0x02a3,0x02f3,0x0353,0x02d4,
     0x0295,0x02e5,0x02b6,0x02a7,0x0298,
     0x02a9,0x02aa,0x031a,0x037a,0x040a,
     0x04aa,0x057a,0x069a}
};
const u8 CONST_AFC_Configuration_400041F8[4]=
{
    0x00,0x00,0x00,0x00  /*20000304*/
};

const u8 CONST_PROFILE_CCA_CFG_20000378[4]=
{
    0x43,0x00,0xC0,0x06  /*20000304*/
};




