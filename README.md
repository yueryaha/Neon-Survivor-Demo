# 🎮 Neon Survivor (极简生存者)

![C++](https://img.shields.io/badge/C++-17-blue.svg?style=flat&logo=c%2B%2B)
![CMake](https://img.shields.io/badge/CMake-3.14+-brightgreen.svg?style=flat&logo=cmake)
![Raylib](https://img.shields.io/badge/Raylib-5.0-red.svg?style=flat)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)

**Neon Survivor** 是一款基于纯 C++ 和 Raylib 开发的 2D 俯视角生存射击游戏 Demo。本项目主要作为技术展示，侧重于**核心游戏循环 (Game Loop)**、**面向对象架构设计**、**内存安全**以及**基础物理碰撞**的实现。

> **展示动图** > *(这里请替换为你录制的游戏运行 GIF 动图链接，例如：`![Gameplay](assets/gameplay.gif)`)*

---

## ✨ 核心特性与技术亮点

本项目在一天内极速开发完成，摒弃了复杂的美术资产，专注于纯代码驱动的游戏性和底层逻辑实现：

* **现代化 C++ 实践**：使用 C++17 标准，采用 `std::vector` 管理游戏实体生命周期，并结合 `erase-remove_if` 惯用法实现实体（子弹、敌人、粒子）的延迟销毁，彻底避免了迭代器失效和内存泄漏问题。
* **无缝的构建体验**：利用 CMake 的 `FetchContent` 模块实现依赖自动管理。开发者无需在本地手动配置或预装第三方库，拉取代码后即可一键编译。
* **标准游戏循环与状态机**：严格分离了 `Update()`（逻辑更新）与 `Draw()`（渲染）阶段；实现了一个极简的有限状态机 (FSM) 来管理 `START_SCREEN`、`PLAYING` 和 `GAME_OVER` 状态的平滑切换。
* **帧率无关的物理移动**：所有运动逻辑（玩家移动、敌人寻路、子弹弹道、粒子消散）均深度解绑帧率，使用 `GetFrameTime() (Delta Time)` 进行插值计算，确保在不同性能设备上的物理表现一致。
* **自定义粒子系统**：从零实现了一个基于生命周期的粒子发射器，用于处理子弹命中时的视觉反馈 (Juiciness)。
* **动态寻路与碰撞检测**：实现了基础的向量数学（归一化与标量乘法）用于敌人索敌，并采用了圆与圆 (`CheckCollisionCircles`)、圆与矩形 (`CheckCollisionCircleRec`) 的混合碰撞检测。

---

## 📂 项目结构

```text
Neon-Survivor-Demo/
├── CMakeLists.txt      # CMake 构建脚本，包含 Raylib 自动拉取逻辑
├── main.cpp            # 游戏主循环、状态机、全局实体管理与碰撞结算
├── player.h/.cpp       # 玩家类 (输入处理、边界约束、渲染)
├── enemy.h/.cpp        # 敌人类 (动态索敌逻辑)
└── bullet.h/.cpp       # 子弹类 (弹道计算、生命周期管理)
````
---

## 🚀 编译与运行指南

本项目环境配置极其简单，仅需安装 [CMake](https://cmake.org/) 和支持 C++17 的编译器（如 MSVC, GCC, Clang）。

**1. 克隆仓库**
> git clone [https://github.com/你的用户名/Neon-Survivor-Demo.git](https://github.com/你的用户名/Neon-Survivor-Demo.git)
> cd Neon-Survivor-Demo

**2. 生成构建文件并拉取依赖**
> cmake -B build

**3. 编译并运行**
> cmake --build build
> .\build\Debug\NeonSurvivor.exe

---

## 🕹️ 游玩说明

* **移动**：使用 `W` `A` `S` `D` 或 `↑` `↓` `←` `→` 键控制蓝色方块移动。*(请确保输入法处于英文状态)*
* **战斗**：玩家会全自动扫描距离最近的敌人并开火。
* **目标**：面对移动速度和生成频率极高的“红点”尸潮，你需要利用走位拉扯空间，尽可能存活更长的时间并获取高分！

---

## 📝 开发者日记 (Dev Notes)

在开发过程中，最有趣的环节是**数值平衡 (Balancing)**。起初玩家处于“站桩无敌”的状态。为了提升游戏性，我将玩家射速设定为 0.2 秒/发，而敌人的生成频率设定为 0.15 秒/个，并且敌人的移动速度略低于子弹但极具压迫感。这种**非对称的速率设计**成功逼迫玩家必须进行动态走位，大幅提升了生存游戏的紧张感。
