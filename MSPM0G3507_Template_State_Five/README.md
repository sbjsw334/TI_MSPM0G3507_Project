# MSPM0G3507 状态机五段式模板

本工程用于整理 MSPM0G3507 电赛项目的**状态机 III 工程目标段位模板**，并保留状态机 I ~ V 的学习路径说明，便于后续扩展为完整的工程框架。

## 设计目标

- 主循环只负责**取消息、跑状态机、清消息**。
- 业务逻辑集中在 `Application` 包内，硬件相关内容集中在 `Hardware` 包内。
- 文件命名、类型命名、宏命名、注释风格统一遵循《规范性.md》的要求。
- 代码结构尽量保持清晰，方便后续复制到新工程中直接使用。

## 规范对应关系

本模板重点对齐以下规范：

- **工程创建规范**：工程名首字母大写。
- **工程结构规范**：代码相关文件按包管理，推荐划分为 `Hardware` 和 `Application`。
- **命名规范**：
  - 函数、变量：小写字母开头
  - 类型：大写字母开头
  - 宏：全大写
  - 指针：`p` 开头
  - 包名：首字母大写
- **注释规范**：采用 Doxygen 风格，重点使用 `@brief`、`@param`、`@retval`、`@note`、`@warning`。

## 核心思想

主循环统一处理消息，避免多个状态机重复读取同一事件源：

```c
MsgId_t msg = MsgMap_Get();
AppSM_Run(msg);
SubSM_Run(msg);
MsgMap_Clear();
```

说明：

1. `MsgMap_Get()` 负责获取当前周期内的消息。
2. `AppSM_Run()` 处理主状态机。
3. `SubSM_Run()` 处理子状态机。
4. `MsgMap_Clear()` 在主循环末尾统一清消息。

## 状态机五段式

| 段位 | 名称 | 说明 |
| --- | --- | --- |
| I | switch-case 直写版 | 在 `main.c` 中直接编写状态机逻辑 |
| II | 状态行为外提版 | 每个状态拆成独立函数 |
| III | 模块化封装版 | 状态机封装为独立 `.h/.c`，本模板采用该方案 |
| IV | 函数指针版 | 使用函数指针组织状态跳转 |
| V | SysML / 嵌套状态机版 | 支持层次状态机与并发区域 |

当前模板采用 **状态机 III**，适合作为电赛项目的基础工程骨架。

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
├─ Hardware/
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
├─ docs/
└─ keil/
```

### 目录说明

- `Application/`：应用层逻辑，主要放状态机、消息映射、控制算法等代码。
- `Hardware/`：与硬件平台强相关的内容，建议集中放置底层驱动封装。
- `BSP/`：板级支持层，用于对接外设驱动和具体实例。
- `Board/`：板卡配置与平台相关文件。
- `docs/`：设计文档、说明文档、流程图等资料。
- `keil/`：Keil 相关工程文件或辅助文件。

## 单件三模块封装示例

模板中使用 LED 作为示例，展示“控制类 + 实体类 + 实例层”的组织方式：

```text
BSP/inc/bsp_led.h           # 控制类和实体类声明
BSP/src/bsp_led.c           # 控制类方法实现
BSP/src/bsp_led_instances.c # 具体实例：ledRun、ledError
```

### 设计约定

- 控制类统一操作实体指针。
- 实体类保存硬件资源、状态和回调。
- 多实例由同一控制对象管理。
- 回调允许为空，调用前必须判空。

## 使用方式

1. 复制整个工程文件夹，并修改为新的工程名。
2. 打开 Keil 工程文件：

   ```text
   keil\MSPM0G3507_Template_State_Five.uvprojx
   ```

3. Rebuild 工程。
4. 在 `MsgMap_Get()`、外部中断或按键处理中产生消息。
5. 在 `AppSM_Run()` 与 `SubSM_Run()` 中消费消息并完成业务逻辑。

## 编码建议

- 包内文件遵循“一个 `.c` 对应一个 `.h`”的组织方式。
- 头文件统一添加保护宏。
- 函数说明使用 Doxygen 风格注释。
- 常量集中定义，避免魔术数字。
- 寄存器操作和中断处理要补充必要注释。

## 适用场景

- 电赛项目快速搭建基础框架。
- 需要主状态机 + 子状态机协作的控制项目。
- 需要统一消息入口、统一状态调度的嵌入式工程。

## 备注

如果后续要严格贴合《规范性.md》，建议继续统一以下内容：

- 代码相关目录尽量收敛为 `Hardware` 和 `Application` 两个包。
- `main.c` 作为唯一主入口文件。
- 新增模块时保持函数、变量、类型、宏命名一致。
- 新增接口时补全 `@brief`、`@param`、`@retval`、`@note`。
