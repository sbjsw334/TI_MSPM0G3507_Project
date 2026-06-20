#ifndef _MSG_MAP_H_
#define _MSG_MAP_H_

typedef enum {
    MSG_NONE = 0,
    MSG_START,
    MSG_STOP,
    MSG_TICK,
    MSG_ERROR,
    MSG_RESET,
} MsgId_t;

void MsgMap_Init(void);
MsgId_t MsgMap_Get(void);
void MsgMap_Set(MsgId_t msg);
void MsgMap_Clear(void);

#endif /* _MSG_MAP_H_ */
