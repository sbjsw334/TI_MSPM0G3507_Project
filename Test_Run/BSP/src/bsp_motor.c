#include "bsp_motor.h"

#include "ti_msp_dl_config.h"

#define BSP_MOTOR_LEFT_IN1_PIN      (DL_GPIO_PIN_12)
#define BSP_MOTOR_LEFT_IN2_PIN      (DL_GPIO_PIN_13)
#define BSP_MOTOR_RIGHT_IN1_PIN     (DL_GPIO_PIN_14)
#define BSP_MOTOR_RIGHT_IN2_PIN     (DL_GPIO_PIN_15)
#define BSP_MOTOR_STBY_PIN          (DL_GPIO_PIN_17)

#define BSP_MOTOR_LEFT_DIR_MASK     (BSP_MOTOR_LEFT_IN1_PIN | BSP_MOTOR_LEFT_IN2_PIN)
#define BSP_MOTOR_RIGHT_DIR_MASK    (BSP_MOTOR_RIGHT_IN1_PIN | BSP_MOTOR_RIGHT_IN2_PIN)
#define BSP_MOTOR_CTRL_PIN_MASK     (BSP_MOTOR_LEFT_DIR_MASK | BSP_MOTOR_RIGHT_DIR_MASK | BSP_MOTOR_STBY_PIN)

#define BSP_MOTOR_LEFT_PWM_INST     PWM_0_INST
#define BSP_MOTOR_RIGHT_PWM_INST    PWM_1_INST

#define BSP_MOTOR_FORWARD_LEFT_SCALE   (98U) //右偏把左轮速度降一点
#define BSP_MOTOR_FORWARD_RIGHT_SCALE  (99U) //左偏把右轮速度降一点

static uint16_t _ClampSpeed(uint16_t speed);
static uint32_t _SpeedToCompare(GPTIMER_Regs *pTimer, uint16_t speed);
static uint16_t _ScaleSpeed(uint16_t speed, uint16_t scale);
static void _SetStandby(uint8_t enable);
static void _SetLeftForward(void);
static void _SetLeftBackward(void);
static void _SetRightForward(void);
static void _SetRightBackward(void);
static void _SetPwmSpeed(uint16_t leftSpeed, uint16_t rightSpeed);

void BspMotor_Init(void)
{
    DL_GPIO_initDigitalOutput(IOMUX_PINCM34);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM35);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM36);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM37);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM39);

    DL_GPIO_enableOutput(GPIOA, BSP_MOTOR_CTRL_PIN_MASK);

    DL_TimerA_setCCPDirection(BSP_MOTOR_LEFT_PWM_INST, DL_TIMER_CC1_OUTPUT);
    DL_TimerA_setCCPDirection(BSP_MOTOR_RIGHT_PWM_INST, DL_TIMER_CC1_OUTPUT);
    DL_TimerA_startCounter(BSP_MOTOR_LEFT_PWM_INST);
    DL_TimerA_startCounter(BSP_MOTOR_RIGHT_PWM_INST);

    BspMotor_Stop();
}

void BspMotor_SetSpeed(uint16_t leftSpeed, uint16_t rightSpeed)
{
    _SetStandby(1U);
    _SetPwmSpeed(leftSpeed, rightSpeed);
}

void BspMotor_Forward(uint16_t speed)
{
    _SetStandby(1U);
    _SetLeftForward();
    _SetRightForward();
    _SetPwmSpeed(_ScaleSpeed(speed, BSP_MOTOR_FORWARD_LEFT_SCALE),
        _ScaleSpeed(speed, BSP_MOTOR_FORWARD_RIGHT_SCALE));
}

void BspMotor_Backward(uint16_t speed)
{
    _SetStandby(1U);
    _SetLeftBackward();
    _SetRightBackward();
    _SetPwmSpeed(speed, speed);
}

void BspMotor_SpinLeft(uint16_t speed)
{
    _SetStandby(1U);
    _SetLeftBackward();
    _SetRightForward();
    _SetPwmSpeed(speed, speed);
}

