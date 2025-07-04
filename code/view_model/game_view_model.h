#ifndef GAME_VIEW_MODEL_H
#define GAME_VIEW_MODEL_H

#include "../common/notifier.h"
#include "../common/property_ids.h"
#include "../model/entity_model.h"
#include <functional>

class GameViewModel : public PropertyNotifier
{
public:
    // 定义游戏状态枚举
    enum class GameState {
        Playing,         // 正在游戏中
        Dead,           // 玩家死亡
        Complete,       // 完成关卡
        Initialization, // 初始化界面
        AllComplete     // 全部关卡完成
    };

    GameViewModel();
    ~GameViewModel() = default;

    // 状态转换方法
    void start_game();  // 从初始化状态转到游戏状态
    void game_over();   // 转到游戏结束状态
    void complete_level(); // 转到关卡完成状态
    void reset_game();    // 重置到初始化状态
    void pass_all_levels(); // 新增：全部关卡完成

    // 获取当前状态
    GameState get_game_state() const { return m_game_state; }

    // 通知相关
    void set_property_notify(PropertyNotification&& ntf);

    std::function<void()> getStartGameCommand() {
        return [this]() { this->start_game(); };
    }
    std::function<void()> getGameOverCommand() {
        return [this]() { this->game_over(); };
    }
    std::function<void()> getCompleteLevelCommand() {
        return [this]() { this->complete_level(); };
    }
    std::function<void()> getResetGameCommand() {
        return [this]() { this->reset_game(); };
    }
    std::function<void()> getPassAllLevelsCommand() {
        return [this]() { this->pass_all_levels(); };
    }
    
private:
    GameState m_game_state;
    PropertyNotification m_ntf;

    // 通知视图状态改变
    void notify_state_changed();
};

#endif // GAME_VIEW_MODEL_H
