#ifndef GAME_STATE_WIDGET_H
#define GAME_STATE_WIDGET_H

#include <FL/Fl_Group.H>

class GameStateWidget : public Fl_Group
{
public:
    // 定义游戏状态枚举
    enum class State {
        Playing,         // 正在游戏中
        Dead,           // 玩家死亡
        Complete,       // 完成关卡
        Initialization  // 初始化界面
    };

private:
    typedef Fl_Group BaseClass;

public:
    GameStateWidget(int x, int y, int w, int h, const char* l = nullptr);
    GameStateWidget(const GameStateWidget&) = delete;
    ~GameStateWidget() noexcept;

    GameStateWidget& operator=(const GameStateWidget&) = delete;

    // 更新当前显示状态
    void update_state(State new_state)
    {
        m_current_state = new_state;
        redraw();
    }

    // 获取当前状态
    State get_current_state() const noexcept
    {
        return m_current_state;
    }

protected:
    void draw() override;

private:
    State m_current_state;

    // 绘制不同状态界面的辅助方法
    void draw_initialization();
    void draw_game_over();
    void draw_level_complete();
};

#endif // GAME_STATE_WIDGET_H 