void BspMotor_SpinRight(uint16_t speed)
{
    _SetStandby(1U);
    _SetLeftForward();
    _SetRightBackward();
    _SetPwmSpeed(speed, speed);
}

void BspMotor_Stop(void)
{
    DL_TimerA_setCaptureCompareValue(BSP_MOTOR_LEFT_PWM_INST, 0U, DL_TIMER_CC_1_INDEX);
    DL_TimerA_setCaptureCompareValue(BSP_MOTOR_RIGHT_PWM_INST, 0U, DL_TIMER_CC_1_INDEX);

    DL_GPIO_clearPins(GPIOA, BSP_MOTOR_CTRL_PIN_MASK);
}

void BspMotor_Update(void)
{
}

static uint16_t _ClampSpeed(uint16_t speed)
{
    if (speed > BSP_MOTOR_SPEED_MAX) {
        return BSP_MOTOR_SPEED_MAX;
    }

    return speed;
}

static uint32_t _SpeedToCompare(GPTIMER_Regs *pTimer, uint16_t speed) //计算PWM比较值  speed期望占空比（未映射）
{
    uint32_t loadValue; //装载值

    if (pTimer == 0U) { //指针保护
        return 0U;
    }

    speed = _ClampSpeed(speed); //速度限幅
    loadValue = DL_TimerA_getLoadValue(pTimer);

    if (loadValue == 0U) { //防止除零
        return 0U;
    }

    return loadValue - ((loadValue * (uint32_t)speed) / BSP_MOTOR_SPEED_MAX);
}

static uint16_t _ScaleSpeed(uint16_t speed, uint16_t scale)
{
    return _ClampSpeed(((uint32_t)speed * (uint32_t)scale) / 100U);
}

static void _SetStandby(uint8_t enable)
{
    if (enable != 0U) {
        DL_GPIO_setPins(GPIOA, BSP_MOTOR_STBY_PIN);
    } else {
        DL_GPIO_clearPins(GPIOA, BSP_MOTOR_STBY_PIN);
    }
}

static void _SetLeftForward(void)
{
    DL_GPIO_setPins(GPIOA, BSP_MOTOR_LEFT_IN1_PIN);
    DL_GPIO_clearPins(GPIOA, BSP_MOTOR_LEFT_IN2_PIN);
}

static void _SetLeftBackward(void)
{
    DL_GPIO_clearPins(GPIOA, BSP_MOTOR_LEFT_IN1_PIN);
    DL_GPIO_setPins(GPIOA, BSP_MOTOR_LEFT_IN2_PIN);
}

static void _SetRightForward(void)
{
    DL_GPIO_clearPins(GPIOA, BSP_MOTOR_RIGHT_IN1_PIN);
    DL_GPIO_setPins(GPIOA, BSP_MOTOR_RIGHT_IN2_PIN);
}

static void _SetRightBackward(void)
{
    DL_GPIO_setPins(GPIOA, BSP_MOTOR_RIGHT_IN1_PIN);
    DL_GPIO_clearPins(GPIOA, BSP_MOTOR_RIGHT_IN2_PIN);
}

static void _SetPwmSpeed(uint16_t leftSpeed, uint16_t rightSpeed) //传左右轮速度
{
    uint32_t leftCompare;
    uint32_t rightCompare;

	//计算占空比
    leftCompare = _SpeedToCompare(BSP_MOTOR_LEFT_PWM_INST, leftSpeed);
    rightCompare = _SpeedToCompare(BSP_MOTOR_RIGHT_PWM_INST, rightSpeed);

	//设置占空比
    DL_TimerA_setCaptureCompareValue(BSP_MOTOR_LEFT_PWM_INST, leftCompare,
        DL_TIMER_CC_1_INDEX);
    DL_TimerA_setCaptureCompareValue(BSP_MOTOR_RIGHT_PWM_INST, rightCompare,
        DL_TIMER_CC_1_INDEX);
}


