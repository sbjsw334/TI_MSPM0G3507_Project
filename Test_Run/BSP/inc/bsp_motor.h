#ifndef _BSP_MOTOR_H_
#define _BSP_MOTOR_H_

#include <stdint.h>

#define BSP_MOTOR_SPEED_MIN (0U)
#define BSP_MOTOR_SPEED_MAX (100U)
#define BSP_MOTOR_TEST_SPEED (100U)

/**
 * @brief  初始化电机控制引脚与PWM输出
 */
void BspMotor_Init(void);

/**
 * @brief  设置左右电机速度
 * @param  leftSpeed: 左电机速度，范围 0-100
 * @param  rightSpeed: 右电机速度，范围 0-100
 */
void BspMotor_SetSpeed(uint16_t leftSpeed, uint16_t rightSpeed);

/**
 * @brief  前进
 * @param  speed: 速度，范围 0-100
 */
void BspMotor_Forward(uint16_t speed);

/**
 * @brief  后退
 * @param  speed: 速度，范围 0-100
 */
void BspMotor_Backward(uint16_t speed);

/**
 * @brief  原地左转
 * @param  speed: 速度，范围 0-100
 */
void BspMotor_SpinLeft(uint16_t speed);

/**
 * @brief  原地右转
 * @param  speed: 速度，范围 0-100
 */
void BspMotor_SpinRight(uint16_t speed);

/**
 * @brief  停止电机
 */
void BspMotor_Stop(void);

/**
 * @brief  兼容状态机模板的更新接口
 */
void BspMotor_Update(void);

#endif /* _BSP_MOTOR_H_ */
