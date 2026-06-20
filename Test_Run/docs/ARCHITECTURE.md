# 状态机五段式架构说明

## 当前工程定位

`Test_Run` 目前承担两个角色：

1. 作为 MSPM0G3507 小车电机的上电测试模板。
2. 作为后续状态机 / 编码器 / PID / 差速控制的基础工程。

当前的实际运行入口仍然是 `main.c` 的固定动作序列，因为这是最稳定、最容易验证接线正确性的方式。

## 当前运行流程

```text
Board_Init()
  -> BspMotor_Init()
  -> 前进 3 秒
  -> 后退 3 秒
  -> 原地左转 3 秒
  -> 原地右转 3 秒
  -> Stop()
  -> while(1)
```

## 分层职责

### 1. Board 层

文件：

- `Board/board.c`
- `Board/board.h`

职责：

- 完成 SysConfig 生成的板级初始化
- 提供底层芯片初始化入口

### 2. BSP 层

文件：

- `BSP/src/bsp_motor.c`
- `BSP/inc/bsp_motor.h`
- `BSP/src/bsp_encoder.c`
- `BSP/inc/bsp_encoder.h`

职责：

- 管理电机方向、PWM、STBY
- 保持电机控制 API 稳定
- 预留编码器采样接口

### 3. Application 层

文件：

- `Application/app_state_machine.c`
- `Application/sub_state_machine.c`
- `Application/msg_map.c`
- `Application/pid_ctrl.c`

职责：

- 保留状态机模板结构
- 后续承载闭环控制和业务调度

## 现阶段模板策略

当前的最佳策略是：

- 把“上电轮子测试”放在 `main.c`
- 把“硬件控制细节”放在 `bsp_motor.c`
- 把“后续闭环逻辑”留给 `Application` 层

这样做的好处是：

- bring-up 简单直接
- 便于定位方向/接线问题
- 后续升级到闭环时不需要重写主入口

## 电机控制约定

### 速度语义

`BspMotor_SetSpeed(leftSpeed, rightSpeed)` 使用统一的 `0 ~ 100` 语义：

- `0` = 停止
- `100` = 最大占空比

### 方向约定

- 左轮：`PA12 / PA13`
- 右轮：`PA14 / PA15`
- 使能：`PA17`
- PWM：左轮 `PA16`，右轮 `PA22`

## 五段式路径

1. **状态机 I：switch-case 直写版**
   - 适合最早期 bring-up
2. **状态机 II：状态行为外提版**
   - 便于拆分状态逻辑
3. **状态机 III：模块化封装版**
   - 当前工程默认采用
4. **状态机 IV：函数指针版**
   - 适合更复杂跳转
5. **状态机 V：SysML / 嵌套状态机版**
   - 适合复杂任务协调

## 后续闭环扩展建议

1. 编码器模块输出左右轮速度。
2. PID 模块根据目标速度和实际速度计算调节量。
3. 电机模块根据调节量更新左右轮 PWM 占空比。
4. 再将运行逻辑回接到 `AppSM_Run()`。

## 建议保持的规范

- `main.c` 始终是唯一主入口文件。
- `Application` 存状态机与控制逻辑。
- `BSP` 只做硬件抽象。
- 任何新增接口都要写 Doxygen 注释。
