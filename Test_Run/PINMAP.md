# MSPM0G3507 引脚分配表

> 本文件用于记录电赛工程接线。每次在 SysConfig 中修改引脚后，同步更新这里。

## 调试接口

| 功能 | 引脚 | 说明 |
| --- | --- | --- |
| SWCLK | PA20 | 下载/调试时使用 |
| SWDIO | PA19 | 下载/调试时使用 |

## 电机

| 功能 | 引脚 | 外设 | 说明 |
| --- | --- | --- | --- |
| 左电机 PWM | PB1 | TIMA1 CCP1 | 左轮速度输出 |
| 左电机 DIR1 | PA12 | GPIO | AIN1 |
| 左电机 DIR2 | PA13 | GPIO | AIN2 |
| 右电机 PWM | PB13 | TIMA0 CCP1_CMPL | 右轮速度输出，SysConfig 生成 `GPIO_PWM_1_C1_CMPL_*` |
| 右电机 DIR1 | PA14 | GPIO | BIN1 |
| 右电机 DIR2 | PA15 | GPIO | BIN2 |
| 使能 STBY | PA17 | GPIO | 高电平使能电机驱动 |

## 编码器

| 功能 | 引脚 | 外设 | 说明 |
| --- | --- | --- | --- |
| 左编码器 A | PB10 | GPIO/Timer | 左轮 A 相，测速/方向 |
| 左编码器 B | PB11 | GPIO/Timer | 左轮 B 相，测速/方向 |
| 右编码器 A | PB6 | GPIO/Timer | 右轮 A 相，测速/方向 |
| 右编码器 B | PB7 | GPIO/Timer | 右轮 B 相，占用 SPI_POCI |

## 通信与显示

| 功能 | 引脚 | 外设 | 说明 |
| --- | --- | --- | --- |
| UART TX | TBD | UART | 调试/蓝牙 |
| UART RX | TBD | UART | 调试/蓝牙 |
| OLED SCL | TBD | I2C | OLED |
| OLED SDA | TBD | I2C | OLED |

## 传感器

| 功能 | 引脚 | 外设 | 说明 |
| --- | --- | --- | --- |
| 灰度 1 | TBD | GPIO/ADC | 待分配 |
| 灰度 2 | TBD | GPIO/ADC | 待分配 |
| 灰度 3 | TBD | GPIO/ADC | 待分配 |
| IMU SCL | TBD | I2C | MPU/IMU |
| IMU SDA | TBD | I2C | MPU/IMU |
