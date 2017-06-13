/***********************************************************************/
/*  FILE        :eeprom.c                                              */
/*  DATE        :June, 2011                                            */
/*  DESCRIPTION :routine for VHF60-2011                                */
/*  CPU TYPE    :STM8S207C8                                            */
/*  Programmer	:Gong Dong Sheng                                       */
/*  Mark        :STM8S207C8��CODE�ռ�Ϊ64K                             */
/*              :STM8S207C8��EEPROM�Ĵ�СΪ1536�ֽ�,��:3ҳ,512��/ҳ    */
/***********************************************************************/
#include <iostm8l151g4.h> // CPU�ͺ�
//#include "stm8l15x.h"
#include "Pin_define.h" // �ܽŶ���
//#include "initial.h"		// ��ʼ��  Ԥ����
#include "ram.h"    // RAM����
#include "eeprom.h" // eeprom
#include "ID_Decode.h"
/***********************************************************************/
/*                    FLASH & EEPROM �Ĵ���������λ                    */
/***********************************************************************/
#define FIRST_SECURITY_KEY 0xAE
#define SECOND_SECURITY_KEY 0x56
#define ADD_EEPROM_S8 0x1000

///* FLASH_CR2 */
//#define OPT               7   /* ��ѡ���ֽڽ���д���� */
//#define WPRG              6   /* �ֱ��� */
//#define ERASE             5   /* ������ */
//#define FPRG              4   /* ���ٿ����� */
////#define NC              3
////#define NC              2
////#define NC              1
//#define PRG               0   /* ��׼������ */
//
///* FLASH_NCR2 */
//#define NOPT              7   /* ��ѡ���ֽڽ���д���� */
//#define NWPRG             6   /* �ֱ��� */
//#define NERASE            5   /* ������ */
//#define NFPRG             4   /* ���ٿ����� */
////#define NC              3
////#define NC              2
////#define NC              1
//#define NPRG              0   /* ��׼������ */
//
///* FLASH_FPR */
////#define NC              7
////#define NC              6
//#define WPB5              5   /* �û��������뱣��λ */
//#define WPB4              4
//#define WPB3              3
//#define WPB2              2
//#define WPB1              1
//#define WPB0              0
//
///* FLASH_NFPR */
////#define NC              7
////#define NC              6
//#define NWPB5             5   /* �û��������뱣��λ */
//#define NWPB4             4
//#define NWPB3             3
//#define NWPB2             2
//#define NWPB1             1
//#define NWPB0             0
//
///* FLASH_PUKR */
//#define MASS_PRG_KEY7     7   /* �������洢��������Կ */
//#define MASS_PRG_KEY6     6
//#define MASS_PRG_KEY5     5
//#define MASS_PRG_KEY4     4
//#define MASS_PRG_KEY3     3
//#define MASS_PRG_KEY2     2
//#define MASS_PRG_KEY1     1
//#define MASS_PRG_KEY0     0
//
///* FLASH_DUKR */
//#define MASS_DATA_KEY7    7   /* DATA EEPROM������Կ */
//#define MASS_DATA_KEY6    6
//#define MASS_DATA_KEY5    5
//#define MASS_DATA_KEY4    4
//#define MASS_DATA_KEY3    3
//#define MASS_DATA_KEY2    2
//#define MASS_DATA_KEY1    1
//#define MASS_DATA_KEY0    0
//
/* FLASH_IAPSR */
//#define NC              7
#define HVOFF 6 /* 高压结束标志 */
//#define NC              5
//#define NC              4
#define DUL 3       /* DATA EEPROM区域解锁标志 */
#define EOP 2       /* 编程结束(写或擦除操作)标志 */
#define PUL 1       /* �?速程序存储器结束标志 */
#define WR_PG_DIS 0 /* 试图向�??保护页进行写操作的标�? */

#define FLASH_CR1_RESET_VALUE ((uchar)0x00)
#define FLASH_CR2_RESET_VALUE ((uchar)0x00)
#define FLASH_NCR2_RESET_VALUE ((uchar)0xFF)
#define FLASH_IAPSR_RESET_VALUE ((uchar)0x40)
#define FLASH_PUKR_RESET_VALUE ((uchar)0x00)
#define FLASH_DUKR_RESET_VALUE ((uchar)0x00)

#define FLASH_PUKR_PUK ((uchar)0xFF) /*!< Flash Program memory unprotection mask */
#define FLASH_DUKR_DUK ((uchar)0xFF) /*!< Data EEPROM unprotection mask */

