# MSPM0G3507 电机模板（Test_Run）

本工程用于电赛小车的电机 bring-up 与后续模板化扩展，当前已经完成最小可用的轮子测试闭环：

- 上电自动执行
- 前进 3 秒
- 后退 3 秒
- 原地左转 3 秒
- 原地右转 3 秒
- 最后停止

## 当前目标

1. 作为 MSPM0G3507 车模的正式电机测试模板。
2. 统一电机控制接口，速度使用 `0 ~ 100` 的语义值。
3. 保留状态机模板结构，方便后续接入编码器和 PID 闭环。
4. 保持引脚、结构、注释风格符合《规范性.md》。

## 已确认的电机接线

| 功能 | 引脚 | 外设 | 说明 |
| --- | --- | --- | --- |
| 左电机 PWM | PB1 | TIMA1 CCP1 | 左轮速度输出 |
| 左电机 DIR1 | PA12 | GPIO | AIN1 |
| 左电机 DIR2 | PA13 | GPIO | AIN2 |
| 右电机 PWM | PB13 | TIMA0 CCP1_CMPL | 右轮速度输出，SysConfig 生成 `GPIO_PWM_1_C1_CMPL_*` |
| 右电机 DIR1 | PA14 | GPIO | BIN1 |
| 右电机 DIR2 | PA15 | GPIO | BIN2 |
| 使能 STBY | PA17 | GPIO | 高电平使能电机驱动 |

## 主流程

`main.c` 采用一条固定的上电测试序列，不依赖消息系统：

```c
Board_Init();
BspMotor_Init();

BspMotor_Forward(BSP_MOTOR_TEST_SPEED);
BspMotor_Backward(BSP_MOTOR_TEST_SPEED);
BspMotor_SpinLeft(BSP_MOTOR_TEST_SPEED);
BspMotor_SpinRight(BSP_MOTOR_TEST_SPEED);

BspMotor_Stop();
```

说明：

- 当前 `BSP_MOTOR_TEST_SPEED` 默认是 `30U`。
- `PB13` 是 `TIMA0 CCP1_CMPL` 互补输出，引脚配置必须在 `MSPM0G3507_Template_State_Five.syscfg` 中维护，不能只手改 `ti_msp_dl_config.h`。
- `BspMotor_SetSpeed(leftSpeed, rightSpeed)` 预留给后续差速/PID 控制。
- `BspMotor_Update()` 保留为模板兼容接口。

## 工程结构

```text
Test_Run/
├─ main.c
├─ MSPM0G3507_Template_State_Five.syscfg
├─ ti_msp_dl_config.c/h
├─ Board/
├─ Application/
│  ├─ app_state_machine.c/h
│  ├─ sub_state_machine.c/h
│  ├─ msg_map.c/h
│  └─ pid_ctrl.c/h
├─ BSP/
│  ├─ inc/
│  │  ├─ bsp_led.h
│  │  ├─ bsp_motor.h
│  │  ├─ bsp_encoder.h
│  │  ├─ bsp_oled.h
│  │  └─ bsp_key.h
│  └─ src/
│     ├─ bsp_led.c
│     ├─ bsp_led_instances.c
│     ├─ bsp_motor.c
│     ├─ bsp_encoder.c
│     ├─ bsp_oled.c
│     └─ bsp_key.c
├─ Hardware/
├─ docs/
└─ keil/
```

## 电机控制接口

- `BspMotor_Init()`：初始化 PWM 与方向控制
- `BspMotor_SetSpeed()`：设置左右电机速度
- `BspMotor_Forward()` / `BspMotor_Backward()`
- `BspMotor_SpinLeft()` / `BspMotor_SpinRight()`
- `BspMotor_Stop()`

速度参数统一按 `0 ~ 100` 解释：

- `0`：停止
- `100`：最大
- 中间值：占空比比例值

## 编码器与 PID

当前工程已经保留了后续闭环的入口：

- `Application/pid_ctrl.c/h`
- `BSP/src/bsp_encoder.c/h`
- `Application/app_state_machine.c`

后续可以按下面方式扩展：

1. 让编码器模块输出左右轮实际速度。
2. 用 `PID_Calc()` 做左右轮速度调节。
3. 用 `BspMotor_SetSpeed()` 直接写入左右轮目标速度。
4. 再把闭环逻辑接回状态机运行态。

## 使用方式

1. 打开 Keil 工程：

   ```text
   keil\MSPM0G3507_Template_State_Five.uvprojx
   ```

2. Rebuild。
3. 上电观察四段动作是否正确。
4. 如果方向需要调整，只改 `BSP/src/bsp_motor.c` 的方向映射。
5. 如果 PWM 引脚需要调整，优先改 `MSPM0G3507_Template_State_Five.syscfg` 后重新生成配置。
6. 如果后续要做更细的调速，再把 PWM 参数和 PID 控制接起来。

## 备注

- 该工程当前以“先能稳定转起来”为优先。
- 速度控制已经预留为标准接口，后续升级不会影响主流程。
- 文档中的引脚和模板结构应与代码保持同步更新。
