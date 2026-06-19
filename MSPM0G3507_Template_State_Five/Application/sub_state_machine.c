#include "sub_state_machine.h"

static SubState_t s_state = SUB_STATE_IDLE;

static void _State_Idle(MsgId_t msg);
static void _State_Active(MsgId_t msg);
static void _State_Error(MsgId_t msg);

void SubSM_Init(void)
{
    s_state = SUB_STATE_IDLE;
}

void SubSM_Run(MsgId_t msg)
{
    switch (s_state) {
        case SUB_STATE_IDLE:
            _State_Idle(msg);
            break;

        case SUB_STATE_ACTIVE:
            _State_Active(msg);
            break;

        case SUB_STATE_ERROR:
        default:
            _State_Error(msg);
            break;
    }
}

SubState_t SubSM_GetState(void)
{
    return s_state;
}

static void _State_Idle(MsgId_t msg)
{
    if (msg == MSG_START) {
        s_state = SUB_STATE_ACTIVE;
    }
}

static void _State_Active(MsgId_t msg)
{
    if (msg == MSG_STOP) {
        s_state = SUB_STATE_IDLE;
    } else if (msg == MSG_ERROR) {
        s_state = SUB_STATE_ERROR;
    }
}

static void _State_Error(MsgId_t msg)
{
    if (msg == MSG_RESET) {
        s_state = SUB_STATE_IDLE;
    }
}
