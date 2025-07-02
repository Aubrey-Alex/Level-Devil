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

    if (pThis->m_next_step_command != nullptr) {
        pThis->m_next_step_command(deltaTime); // Pass deltaTime (float)
    }
    Fl::repeat_timeout(deltaTime, &timeout_cb, pThis);
}

// 实现 FLTK 事件处理函数
int MainWindow::handle(int event) {
    printf("event: %d, key: %d\n", event, Fl::event_key()); // 调试输出
    switch (event) {
    case FL_KEYDOWN:
        if (Fl::event_key() == 'a' || Fl::event_key() == 'A') {
            if (m_start_move_left_command) m_start_move_left_command();
            return 1;
        } else if (Fl::event_key() == 'd' || Fl::event_key() == 'D') {
            if (m_start_move_right_command) m_start_move_right_command();
            return 1;
        } else if (Fl::event_key() == 'w' || Fl::event_key() == 'W') {
            if (m_jump_command) m_jump_command();
            return 1;
        }
        break;
    case FL_KEYUP:
        if (Fl::event_key() == 'a' || Fl::event_key() == 'A' || Fl::event_key() == 'd' || Fl::event_key() == 'D') {
            if (m_stop_move_command) m_stop_move_command();
            return 1;
        }
        break;
    default:
        break;
    }
    return Fl_Double_Window::handle(event);
}