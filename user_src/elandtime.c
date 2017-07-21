#include "elandtime.h"
#include <string.h>
#include <stdio.h>
#include "lcd.h"
#include "rtc.h"
/**
 ****************************************************************************
 * @Warning :Without permission from the author,Not for commercial use
 * @File    :elandtime.c
 * @Author  :Xiaowine
 * @date    :2017/7/20
 * @version :V 1.0.0
 *************************************************
 * @brief   :
 ****************************************************************************
**/
iso8601_time_t SystemStartTime;
_eland_date_time ElandTimeNow = {2017, 7, 20, 17, 20, 0, 4};
u8 ElandTime_For_Set[6] = {17, 7, 20, 17, 20, 0};
static u8 ElandTimeSetStatus = 0;
static u8 Time_Set_Select_Num = 0;
char TimeSetString[6][6] = {
    {'y', 'e', 'a', 'r', ' ', ' '},
    {'m', 'o', 'u', 't', 'h', ' '},
    {'d', 'a', 'y', ' ', ' ', ' '},
    {'h', 'o', 'u', 'r', ' ', ' '},
    {'m', 'i', 'n', 'u', 't', 'e'},
    {'s', 'e', 'c', 'o', 'n', 'd'},
};

void InitTimeBuff(void)
{

    memcpy((char *)&SystemStartTime, "2017-07-20 14:26:00", sizeof("2017-07-20 14:26:00"));
}
/**
 ****************************************************************************
 * @Function : void ElandTimeSet(void)
 * @File     : elandtime.c
 * @Program  :
 * @Created  : 2017/7/21 by Xiaowine
 * @Brief    :
 * @Version  : V1.0
**/
void ElandTimeSet(void)
{
    char Cache[20];
    if (ElandTimeSetStatus == (u8)TIME_SET_NONE)
    {

        ElandTime_For_Set[0] = ElandTimeNow.year % 100;
        ElandTime_For_Set[1] = ElandTimeNow.month;
        ElandTime_For_Set[2] = ElandTimeNow.day;
        ElandTime_For_Set[3] = ElandTimeNow.hour;
        ElandTime_For_Set[4] = ElandTimeNow.minute;
        ElandTime_For_Set[5] = ElandTimeNow.second;

        Time_Set_Select_Num = 1;
        display_map_58_6(10, 20, 6, (const unsigned char *)&TimeSetString[ElandTimeSetStatus]);
        sprintf(Cache, "%02d", ElandTime_For_Set[ElandTimeSetStatus]);
        display_map_58_6(46, 20, 2, (const unsigned char *)Cache);
        display_map_58_6(46 + ((1 - Time_Set_Select_Num) * 6), 30, 2, "* ");
        ElandTimeSetStatus = TIME_SET_YEAR;
    }
    else if (ElandTimeSetStatus == (u8)TIME_SET_SECOND)
    {
        if (Time_Set_Select_Num > 0)
        {
            display_map_58_6(46, 30, 2, " *");
            Time_Set_Select_Num--;
        }
        else
        {
            Time_Set_Select_Num = 1;
            display_map_58_6(10, 20, 8, "        ");
            display_map_58_6(46, 30, 2, "  ");
            ElandTimeNow.year = 2000 + ElandTime_For_Set[0];
            ElandTimeNow.month = ElandTime_For_Set[1];
            ElandTimeNow.day = ElandTime_For_Set[2];
            ElandTimeNow.hour = ElandTime_For_Set[3];
            ElandTimeNow.minute = ElandTime_For_Set[4];
            ElandTimeNow.second = ElandTime_For_Set[5];
            RTC_Time_Set(ElandTimeNow);
            ElandTimeSetStatus = TIME_SET_NONE;
        }
    }
    else
    {
        if (Time_Set_Select_Num > 0)
        {
            display_map_58_6(46, 30, 2, " *");
            Time_Set_Select_Num--;
        }
        else
        {
            Time_Set_Select_Num = 1;
            display_map_58_6(10, 20, 6, (const unsigned char *)&TimeSetString[ElandTimeSetStatus]);
            sprintf(Cache, "%02d", ElandTime_For_Set[ElandTimeSetStatus]);
            display_map_58_6(46, 20, 4, (const unsigned char *)Cache);
            display_map_58_6(46, 30, 2, "* ");
            ElandTimeSetStatus++;
        }
    }
}
/**
 ****************************************************************************
 * @Function : void TimeToString(_eland_date_time *Timecache,iso8601_time_t  *timestring)
 * @File     : elandtime.c
 * @Program  : _eland_date_time *Timecache,iso8601_time_t  *timestring
 * @Created  : 2017/7/21 by Xiaowine
 * @Brief    : _eland_date_time  to iso8601_time_t
 * @Version  : V1.0
**/
void TimeToString(_eland_date_time *Timecache, iso8601_time_t *timestring)
{
    sprintf((char *)&timestring->year, "%4d", Timecache->year);
    sprintf((char *)&timestring->month, "%02d", Timecache->month);
    sprintf((char *)&timestring->day, "%02d", Timecache->day);
    sprintf((char *)&timestring->hour, "%02d", Timecache->hour);
    sprintf((char *)&timestring->minute, "%02d", Timecache->minute);
    sprintf((char *)&timestring->second, "%02d", Timecache->second);
    timestring->dash1 = '-';
    timestring->dash2 = '-';
    timestring->T = ' ';
    timestring->colon1 = ':';
    timestring->colon2 = ':';
}
/**
 ****************************************************************************
 * @Function : void ElandTimeChange(u8 keyvalue)
 * @File     : elandtime.c
 * @Program  :
 * @Created  : 2017/7/21 by Xiaowine
 * @Brief    :
 * @Version  : V1.0
**/
void ElandTimeChange(u8 keyvalue)
{
    switch (ElandTimeSetStatus)
    {
    case TIME_SET_YEAR:
        if (ADD_KEY == keyvalue)
        {
            ElandTime_For_Set[0] += (Time_Set_Select_Num ? 10 : 1);
            if (ElandTime_For_Set[0] >= 100)
                ElandTime_For_Set[0] %= 100;
        }
        else if (MINUS_KEY == keyvalue)
        {
            if (ElandTime_For_Set[0] >= (Time_Set_Select_Num ? 10 : 1))
                ElandTime_For_Set[0] -= (Time_Set_Select_Num ? 10 : 1);
            else
                ElandTime_For_Set[0] = 99;
        }
        sprintf(Cache, "%02d", ElandTime_For_Set[ElandTimeSetStatus]);
        display_map_58_6(46, 20, 2, (const unsigned char *)Cache);
        break;
    case TIME_SET_MONTH:
        if (ADD_KEY == keyvalue)
        {
            if ((ElandTime_For_Set[0] + (Time_Set_Select_Num ? 10 : 1)) <= 12)
                ElandTime_For_Set[0] += (Time_Set_Select_Num ? 10 : 1);
        }
        else if (MINUS_KEY == keyvalue)
        {
            if (ElandTime_For_Set[0] - (Time_Set_Select_Num ? 10 : 1) >= 1)
                ElandTime_For_Set[0] -= (Time_Set_Select_Num ? 10 : 1);
        }
        sprintf(Cache, "%02d", ElandTime_For_Set[ElandTimeSetStatus]);
        display_map_58_6(46, 20, 2, (const unsigned char *)Cache);
        break;
    case TIME_SET_DAY:
        if (ADD_KEY == keyvalue)
        {
            if ((ElandTime_For_Set[0] + (Time_Set_Select_Num ? 10 : 1)) <= 59)
                ElandTime_For_Set[0] += (Time_Set_Select_Num ? 10 : 1);
        }
        else if (MINUS_KEY == keyvalue)
        {
            if (ElandTime_For_Set[0] - (Time_Set_Select_Num ? 10 : 1) >= 0)
                ElandTime_For_Set[0] -= (Time_Set_Select_Num ? 10 : 1);
        }
        sprintf(Cache, "%02d", ElandTime_For_Set[ElandTimeSetStatus]);
        display_map_58_6(46, 20, 2, (const unsigned char *)Cache);
        break;
    case TIME_SET_HOUR:
        break;
    case TIME_SET_MINUTE:
        break;
    case TIME_SET_SECOND:
        break;
    default:
        break;
    }
}
