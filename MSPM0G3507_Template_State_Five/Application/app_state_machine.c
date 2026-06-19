#include "app_state_machine.h"

#include "bsp_encoder.h"
#include "bsp_motor.h"
#include "bsp_oled.h"
#include "pid_ctrl.h"

static AppState_t s_state = APP_STATE_IDLE;

static void _State_Idle(MsgId_t msg);
static void _State_Ready(MsgId_t msg);
static void _State_Running(MsgId_t msg);
static void _State_Pause(MsgId_t msg);
static void _State_Error(MsgId_t msg);

void AppSM_Init(void)
{
    PID_Init();
    BspMotor_Init();
    BspEncoder_Init();
    BspOled_Init();

    s_state = APP_STATE_IDLE;
}

void AppSM_Run(MsgId_t msg)
{
    switch (s_state) {
        case APP_STATE_IDLE:
            _State_Idle(msg);
            break;

        case APP_STATE_READY:
            _State_Ready(msg);
            break;

        case APP_STATE_RUNNING:
            _State_Running(msg);
            break;

        case APP_STATE_PAUSE:
            _State_Pause(msg);
            break;

        case APP_STATE_ERROR:
        default:
            _State_Error(msg);
            break;
    }
}

AppState_t AppSM_GetState(void)
{
    return s_state;
}

void AppSM_SetState(AppState_t state)
{
    s_state = state;
}

static void _State_Idle(MsgId_t msg)
{
    if (msg == MSG_START) {
        s_state = APP_STATE_READY;
    }
}

static void _State_Ready(MsgId_t msg)
{
    if (msg == MSG_TICK) {
        s_state = APP_STATE_RUNNING;
    } else if (msg == MSG_STOP) {
        s_state = APP_STATE_IDLE;
    }
}

static void _State_Running(MsgId_t msg)
{
    BspEncoder_Update();
    PID_Update();
    BspMotor_Update();

    if (msg == MSG_STOP) {
        BspMotor_Stop();
        s_state = APP_STATE_PAUSE;
    } else if (msg == MSG_ERROR) {
        s_state = APP_STATE_ERROR;
    }
}

static void _State_Pause(MsgId_t msg)
{
    if (msg == MSG_START) {
        s_state = APP_STATE_RUNNING;
    } else if (msg == MSG_RESET) {
        s_state = APP_STATE_IDLE;
    }
}

static void _State_Error(MsgId_t msg)
{
    BspMotor_Stop();

    if (msg == MSG_RESET) {
        s_state = APP_STATE_IDLE;
    }
}
