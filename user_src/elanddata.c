#include "elanddata.h"
#include "rtc.h"
#include "Pin_define.h"

#include <iostm8l052c6.h> // CPU型号
/****************/
u8 ElandReceiveBuff[11] = {0, 0};
u8 ElandReceiveBuffBak[11];
/******************/
void ReceiveFromEland(u8 cache)
{
    static u8 number = 0;
    if ((number == 0) && (cache == '{'))
    {
        ElandReceiveBuff[number] = cache; //header
        number++;
    }
    else if (number == 1)
    {
        ElandReceiveBuff[number] = cache; //status
        number++;
    }
    else if (number == 2)
    {
        ElandReceiveBuff[number] = cache; //second
        number++;
    }
    else if (number == 3)
    {
        ElandReceiveBuff[number] = cache; //minute
        number++;
    }
    else if (number == 4)
    {
        ElandReceiveBuff[number] = cache; //hour
        number++;
    }
    else if (number == 5)
    {
        ElandReceiveBuff[number] = cache; //week
        number++;
    }
    else if (number == 6)
    {
        ElandReceiveBuff[number] = cache; //date
        number++;
    }
    else if (number == 7)
    {
        ElandReceiveBuff[number] = cache; //month
        number++;
    }
    else if (number == 8)
    {
        ElandReceiveBuff[number] = cache; //year
        number++;
    }
    else if ((number == 9) && (cache == '}'))
    {
        ElandReceiveBuff[number] = cache; //trail
        number++;
    }
    else
        number = 0;

    if (number == 10)
    {
        processData();
        number = 0;
    }
}
void processData(void)
{
    u8 i;
    if (ElandReceiveBuff[1] != ElandReceiveBuffBak[1])
        bRTC_Update_Flag = 1;
    if ((ElandReceiveBuff[1] == ElandWifyConnectedSuccessed) || (ElandReceiveBuff[1] >= ElandWifyConnectedFailed))
        LED_WIFI = LED_ON;
    else
        LED_WIFI = LED_OFF;
    for (i = 2; i < 10; i++)
    {
        if (ElandReceiveBuff[i] != ElandReceiveBuffBak[i])
            break;
    }
}
