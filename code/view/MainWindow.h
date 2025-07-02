#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "../common/frame.h"
#include "widgets/GameWidget.h"
#include <functional> 
#include <FL/Fl_Double_Window.H> // 必须有这一行，定义基类
#include <FL/Fl.H> // 用于处理 FLTK 事件，例如键盘事件

class MainWindow : public Fl_Double_Window
{
public:
    MainWindow(int w, int h, const char *title = nullptr);
    MainWindow(const MainWindow&) = delete;
    ~MainWindow() noexcept;

    MainWindow& operator=(const MainWindow&) = delete;

//commands
    // 定时更新命令（已存在）
    void set_next_step_command(std::function<void(float)>&& pn) noexcept
    {
        m_next_step_command = std::move(pn);
    }

    // ADDED: 设置移动和跳跃命令的setter函数
    void set_start_move_left_command(std::function<void()>&& cmd) noexcept { m_start_move_left_command = std::move(cmd); }
    void set_start_move_right_command(std::function<void()>&& cmd) noexcept { m_start_move_right_command = std::move(cmd); }
    void set_stop_move_command(std::function<void()>&& cmd) noexcept { m_stop_move_command = std::move(cmd); }
    void set_jump_command(std::function<void()>&& cmd) noexcept { m_jump_command = std::move(cmd); }


//notification
    PropertyNotification get_notification();

//methods
    GameWidget& get_board() noexcept
    {
        return m_board;
    }

protected:
//callbacks
    static void timeout_cb(void*);
    // ADDED: 重写 FLTK 的事件处理函数
    int handle(int event) override; 

private:
    GameWidget m_board;

private:
//commands
    std::function<void(float)> m_next_step_command;
    // ADDED: 存储移动和跳跃命令的成员变量
    std::function<void()> m_start_move_left_command;
    std::function<void()> m_start_move_right_command;
    std::function<void()> m_stop_move_command;
    std::function<void()> m_jump_command;
};

#endif