#ifndef __ELANDDATA_H__
#define __ELANDDATA_H__
#include "type_def.h"

typedef enum {
    ElandBegin = 0,
    ElandAPStatus,
    ElandHttpServerStatus,
    ElandWifyConnectedSuccessed,
    ElandWifyConnectedFailed,
    ElandAliloPlay,
    ElandAliloPause,
    ElandAliloStop,
} Eland_Status_type;

extern u8 ElandReceiveBuff[11];
extern u8 ElandReceiveBuffBak[11];

void ReceiveFromEland(u8 cache);
void processData(void);
#endif
