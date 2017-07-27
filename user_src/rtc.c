#include "rtc.h"
//#include <iostm8l151g4.h> // CPU型号
#include <iostm8l052c6.h> // CPU型号
u8 bRTC_Update_Flag = 0;
/******************************************************************************************************

* 名    称：void RTC_Config(void)

* 功    能：重新设置RTC的时分秒年月日,同时闹铃设置为一秒进入一次中断

* 入口参数：无

* 出口参数：无

* 说    明：

* 范    例：无

******************************************************************************************************/
void RTC_Config(void)
{
    //------打开LCD/RTC时钟------
    CLK_PCKENR2_PCKEN22 = 1;
#ifndef RTC_LSE
    //---选择LSI作为RTC时钟---
    CLK_CRTCR_RTCSEL0 = 0;
    CLK_CRTCR_RTCSEL1 = 1;
    CLK_CRTCR_RTCSEL2 = 0;
    CLK_CRTCR_RTCSEL3 = 0;
/*  0000: No clock selected
    0001: HSI clock used as RTC clock source
    0010: LSI clock used as RTC clock source
    0100: HSE clock used as RTC clock source
    1000: LSE clock used as RTC clock sourc*/
#else
    //---选择LSI作为RTC时钟---
    CLK_CRTCR_RTCSEL0 = 0;
    CLK_CRTCR_RTCSEL1 = 0;
    CLK_CRTCR_RTCSEL2 = 0;
    CLK_CRTCR_RTCSEL3 = 1;
/*  0000: No clock selected
    0001: HSI clock used as RTC clock source
    0010: LSI clock used as RTC clock source
    0100: HSE clock used as RTC clock source
    1000: LSE clock used as RTC clock sourc*/
#endif
    //----设置RTC时钟分频值----
    CLK_CRTCR_RTCDIV0 = 0;
    CLK_CRTCR_RTCDIV1 = 0;
    CLK_CRTCR_RTCDIV2 = 0;
    /*000: RTC clock source/1
    001: RTC clock source /2
    010: RTC clock source /4
    011: RTC clock source /8
    100: RTC clock source /16
    101: RTC clock source /32
    110: RTC clock source /64
    111: RTC clock source /128*/
}

void RTC_Time_Set(_eland_date_time time)
{
    //关闭RTC寄存器的写保护功能
    RTC_WPR = 0xCA;
    RTC_WPR = 0x53;
    RTC_ISR1_INIT = 1; //进入初始化模式，计数器停止工作
    while (!RTC_ISR1_INITF)
        ; //等待同步完成
    //初始化时间和日期
    RTC_TR1_ST = time.second / 10;           //second tens
    RTC_TR1_SU = time.second % 10;           //second units
    RTC_TR2_MNT = time.minute / 10;          //minute tens
    RTC_TR2_MNU = time.minute % 10;          //minute units
    RTC_TR3_PM = ((time.hour < 12) ? 0 : 1); //AM/PM
    RTC_TR3_HT = time.hour / 10;             //hour tens
    RTC_TR3_HU = time.hour % 10;             //hour units
    RTC_DR1_DT = time.day / 10;              //date tens
    RTC_DR1_DU = time.day % 10;              //date units
    RTC_DR2_WDU = time.week;                 //week day units
    RTC_DR2_MT = time.month / 10;            //month tens
    RTC_DR2_MU = time.month % 10;            //month units
    RTC_DR3_YT = (time.year % 100) / 10;     //year tens
    RTC_DR3_YU = time.year % 10;             //year units
    RTC_CR1_FMT = 0;                         //24小时模式

#ifndef RTC_LSE
    // RTC_APRER=0x7F;//保持默认值0x7F
    RTC_APRER = 0x7c; //保持默认值0x7F
    RTC_SPRERH = 0x01;
    RTC_SPRERL = 0x2F; //保持默认值0xFF
//38000Hz / ((303 + 1) * (124 + 1)) = 1Hz
#else
    // RTC_APRER=0x7F;//保持默认值0x7F
    RTC_APRER = 0x7f; //保持默认值0x7F
    RTC_SPRERH = 0x00;
    RTC_SPRERL = 0xff; //保持默认值0xFF

//以上两个RTC时钟分频值保持默认
//最终提供给日历模块的时钟为 32768Hz/( (127+1)*(255+1) ) =1Hz
#endif
    RTC_ISR1_INIT = 0; //退出初始化模式
    //设置闹钟
    RTC_CR2_ALRAE = 0; //disable the alarm
    while (!RTC_ISR1_ALRAWF)
        ; //
    //设置闹钟时间
    //屏蔽了所有时间,导致闹钟1秒中执行一次,进入一次闹钟中断
    RTC_ALRMAR1_MSK1 = 1;  //屏蔽秒定时
    RTC_ALRMAR1_ALST = 2;  //second tens
    RTC_ALRMAR1_ALSU = 0;  //second units
    RTC_ALRMAR2_MSK2 = 1;  //屏蔽分钟定时
    RTC_ALRMAR2_ALMNT = 0; //minute tens
    RTC_ALRMAR2_ALMNU = 0; //minute units
    RTC_ALRMAR3_MSK3 = 1;  //屏蔽小时定时
    RTC_ALRMAR3_ALHT = 0;  //hour tens
    RTC_ALRMAR3_ALHU = 6;  //hour units
    RTC_ALRMAR3_PM = 0;
    RTC_ALRMAR4_MSK4 = 1; //屏蔽关闭天定时
    RTC_ALRMAR4_ALDT = 0;
    RTC_ALRMAR4_ALDU = 0;
    RTC_ALRMAR4_WDSEL = 0;
    RTC_CR2_ALRAE = 1;  //使能闹铃功能
    RTC_CR2_ALRAIE = 1; //使能闹铃中断
    //programming the auto-wakeup timer
    // RTC_CR2_WUTE=0;//disable the wakeup timer
    // while(!RTC_ISR1_WUTWF);
    // RTC_WUTRH=0;//装初值
    // RTC_WUTRL=8;//
    //配置自动唤醒分频值
    //RTC_CR1_WUCKSEL=0x03;//32768Hz/2=16384Hz
    /* 000: RTCCLK/16 clock is selected
    001: RTCCLK/8 clock is selected
    010: RTCCLK/4 clock is selected
    011: RTCCLK/2 clock is selected   */
    // RTC_CR2_WUTE=0;//enable the tiemr again
    // RTC_CR2_WUTIE=0;
    RTC_WPR = 0x55; //使能写保护
    RTC_WPR = 0x55;
}
void RTC_Time_Read(_eland_date_time *time)
{
    time->year = 2000;
    time->year += RTC_DR3_YT * 10;
    time->year += RTC_DR3_YU;

    time->month = RTC_DR2_MT * 10;
    time->month += RTC_DR2_MU;

    time->day = RTC_DR1_DT * 10;
    time->day += RTC_DR1_DU;

    time->hour = RTC_TR3_HT * 10;
    time->hour += RTC_TR3_HU;

    time->minute = RTC_TR2_MNT * 10;
    time->minute += RTC_TR2_MNU;

    time->second = RTC_TR1_ST * 10;
    time->second += RTC_TR1_SU;

    time->week = RTC_DR2_WDU; //week day units
}
void RTC_ALARM_ISR(void)
{
    bRTC_Update_Flag = true;
    RTC_Time_Read(&ElandTimeNow);
    RTC_ISR2_ALRAF = 0;
}
