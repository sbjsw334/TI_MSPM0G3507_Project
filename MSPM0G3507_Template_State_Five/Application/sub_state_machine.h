#ifndef _SUB_STATE_MACHINE_H_
#define _SUB_STATE_MACHINE_H_

#include "msg_map.h"

typedef enum {
    SUB_STATE_IDLE = 0,
    SUB_STATE_ACTIVE,
    SUB_STATE_ERROR,
} SubState_t;

void SubSM_Init(void);
void SubSM_Run(MsgId_t msg);
SubState_t SubSM_GetState(void);

#endif /* _SUB_STATE_MACHINE_H_ */
