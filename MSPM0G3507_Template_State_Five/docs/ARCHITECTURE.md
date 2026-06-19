# 状态机五段式架构说明

## 目标段位

本模板以 **状态机 III：模块化封装版** 作为工程默认架构。

## 五段式路径

1. **状态机 I：switch-case 直写版**
   - 状态机直接写在 `main.c` 的 `while (1)` 中。
2. **状态机 II：状态行为外提版**
   - 每个状态拆成独立函数，但状态机仍放在 `main.c`。
3. **状态机 III：模块化封装版**
   - 状态机独立成 `.h/.c`，支持多个状态机并行。
4. **状态机 IV：函数指针版**
   - 用函数指针表示当前状态。
5. **状态机 V：SysML/嵌套状态机版**
   - 支持层次状态、复合状态和并发区域。

## 当前工程结构

```text
main.c
  ├─ MsgMap_Get()
  ├─ AppSM_Run(msg)
  ├─ SubSM_Run(msg)
  └─ MsgMap_Clear()
```

消息在主循环中只读取一次，多个状态机共享同一条消息。

## 状态机模块接口

主状态机：

```c
void AppSM_Init(void);
void AppSM_Run(MsgId_t msg);
AppState_t AppSM_GetState(void);
void AppSM_SetState(AppState_t state);
```

子状态机：

```c
void SubSM_Init(void);
void SubSM_Run(MsgId_t msg);
SubState_t SubSM_GetState(void);
```

## 私有函数规则

每个状态处理函数使用 `static` 修饰，并以下划线开头：

```c
static void _State_Idle(MsgId_t msg);
static void _State_Running(MsgId_t msg);
```

## 单件三模块封装

LED 示例按三部分拆分：

| 文件 | 职责 |
| --- | --- |
| `bsp_led.h` | 控制类、实体类、实例声明 |
| `bsp_led.c` | 控制对象和方法实现 |
| `bsp_led_instances.c` | 具体实体实例 |

这种方式适合电机、舵机、LED、传感器等同类多实例外设。
