#ifndef __RAM_H__
#define __RAM_H__
//CPU?????
//?????ADF030???????
//#define TX_TEST_CARRIER_MODE 0
#include "initial.h"		// 初始化  预定义

extern uFLAG FLAG_test1;
	//************************************************
	#define 	FLAG_test1_BYTE		FLAG_test1.BYTE
	//------------------------------------------------
    #define		BIT_SIO          	FLAG_test1.BIT.Bit0
    #define		FG_auto_out	        FLAG_test1.BIT.Bit1
    #define		FG_OUT_OPEN_CLOSE	FLAG_test1.BIT.Bit2    //历史记录   误码率测试用
//    #define		FG_auto_outbz		FLAG_test1.BIT.Bit3
    #define		FG_auto_open_time	FLAG_test1.BIT.Bit4
    #define		FG_auto_manual_mode	FLAG_test1.BIT.Bit5      //1=auto,0=manual
    #define		FG_Receiver_LED_RX	FLAG_test1.BIT.Bit6
    #define		FG_First_auto		FLAG_test1.BIT.Bit7
	//************************************************

extern UINT8 SIO_cnt;
extern UINT8 SIO_buff[16];
extern UINT8 SIO_DATA[16];


extern UINT8  TIME_10ms;
extern UINT16 TIMER1s;
extern UINT16 TIMER300ms;
extern UINT16 TIMER18ms;
extern UINT8  TIMER250ms_STOP;
extern UINT16 TIME_auto_out;
extern UINT16 TIME_auto_close;
extern UINT16 time_3sec;
extern UINT32 ID_Receiver_DATA[256];//写入EEPROM ID的数据
extern UINT16 ID_DATA_PCS;
extern u8 Count_key_SW3;
extern u8 Display_key_SW3;

/**********LCD******************/
extern uFLAG FlagLCDUpdate;

#define LCDUpdateIDFlag             FlagLCDUpdate.BIT.Bit0
#define LCDUpdateRISSFlag           FlagLCDUpdate.BIT.Bit1
#define LCDFirstDisplayFlag         FlagLCDUpdate.BIT.Bit2
/**********RSSI*********************/
extern u16 LCDRSSI;
extern u8 RAM_RSSI_AVG;


#define SPI_SEND_BUFF_LONG  	300
#define SPI_REV_BUFF_LONG  		40

extern const u8 ADF7030Cfg[];
u32 CFG_SIZE(void);

#define OPEN_LONG 12
extern UINT8  CONST_TXPACKET_DATA_20000AF0[OPEN_LONG];


extern u32 GENERIC_PKT_TEST_MODES0_32bit_20000548;
extern const u8 TEST_MODES0_para[5];
extern u32 RADIO_DIG_TX_CFG0_32bit_20000304;
#define AFCCONFIG_LONG 4
extern const u8 CONST_AFC_Configuration_400041F8[4];
extern u16 PA_POWER_OUT[2][18];


void SPI_INIT(void);
UINT32 ADF7030_GET_MISC_FW(void);//??MISC_FW?????
void ADF7030_WRITING_PROFILE_FROM_POWERON(void);
void ADF7030_TRANSMITTING_FROM_POWEROFF(void);
void ADF7030_RECEIVING_FROM_POWEROFF(void);
void SCAN_RECEIVE_PACKET(void);
u32 ConfigurationLen(void);



#endif