//#define UNLOCK_FLASH_TYPE       (( uchar )0x00 )
//#define UNLOCK_EEPROM_TYPE      (( uchar )0x01 )

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void InitialFlashReg(void)
{ // 初�?�化�?存寄存器�?
    FLASH_CR1 = FLASH_CR1_RESET_VALUE;
    FLASH_CR2 = FLASH_CR2_RESET_VALUE;
    //FLASH_NCR2 = FLASH_NCR2_RESET_VALUE;
    FLASH_IAPSR &= (uchar)(~(1 << DUL)); // 清除�?读DATA区解�?
    FLASH_IAPSR &= (uchar)(~(1 << PUL)); // 清除程序区解�?
}
//------------------------------------------------
//  �?: 2�?密钥的操作序列�?�好相反
void UnlockFlash(unsigned char Type)
{ // 解锁flash
    if (Type == UNLOCK_FLASH_TYPE)
    { // 解锁程序�?
        FLASH_DUKR = SECOND_SECURITY_KEY;
        FLASH_DUKR = FIRST_SECURITY_KEY;
    }
    else
    { // 解锁eeprom
        FLASH_DUKR = FIRST_SECURITY_KEY;
        FLASH_DUKR = SECOND_SECURITY_KEY;
    }
}
//------------------------------------------------
void LockFlash(unsigned char Type)
{ // 锁定存储�?
    if (Type == UNLOCK_FLASH_TYPE)
    {
        FLASH_IAPSR &= ~(1 << PUL);
    }
    else
    {
        FLASH_IAPSR &= ~(1 << DUL);
    }
}
//------------------------------------------------
uchar ReadByteEEPROM(ulong Addr)
{                                    // 从eeprom�?读取1字节
    return (*((__far uchar *)Addr)); // Read byte
}
//------------------------------------------------
void WriteByteToFLASH(ulong Addr, uchar Dat)
{ // 写入一字节到eeprom
    *((__far uchar *)Addr) = Dat;
}
//------------------------------------------------
void EraseByteFLASH(uint Addr)
{ // 擦除eeprom�?内�??
    *((__near uchar *)Addr) = 0x00;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void eeprom_save(void)
{
    unsigned char i, eeprom_sys_buff;

    UnlockFlash(UNLOCK_EEPROM_TYPE);
    for (i = 0; i < 16; i++)
        WriteByteToFLASH(addr_eeprom_sys + i, eeprom_sys_buff);
    LockFlash(UNLOCK_EEPROM_TYPE);
}
void eeprom_sys_load(void)
{
    UINT16 i, j, q, p;
    UINT8 xm[3] = {0};
    uni_rom_id xn;
    for (i = 0; i < 256; i++)
        ID_Receiver_DATA[i] = 0;
    xm[0] = ReadByteEEPROM(addr_eeprom_sys + 0x3FE);
    xm[1] = ReadByteEEPROM(addr_eeprom_sys + 0x3FF);
    ID_DATA_PCS = xm[0] * 256 + xm[1];
    if (ID_DATA_PCS == 0xFFFF)
        ID_DATA_PCS = 0;
    else if (ID_DATA_PCS > 256)
        ID_DATA_PCS = 256;
    q = ID_DATA_PCS;
    p = 0;
    for (i = 0; i < q; i++)
    {
        j = 3 * i;
        xm[0] = ReadByteEEPROM(addr_eeprom_sys + j);
        j++;
        xm[1] = ReadByteEEPROM(addr_eeprom_sys + j);
        j++;
        xm[2] = ReadByteEEPROM(addr_eeprom_sys + j);
        xn.IDB[0] = 0;
        xn.IDB[1] = xm[0];
        xn.IDB[2] = xm[1];
        xn.IDB[3] = xm[2];
        if ((xn.IDL == 0) || (xn.IDL == 0xFFFFFF))
            q++;
        else
            ID_Receiver_DATA[p++] = xn.IDL;
        if (q > 260)
            break;
        ClearWDT(); // Service the WDT
    }

    for (i = 1; i < 2; i++)
    {
        j = 0x380 + i * 4;
        //    ROM_adf7012_value[i].byte[0]= ReadByteEEPROM( addr_eeprom_sys+j );
        //    ROM_adf7012_value[i].byte[1]= ReadByteEEPROM( addr_eeprom_sys+j+1 );
        //    ROM_adf7012_value[i].byte[2]= ReadByteEEPROM( addr_eeprom_sys+j+2 );
        //    ROM_adf7012_value[i].byte[3]= ReadByteEEPROM( addr_eeprom_sys+j+3 );
        //    if((ROM_adf7012_value[i].whole_reg==0)||(ROM_adf7012_value[i].whole_reg==0xFFFFFFFF))ROM_adf7012_value[i]=Default_adf7012_value[i];
    }
}

void ALL_ID_EEPROM_Erase(void)
{
    UINT16 m2, i;
    UINT8 xm[3] = {0};
    xm[0] = 0;
    xm[1] = 0;
    xm[2] = 0;
    for (i = 0; i < 260; i++)
    {
        m2 = 3 * i;
        UnlockFlash(UNLOCK_EEPROM_TYPE);
        WriteByteToFLASH(addr_eeprom_sys + m2, xm[0]);
        m2++;
        WriteByteToFLASH(addr_eeprom_sys + m2, xm[1]);
        m2++;
        WriteByteToFLASH(addr_eeprom_sys + m2, xm[2]);
        LockFlash(UNLOCK_EEPROM_TYPE);
        ClearWDT(); // Service the WDT
    }
}
void ID_EEPROM_write(void)
{
    /*    UINT8 xm[3]={0};
    UINT16 i,j,m1;
    uni_rom_id xn,xd;
     ID_DATA_PCS++;
     xm[0]=ID_DATA_PCS%256;
     xm[1]=ID_DATA_PCS/256;

     UnlockFlash( UNLOCK_EEPROM_TYPE );
	WriteByteToFLASH( addr_eeprom_sys+0x3FE, xm[1]);
	WriteByteToFLASH( addr_eeprom_sys+0x3FF, xm[0]);
     LockFlash( UNLOCK_EEPROM_TYPE );

     ID_Receiver_DATA[ID_DATA_PCS-1]=ID_Receiver_Login;
     xn.IDL=ID_Receiver_Login;

     for(i=0;i<260;i++){
        j=3*i;
        xm[0] = ReadByteEEPROM( addr_eeprom_sys+j);
	j++;
        xm[1] = ReadByteEEPROM( addr_eeprom_sys+j);
	j++;
        xm[2] = ReadByteEEPROM( addr_eeprom_sys+j);
        xd.IDB[0]=0;
        xd.IDB[1]=xm[0];
        xd.IDB[2]=xm[1];
        xd.IDB[3]=xm[2];
        if((xd.IDL==0)||(xd.IDL==0xFFFFFF))break;
        ClearWDT(); // Service the WDT
    }

     xm[0]=xn.IDB[1];
     xm[1]=xn.IDB[2];
     xm[2]=xn.IDB[3];
     m1=j-2;
     UnlockFlash( UNLOCK_EEPROM_TYPE );
	WriteByteToFLASH( addr_eeprom_sys+m1, xm[0]);
	m1++;
	WriteByteToFLASH( addr_eeprom_sys+m1, xm[1]);
	m1++;
	WriteByteToFLASH( addr_eeprom_sys+m1, xm[2]);
     LockFlash( UNLOCK_EEPROM_TYPE );

     if(ID_DATA_PCS>=256){ID_Login_EXIT_Initial();DATA_Packet_Control=0;time_Login_exit_256=110;}
  */
}

void ID_EEPROM_write_0x00(void)
{
    /*   UINT8 xm[3]={0};
   UINT16 i,j,m1,q,p;
   uni_rom_id xn,xd;

     ID_DATA_PCS--;
     xm[0]=ID_DATA_PCS%256;
     xm[1]=ID_DATA_PCS/256;

     UnlockFlash( UNLOCK_EEPROM_TYPE );
	WriteByteToFLASH( addr_eeprom_sys+0x3FE, xm[1]);
	WriteByteToFLASH( addr_eeprom_sys+0x3FF, xm[0]);
     LockFlash( UNLOCK_EEPROM_TYPE );

      for(i=0;i<260;i++){
        j=3*i;
        xm[0] = ReadByteEEPROM( addr_eeprom_sys+j);
	j++;
        xm[1] = ReadByteEEPROM( addr_eeprom_sys+j);
	j++;
        xm[2] = ReadByteEEPROM( addr_eeprom_sys+j);
        xd.IDB[0]=0;
        xd.IDB[1]=xm[0];
        xd.IDB[2]=xm[1];
        xd.IDB[3]=xm[2];
        if(xd.IDL==DATA_Packet_ID)break;
        ClearWDT(); // Service the WDT
    }

     xm[0]=0;
     xm[1]=0;
     xm[2]=0;
     m1=i*3;
     UnlockFlash( UNLOCK_EEPROM_TYPE );
	WriteByteToFLASH( addr_eeprom_sys+m1, xm[0]);
	m1++;
	WriteByteToFLASH( addr_eeprom_sys+m1, xm[1]);
	m1++;
	WriteByteToFLASH( addr_eeprom_sys+m1, xm[2]);
     LockFlash( UNLOCK_EEPROM_TYPE );

     q=ID_DATA_PCS;
    p=0;
    for(i=0;i<q;i++){
        j=3*i;
        xm[0] = ReadByteEEPROM( addr_eeprom_sys+j);
	j++;
        xm[1] = ReadByteEEPROM( addr_eeprom_sys+j);
	j++;
        xm[2] = ReadByteEEPROM( addr_eeprom_sys+j);
        xn.IDB[0]=0;
        xn.IDB[1]=xm[0];
        xn.IDB[2]=xm[1];
        xn.IDB[3]=xm[2];
        if((xn.IDL==0)||(xn.IDL==0xFFFFFF))q++;
        else ID_Receiver_DATA[p++]=xn.IDL;
        if(q>260)break;
        ClearWDT(); // Service the WDT
    }
    */
}
