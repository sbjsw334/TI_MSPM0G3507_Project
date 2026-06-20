#ifndef _APP_STATE_MACHINE_H_
#define _APP_STATE_MACHINE_H_

#include "msg_map.h"

typedef enum {
    APP_STATE_IDLE = 0,
    APP_STATE_READY,
    APP_STATE_RUNNING,
    APP_STATE_PAUSE,
    APP_STATE_ERROR,
} AppState_t;

void AppSM_Init(void);
void AppSM_Run(MsgId_t msg);
AppState_t AppSM_GetState(void);
void AppSM_SetState(AppState_t state);

#endif /* _APP_STATE_MACHINE_H_ */
