# MSPM0G3507 状态机五段式模板

本工程参考：

- `D:\Learn\Learn\Obsidian\电赛\系统架构与AIGC教研`
- `D:\Learn\Learn\Obsidian\电赛\单间三模块封装.txt`
- `D:\Learn\Learn\Obsidian\电赛\系统架构.md`

目标是提供一个适合电赛代码的 **状态机 III 工程目标段位模板**，并保留状态机 I~V 的学习路径说明。

## 核心思想

主循环只做三件事：

```c
MsgId_t msg = MsgMap_Get();
AppSM_Run(msg);
SubSM_Run(msg);
MsgMap_Clear();
```

消息只在主循环统一读取一次，然后分发给多个状态机共享。

## 状态机五段式

| 段位 | 名称 | 说明 |
| --- | --- | --- |
| I | switch-case 直写版 | 在 `main.c` 里直接写状态机 |
| II | 状态行为外提版 | 每个状态拆成独立函数 |
| III | 模块化封装版 | 独立 `.h/.c`，工程默认采用 |
| IV | 函数指针版 | 状态本体改为函数指针 |
| V | SysML/嵌套状态机版 | 支持层次状态机和并发区域 |

本模板的代码实现采用 **状态机 III**：

```text
main.c
Application/app_state_machine.c/h
Application/sub_state_machine.c/h
Application/msg_map.c/h
```

## 工程结构

```text
MSPM0G3507_Template_State_Five/
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

## 单件三模块封装示例

模板里用 LED 演示“控制类 + 实体类 + 实例层”：

```text
BSP/inc/bsp_led.h          # 控制类和实体类声明
BSP/src/bsp_led.c          # 控制类方法实现
BSP/src/bsp_led_instances.c# 具体实例 ledRun / ledError
```

核心约定：

- 控制类统一操作实体指针
- 实体类保存硬件资源、状态、回调
- 多实例统一由一个控制对象管理
- 回调允许为空，调用前必须判空

## 使用方式

1. 复制整个文件夹，改成你的新工程名。
2. 打开：

```text
keil\MSPM0G3507_Template_State_Five.uvprojx
```

3. Rebuild。
4. 在 `MsgMap_Get()` 或外部中断/按键处理中产生消息。
5. 在 `AppSM_Run()` / `SubSM_Run()` 中消费消息。
