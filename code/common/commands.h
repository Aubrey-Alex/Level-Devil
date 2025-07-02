#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <functional>

/**
 * @brief 定义了从View层发送到ViewModel层的各种命令。
 *
 * 这里使用C++11的std::function，以一种现代、灵活且类型安全的方式
 * 来实现命令模式。View层获取并执行这些命令对象，而不需要知道
 * ViewModel中具体实现这些命令的函数是什么。
 * 这份文件是View和ViewModel之间的核心"契约"之一。
 */

// 移动相关命令
using StartMoveLeftCommand = std::function<void()>;
using StartMoveRightCommand = std::function<void()>;
using StopMoveCommand = std::function<void()>;
using JumpCommand = std::function<void()>;

// // 游戏控制命令
// using PauseGameCommand = std::function<void()>;
// using ResumeGameCommand = std::function<void()>;
// using RestartLevelCommand = std::function<void()>;
// using QuitGameCommand = std::function<void()>;

// // UI控制命令
// using ShowMenuCommand = std::function<void()>;
// using HideMenuCommand = std::function<void()>;
// using ToggleDebugInfoCommand = std::function<void()>;

// // 关卡相关命令
// using LoadLevelCommand = std::function<void(int levelId)>;
// using SaveGameCommand = std::function<void()>;
// using LoadGameCommand = std::function<void()>;

#endif