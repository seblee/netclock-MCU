#ifndef __ELANDTIME_H__
#define __ELANDTIME_H__
#include "type_def.h"
/**
 ****************************************************************************
 * @Warning :Without permission from the author,Not for commercial use
 * @File    :elandtime.h
 * @Author  :Xiaowine
 * @date    :2017/7/20
 * @version :V 1.0.0
 *************************************************
 * @brief   :
 ****************************************************************************
**/

typedef enum set_time_t {
    TIME_SET_NONE = 0,
    TIME_SET_YEAR,
    TIME_SET_MONTH,
    TIME_SET_DAY,
    TIME_SET_HOUR,
    TIME_SET_MINUTE,
    TIME_SET_SECOND,
    TIME_SET_WEEK
} __set_time_t;

typedef enum {
    Soft_AP, /**< Act as an access point, and other station can connect, 4 stations Max*/
    Station  /**< Act as a station which can connect to an access point*/
} wlanInterfaceTypedef;

extern iso8601_time_t SystemStartTime;
extern _eland_date_time ElandTimeNow;
extern u8 ElandTimeSetStatus;

void InitTimeBuff(void);
void ElandTimeSet(void);
void ElandTimeChange(u8 keyvalue);
#endif
