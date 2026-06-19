#include "bsp_encoder.h"

static int leftSpeed;
static int rightSpeed;

void BspEncoder_Init(void)
{
    leftSpeed = 0;
    rightSpeed = 0;
}

void BspEncoder_Update(void)
{
}

int BspEncoder_GetLeftSpeed(void)
{
    return leftSpeed;
}

int BspEncoder_GetRightSpeed(void)
{
    return rightSpeed;
}
