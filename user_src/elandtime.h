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

extern iso8601_time_t SystemStartTime;
extern _eland_date_time ElandTimeNow;

void InitTimeBuff(void);

#endif
