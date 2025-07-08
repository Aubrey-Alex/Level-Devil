# Level Devil 小游戏

## 项目简介

Level Devil 是一个基于现代 C++ 和 MVVM 架构开发的 2D 平台动作游戏。玩家需要在充满陷阱和动态障碍的关卡中，控制角色到达终点门口。项目注重模块解耦、工程自动化和团队协作，支持跨平台构建和自动化测试。

## 主要特性
- 经典 2D 平台跳跃玩法，关卡包含动态消失墙、隐形刺、移动陷阱等机制
- MVVM 架构，代码高内聚低耦合，易于扩展和维护
- 关卡数据驱动，支持 JSON 配置自定义关卡
- FLTK 实现高效跨平台 GUI 渲染
- Google Test 单元测试与集成测试，保障代码质量
- GitHub Actions 持续集成，自动化构建、测试与打包

## 架构说明

本项目采用 MVVM（Model-View-ViewModel）架构，主要模块如下：

- **Model**：实体、地图、物理逻辑与碰撞检测（`code/model/`）
- **ViewModel**：命令与通知桥梁，解耦 UI 与数据（`code/view_model/`）
- **View**：界面渲染与用户输入（`code/view/`）
- **App**：应用入口与主控逻辑（`code/app/`）
- **Common**：通用类型、工具与通知机制（`code/common/`）
- **Tests**：Google Test 测试用例（`code/tests/`）

## 依赖与环境

- C++17 及以上
- [CMake](https://cmake.org/) >= 3.16
- [vcpkg](https://github.com/microsoft/vcpkg) 包管理器
- [FLTK](https://www.fltk.org/)（GUI）
- [nlohmann-json](https://github.com/nlohmann/json)（关卡数据）
- [Google Test](https://github.com/google/googletest)（测试）

依赖通过 vcpkg 自动管理，详见 `vcpkg.json`。

## 构建与运行

### Windows 一键构建与运行

推荐使用 `command.bat` 脚本自动完成环境配置、构建和运行：

```bat
command.bat
```

该脚本会：
- 设置 vcpkg 环境变量
- 配置 CMake 工具链
- 创建 build 目录并生成 Visual Studio 解决方案
- 编译项目
- 运行游戏主程序

如已完成一次 CMake 配置，可直接用 `make.bat` 增量编译并运行：

```bat
make.bat
```

### 手动构建

1. 安装 vcpkg 并配置环境变量（见 `command.bat`）
2. 安装依赖：
   ```sh
   vcpkg install
   ```
3. 生成构建目录并编译：
   ```sh
   mkdir build
   cd build
   cmake .. -G "Visual Studio 17 2022" -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
   cmake --build .
   ```
4. 运行主程序：
   ```sh
   build\code\Debug\LevelDevil.exe
   ```

## 测试方法

- 所有测试用例位于 `code/tests/`，使用 Google Test 编写
- 构建后自动生成测试可执行文件
- 可通过 CTest 或直接运行测试二进制进行测试

```sh
cd build
ctest
```

或

```sh
build\code\tests\Debug\tests.exe
```

## 目录结构

```plaintext
Level-Devil/
├── code/
│   ├── app/           # 应用入口与主控逻辑
│   ├── common/        # 通用类型与工具
│   ├── model/         # 游戏数据与物理逻辑
│   ├── view_model/    # 视图模型，命令与通知桥梁
│   ├── view/          # 界面与用户交互
│   └── tests/         # 单元与集成测试
├── doc/               # 文档与报告
├── images/            # 游戏截图与流程图
├── CMakeLists.txt     # CMake 配置
├── vcpkg.json         # vcpkg 依赖配置
├── command.bat        # 一键构建脚本
├── make.bat           # 增量编译脚本
└── Readme.md
```

## 主要贡献者

- 张皓珉：App 和 Common 层实现，CI/CD 流程配置，测试集开发，界面美化
- 张晓航：View 层开发，输入与渲染优化，关卡与实体机制扩展
- 杨远航：Model 和 ViewModel 层开发，物理逻辑与关卡系统，测试与文档

## 成果截图

游戏部分界面如下：

![游戏开始界面](doc/结项报告/images/image.png)
![第一关：隐形的刺](doc/结项报告/images/image%20copy%202.png)
![第二关：地面靠近时消失](doc/结项报告/images/image%20copy%203.png)
![第三关：会移动的刺](doc/结项报告/images/image%20copy%204.png)
![过关界面](doc/结项报告/images/image%20copy%208.png)
![失败界面](doc/结项报告/images/image%20copy%209.png)
![通关界面](doc/结项报告/images/image%20copy%2010.png)

CI/CD 与测试流程：

![build过程展示](doc/结项报告/images/image%20copy%2014.png)
![test过程展示](doc/结项报告/images/image%20copy%2015.png)
![package过程展示](doc/结项报告/images/image%20copy%2016.png)

## 致谢

感谢指导老师袁昕的悉心指导，感谢团队成员的共同努力。感谢开源社区提供的 CMake、vcpkg、FLTK、nlohmann-json、Google Test 等优秀工具和库。

