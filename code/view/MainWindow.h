#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "../common/notifier.h"
#include "widgets/GameWidget.h"
#include "widgets/GameStateWidget.h"
#include <functional> 
#include <FL/Fl_Double_Window.H>
#include <FL/Fl.H>

#define DELTA_TIME 0.008f

class MainWindow : public Fl_Double_Window
{
public:
    MainWindow(int w, int h, const char *title = nullptr);
    MainWindow(const MainWindow&) = delete;
    ~MainWindow() noexcept;

    MainWindow& operator=(const MainWindow&) = delete;

//commands
    // 定时更新命令
    void set_next_step_command(std::function<void()> &&cmd) noexcept { m_next_step_command = std::move(cmd); }

    // 设置移动和跳跃命令的setter函数
    void set_start_move_left_command(std::function<void()>&& cmd) noexcept { m_start_move_left_command = std::move(cmd); }
    void set_start_move_right_command(std::function<void()>&& cmd) noexcept { m_start_move_right_command = std::move(cmd); }
    void set_stop_move_command(std::function<void()>&& cmd) noexcept { m_stop_move_command = std::move(cmd); }
    void set_jump_command(std::function<void()>&& cmd) noexcept { m_jump_command = std::move(cmd); }
    
    // 添加游戏状态命令
    void set_start_game_command(std::function<void()>&& cmd) noexcept { m_start_game_command = std::move(cmd); }
    void set_game_over_command(std::function<void()>&& cmd) noexcept { m_game_over_command = std::move(cmd); }
    void set_complete_level_command(std::function<void()>&& cmd) noexcept { m_complete_level_command = std::move(cmd); }
    void set_reset_game_command(std::function<void()>&& cmd) noexcept { m_reset_game_command = std::move(cmd); }
    void set_pass_all_levels_command(std::function<void()>&& cmd) noexcept { m_pass_all_levels_command = std::move(cmd); } // 新增

//notification
    PropertyNotification get_notification();

//methods
    GameWidget& get_board() noexcept { return m_board; }
    GameStateWidget& get_state_widget() noexcept { return m_state_widget; }

protected:
//callbacks
    static void timeout_cb(void*);
    void game_update();

private:
    GameWidget m_board;
    GameStateWidget m_state_widget;

private:
//commands
    std::function<void()> m_next_step_command;
    std::function<void()> m_start_move_left_command;
    std::function<void()> m_start_move_right_command;
    std::function<void()> m_stop_move_command;
    std::function<void()> m_jump_command;
    std::function<void()> m_start_game_command;
    std::function<void()> m_game_over_command;
    std::function<void()> m_complete_level_command;
    std::function<void()> m_reset_game_command;
    std::function<void()> m_pass_all_levels_command; // 新增
};

#endif