# smartwatch

基于 STM32F401 + FreeRTOS + LVGL 的智能手表工程。

## 硬件平台

| 组件 | 型号 | 说明 |
|------|------|------|
| MCU | STM32F401RET6 | Cortex-M4, 84MHz |
| 显示屏 | GC9A01 | 240×240 圆形 TFT-LCD, SPI 接口 |
| 触摸屏 | CST816D | 电容触摸, I²C 接口 |
| 时钟源 | HSE 25MHz → PLL → SYSCLK 84MHz | APB1 42MHz, FLASH_LATENCY_2 |
| FPU | 已启用 | `configENABLE_FPU = 1` |

## 软件架构

```
┌─────────────────────────────┐
│        Application          │
│   (main.c / UI Tasks)       │
├─────────────────────────────┤
│          LVGL v8            │
│    (lv_timer_handler)       │
├─────────────────────────────┤
│        FreeRTOS             │
│   (CMSIS-RTOS v2)           │
├─────────────────────────────┤
│      STM32 HAL Drivers      │
│   (SPI / I²C / GPIO / RCC)  │
├─────────────────────────────┤
│         Hardware             │
│  STM32F401RET6 + GC9A01    │
│       + CST816D              │
└─────────────────────────────┘
```

### 技术栈

- **操作系统**：FreeRTOS (CMSIS-RTOS v2), `configTICK_RATE_HZ = 1000`
- **图形库**：LVGL v8.x
- **工具链**：STM32CubeIDE, GCC ARM
- **HAL 库**：STM32F4xx HAL Drivers

## 目录结构

```
smartwatch/
├── Core/
│   ├── Inc/                    # 头文件
│   │   ├── FreeRTOSConfig.h    # FreeRTOS 配置
│   │   ├── lcd_gc9a01.h        # LCD 驱动头文件
│   │   ├── cst816d.h           # 触摸驱动头文件
│   │   └── main.h
│   ├── Src/
│   │   ├── main.c              # 主程序（初始化、任务创建）
│   │   ├── lcd_gc9a01.c        # GC9A01 LCD 驱动
│   │   ├── cst816d.c           # CST816D 触摸驱动
│   │   └── ...
│   └── Startup/
├── Drivers/                    # STM32 HAL 驱动
│   ├── STM32F4xx_HAL_Driver/
│   └── CMSIS/
├── Middlewares/                # FreeRTOS 中间件
├── lvgl/                       # LVGL 图形库
│   └── src/                    # LVGL 核心源码
├── .gitignore
├── smartwatch.ioc              # STM32CubeMX 工程配置
├── STM32F401RETX_FLASH.ld      # Flash 链接脚本
└── STM32F401RETX_RAM.ld        # RAM 链接脚本
```

## 引脚分配

### SPI — GC9A01 LCD

| 信号 | 引脚 | GPIO |
|------|------|------|
| SCL | PA5 | SPI1_SCK |
| SDA | PA7 | SPI1_MOSI |
| DC | PB0 | GPIO 输出 |
| RST | PB1 | GPIO 输出 |
| CS | PA4 | GPIO 输出 |
| BL | PA6 | GPIO 输出 (背光 PWM) |

### I²C — CST816D 触摸

| 信号 | 引脚 | GPIO |
|------|------|------|
| SCL | PB6 | 软件 I²C |
| SDA | PB7 | 软件 I²C |
| INT | PB9 | 外部中断 |
| RST | PB10 | GPIO 输出 |

> **注意**：CST816D 使用软件 I²C 实现，PB6/PB7 由驱动直接管理。`MX_I2C1_Init()` 已被注释，PB9/PB10 已从 `MX_GPIO_Init` 中移除，避免双重初始化冲突。

## 时钟配置

```
HSE (25MHz 外部晶振)
  │
  └── PLL (×336, /8, /2)
        │
        └── SYSCLK = 84MHz
              ├── HCLK = 84MHz
              ├── APB1 = 42MHz (÷2)
              └── APB2 = 84MHz
```

配置位于 `main.c` 的 `SystemClock_Config()` 函数中，`FLASH_LATENCY = 2`。

## 构建与烧录

### 前置要求

- STM32CubeIDE 1.x+
- ARM GCC 工具链（随 CubeIDE 安装）

### 构建步骤

1. 用 STM32CubeIDE 打开工程目录 `smartwatch/`
2. 右键工程 → **Build Project**（或 `Ctrl+B`）
3. 构建产物位于 `Debug/` 目录：`smartwatch.elf` / `smartwatch.hex` / `smartwatch.bin`

### 烧录

通过 ST-Link / J-Link 连接开发板，在 CubeIDE 中点击 **Run**（或 `F11`）下载并调试。

> **注意**：首次构建前，建议在 CubeIDE 中 **Project → Clean** 后重新编译，确保 Makefile 路径正确。

## 运行流程

```
上电复位
  │
  ├── HAL_Init()
  ├── SystemClock_Config()    ← 配置 84MHz
  ├── MX_GPIO_Init()
  ├── MX_SPI1_Init()
  ├── LCD 初始化 (GC9A01)     ← 使用 HAL_Delay()
  ├── 触摸初始化 (CST816D)    ← 使用 HAL_Delay()
  ├── 创建 FreeRTOS 任务
  │     ├── LVGL Task (lv_timer_handler)
  │     └── Touch Task
  └── osKernelStart()         ← 启动调度器
```

## 修复记录

以下问题已在 `smartwatch2` 中修复：

| # | 严重度 | 问题描述 | 修复方案 |
|---|--------|---------|---------|
| 1 | 🔴 | `osDelay()` 在调度器启动前调用，LCD/触摸初始化时序不可靠 | `lcd_gc9a01.c` 4处 + `cst816d.c` 21处 → `HAL_Delay()` |
| 2 | 🔴 | Makefile 链接脚本路径 `smartwatch\smartwatch\` 重复嵌套 | 修正为单层路径 |
| 3 | 🟡 | `configENABLE_FPU=0` 但 FPU 指令已启用 | `FreeRTOSConfig.h`: → 1 |
| 4 | 🟡 | PB9/PB10 和 PB6/PB7 被 HAL 和驱动双重初始化 | 从 `MX_GPIO_Init` 移除，注释 `MX_I2C1_Init()` |
| 5 | 🟡 | `lv_task_handler()` 已弃用 | → `lv_timer_handler()` |
| 6 | 🟡 | 仅使用 HSI 16MHz，未启用 PLL | 配置 HSE → PLL → 84MHz |

## 开发注意事项

1. **延时函数**：FreeRTOS 启动前使用 `HAL_Delay()`，启动后在任务中使用 `osDelay()`。
2. **触摸驱动**：CST816D 使用软件 I²C，I²C1 硬件外设未启用，勿在 CubeMX 中重新使能 I²C1。
3. **FPU**：`FreeRTOSConfig.h` 中 `configENABLE_FPU` 需保持为 1，与编译器 FPU 选项一致。
4. **LVGL 配置**：`lv_conf.h` 位于 `lvgl/` 目录，可根据需求调整缓冲区大小、颜色深度等参数。
5. **链接脚本**：如通过 CubeMX 重新生成代码，请检查 Makefile 中链接脚本路径是否正确。

## 许可证

本项目仅用于学习参考。
