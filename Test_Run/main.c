#include <stdint.h>

#include "board.h"
#include "bsp_motor.h"
#include "ti_msp_dl_config.h"

#define MOTOR_TEST_PHASE_MS  (3000U)
#define MOTOR_TEST_PAUSE_MS   (200U)

static void _DelayMs(uint32_t ms);
static void _RunPhase(void (*pfnMotion)(uint16_t), uint16_t speed);

int main(void)
{
    Board_Init();
    BspMotor_Init();

    _RunPhase(BspMotor_Forward, BSP_MOTOR_TEST_SPEED);
    _RunPhase(BspMotor_Backward, BSP_MOTOR_TEST_SPEED);
    _RunPhase(BspMotor_SpinLeft, BSP_MOTOR_TEST_SPEED);
    _RunPhase(BspMotor_SpinRight, BSP_MOTOR_TEST_SPEED);

    BspMotor_Stop();

    while (1) {
        __WFI();
    }
}

static void _DelayMs(uint32_t ms)
{
    while (ms-- > 0U) {
        delay_cycles(CPUCLK_FREQ / 1000U);
    }
}

static void _RunPhase(void (*pfnMotion)(uint16_t), uint16_t speed)
{
    (*pfnMotion)(speed);
    _DelayMs(MOTOR_TEST_PHASE_MS);
    BspMotor_Stop();
    _DelayMs(MOTOR_TEST_PAUSE_MS);
}
