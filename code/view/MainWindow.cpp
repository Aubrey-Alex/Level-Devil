#include "../common/property_ids.h"
#include "MainWindow.h"
#include <FL/Fl.H> 

// Constructor needs to initialize m_board
MainWindow::MainWindow(int w, int h, const char *title) : Fl_Double_Window(w, h, title),
    m_board(0, 0, w, h) // CORRECTED: Initialize m_board here
{
    end(); // Call end() after adding all children

    Fl::add_timeout(0.016, &timeout_cb, this); // Use a smaller timeout for smoother updates (approx 60 FPS)
    this->take_focus(); // 自动获取焦点，便于捕获键盘事件
}

MainWindow::~MainWindow() noexcept
{
}

//notification
PropertyNotification MainWindow::get_notification()
{
    // MODIFIED: Change lambda parameter type from uint32_t to PropertyID
    return [this](PropertyID id)->void // CORRECTED: Lambda now accepts PropertyID
        {
            switch (id) {
            case PropertyID::PlayerPositionChanged: // Use PropertyID directly

                m_board.redraw();
                break;
            default:
                break;
            }
        };
}

//callbacks
void MainWindow::timeout_cb(void* pv)
{
    MainWindow* pThis = (MainWindow*)pv;
    // Calculate deltaTime since last frame. For a fixed timeout, it's just the timeout value.
    float deltaTime = 0.016f; // Corresponds to the Fl::add_timeout value

    pThis->game_update(); // Call game_update to handle input and update game world
    Fl::repeat_timeout(deltaTime, &timeout_cb, pThis);
}

// game_update 函数
void MainWindow::game_update()
{
    // --- 在这里使用 Fl::get_key() 查询当前按键状态 ---

    // 查询水平移动
    bool is_moving_left = Fl::get_key('a') || Fl::get_key('A') || Fl::get_key(FL_Left);
    bool is_moving_right = Fl::get_key('d') || Fl::get_key('D') || Fl::get_key(FL_Right);

    // 根据查询结果调用命令
    if (!is_moving_left && !is_moving_right || is_moving_left && is_moving_right)
    {
        if (m_stop_move_command) {
            m_stop_move_command();
            // printf("stop\n");
        }
    }
    else if(is_moving_left) 
    {
        if (m_start_move_left_command) {
            m_start_move_left_command();
            // printf("move left\n");
        }
    }
    else if (is_moving_right)  // 改为独立的if，移除else
    {
        if (m_start_move_right_command) {
            m_start_move_right_command();
            // printf("move right\n");
        }
    }

    // 查询跳跃键
    if (Fl::get_key('w') || Fl::get_key('W') || Fl::get_key(FL_Up))
    {
        if (m_jump_command) {
            m_jump_command();
            // printf("jump\n");
        }
    }

    // --- 在处理完所有输入后，统一驱动游戏世界更新一次 ---
    if (m_next_step_command)
    {
        m_next_step_command(); // 假设 m_next_step_command 驱动 ViewModel 和 Model 的 update
    }

    // 可以在这里加上重绘请求，以更新画面
    redraw();
}