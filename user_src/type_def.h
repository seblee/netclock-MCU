/**
****************************************************************************
* @Warning :Without permission from the author,Not for commercial use
* @File    :type_def.h
* @Author  :Xiaowine
* @date    :2017/4/14
* @version :V 1.0.0
*************************************************
* @brief   :
****************************************************************************
**/

#ifndef __type_def_h__
#define __type_def_h__

/*主控芯片的头文件*/
//

/*bool 类型头文件*/
#include "stdbool.h"

/*总中断头文件*/
#include "intrinsics.h"

/*常用数据类型定义*/
typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned long u32_t;
#define u8 u8_t
#define u16 u16_t
#define u32 u32_t
#define EnableInterrupt __enable_interrupt()

#define SUCESS 1
#define FAILURE 0

//代码标志位
typedef union _fullflag_ {
    unsigned char BYTE;
    struct
    {
        unsigned char Bit0 : 1;
        unsigned char Bit1 : 1;
        unsigned char Bit2 : 1;
        unsigned char Bit3 : 1;
        unsigned char Bit4 : 1;
        unsigned char Bit5 : 1;
        unsigned char Bit6 : 1;
        unsigned char Bit7 : 1;
    } BIT;
} uFLAG, *P_uFLAG;
#define TRANSITION_STATUS_TRANSITION 0
#define TRANSITION_STATUS_EXECUTING 1
#define TRANSITION_STATUS_IDLE 2
typedef struct
{
    char year[4];       /**< Year         */
    char dash1;         /**< Dash1        */
    char month[2];      /**< Month        */
    char dash2;         /**< Dash2        */
    char day[2];        /**< Day          */
    char T;             /**< T            */
    char hour[2];       /**< Hour         */
    char colon1;        /**< Colon1       */
    char minute[2];     /**< Minute       */
    char colon2;        /**< Colon2       */
    char second[2];     /**< Second       */
    char decimal;       /**< Decimal      */
    char sub_second[6]; /**< Sub-second   */
    char Z;             /**< UTC timezone */
} iso8601_time_t;

typedef struct
{
    u16 year;
    u8 month;
    u8 day;
    u8 hour;
    u8 minute;
    u8 second;
    u8 week;
} _eland_date_time;

#endif
