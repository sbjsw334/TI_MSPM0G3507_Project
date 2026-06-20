#ifndef _PID_CTRL_H_
#define _PID_CTRL_H_

typedef struct {
    float kp;
    float ki;
    float kd;
    float target;
    float feedback;
    float output;
    float integral;
    float lastError;
} PIDCtrl;

void PID_Init(void);
void PID_Update(void);
float PID_Calc(PIDCtrl *pPid, float target, float feedback);

#endif /* _PID_CTRL_H_ */
