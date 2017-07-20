#include "elandtime.h"
#include <string.h>
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

void InitTimeBuff(void)
{

    memcpy((char *)&SystemStartTime, "2017-07-20 14:26:00", sizeof("2017-07-20 14:26:00"));
}
