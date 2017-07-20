#ifndef __LCD_H__
#define __LCD_H__
/***********************************************************************/
/*  FILE        :lcd.h                                                 */
/*  DATE        :Mar, 2014                                             */
/*  Programmer	:xiang 'R                                              */
/*  CPU TYPE    :STM8L151G6     Crystal: 16M HSI                       */
/*  DESCRIPTION :                                                      */
/*  Mark        :ver 1.0                                               */
/***********************************************************************/
extern u8 LCDFirstDisplayFlag;
extern u8 LCDUpdateIDFlag;

void lcd_init(void);
void send_command(u8 data);
void send_data(u8 data);
void delay(u16 i);
void display_map_xy(unsigned char x, unsigned char y, unsigned char l, unsigned char h, const unsigned char *p);
void display_map_58_6(unsigned char x, unsigned char y, unsigned char len, const unsigned char *p);
void lcd_clear(unsigned char data1);
void lcd_desplay(void);
void LCD_display_argos_rssi(unsigned int m);
void LCDTestDisplay(void);

extern const unsigned char char_Large_L11_H24[];
extern const unsigned char char_ID[];
extern const unsigned char char_ID_CHECKER[];
extern const unsigned char char_company[];

extern const unsigned char char_Small[];
extern const unsigned char char_Medium[];
extern const unsigned char char_Contro[];
extern const unsigned char char_RSSI[];
extern const unsigned char char_Medium[];

#endif
