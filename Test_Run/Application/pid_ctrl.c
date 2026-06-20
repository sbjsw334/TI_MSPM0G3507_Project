#include "pid_ctrl.h"

void PID_Init(void)
{
}

void PID_Update(void)
{
}

float PID_Calc(PIDCtrl *pPid, float target, float feedback)
{
    float error;
    float derivative;

    if (pPid == 0) {
        return 0.0f;
    }

    error = target - feedback;
    pPid->integral += error;
    derivative = error - pPid->lastError;

    pPid->target = target;
    pPid->feedback = feedback;
    pPid->output = pPid->kp * error + pPid->ki * pPid->integral + pPid->kd * derivative;
    pPid->lastError = error;

    return pPid->output;
}
