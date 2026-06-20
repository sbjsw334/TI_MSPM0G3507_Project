#include "msg_map.h"

static MsgId_t s_msg = MSG_NONE;

void MsgMap_Init(void)
{
    s_msg = MSG_NONE;
}

MsgId_t MsgMap_Get(void)
{
    return s_msg;
}

void MsgMap_Set(MsgId_t msg)
{
    s_msg = msg;
}

void MsgMap_Clear(void)
{
    s_msg = MSG_NONE;
}
