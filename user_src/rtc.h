#ifndef __RTC_H__
#define __RTC_H__
#include "elandtime.h"
/**
 ****************************************************************************
 * @Warning :Without permission from the author,Not for commercial use
 * @File    :rtc.h
 * @Author  :Xiaowine
 * @date    :2017/7/20
 * @version :V 1.0.0
 *************************************************
 * @brief   :
 ****************************************************************************
**/
extern u8 bRTC_Update_Flag;

void RTC_Config(void);
void RTC_Time_Set(_eland_date_time time);
       void RTC_ALARM_ISR(void);
#endif
