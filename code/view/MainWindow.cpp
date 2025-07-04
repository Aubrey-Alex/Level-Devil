#include "../common/property_ids.h"
#include "MainWindow.h"
#include <FL/Fl.H> 

// Constructor needs to initialize m_board
MainWindow::MainWindow(int w, int h, const char *title) : Fl_Double_Window(w, h, title),
    m_board(0, 0, w, h),
    m_state_widget(0, 0, w, h)
{
    end(); // Call end() after adding all children
    
    // 设置初始状态
    m_state_widget.update_state(GameStateWidget::State::Initialization);

    Fl::add_timeout(DELTA_TIME, &timeout_cb, this); // Use a smaller timeout for smoother updates (approx 60 FPS)
    this->take_focus(); // 自动获取焦点，便于捕获键盘事件
}

MainWindow::~MainWindow() noexcept
{
}

//callbacks
void MainWindow::timeout_cb(void* pv)
{
    MainWindow* pThis = (MainWindow*)pv;
    // Calculate deltaTime since last frame. For a fixed timeout, it's just the timeout value.
    float deltaTime = DELTA_TIME; // Corresponds to the Fl::add_timeout value
    
    pThis->game_update(); // Call game_update to handle input and update game world
    Fl::repeat_timeout(deltaTime, &timeout_cb, pThis);
}

// game_update 函数
void MainWindow::game_update()
{
    // 如果当前是初始化状态，只处理Enter键
    if (m_state_widget.get_current_state() == GameStateWidget::State::Initialization)
    {
        if (Fl::get_key(FL_Enter) || Fl::get_key(FL_KP_Enter))
        {
            if (m_start_game_command) {
                m_start_game_command();
            }
            return;
        }
        return;  // 在初始化状态下不处理其他输入
    }

    // 如果当前是游戏状态，处理输入
    if (m_state_widget.get_current_state() == GameStateWidget::State::Playing)
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
            }
        }
        else if(is_moving_left) 
        {
            if (m_start_move_left_command) {
                m_start_move_left_command();
            }
        }
        else if (is_moving_right)
        {
            if (m_start_move_right_command) {
                m_start_move_right_command();
            }
        }
        
        // 查询跳跃键
        if (Fl::get_key('w') || Fl::get_key('W') || Fl::get_key(FL_Up))
        {
            if (m_jump_command) {
                m_jump_command();
            }
        }
        
        // --- 在处理完所有输入后，统一驱动游戏世界更新一次 ---
        if (m_next_step_command)
        {
            m_next_step_command();
        }
    }

    if (m_state_widget.get_current_state() == GameStateWidget::State::Dead
        || m_state_widget.get_current_state() == GameStateWidget::State::Complete
        || m_state_widget.get_current_state() == GameStateWidget::State::AllComplete)
    {
        if (Fl::get_key(FL_Enter) || Fl::get_key(FL_KP_Enter))
        {
            if (m_state_widget.get_current_state() == GameStateWidget::State::AllComplete) {
                exit(0);
            } else {
                if (m_reset_game_command) {
                    m_reset_game_command();
                }
                m_state_widget.update_state(GameStateWidget::State::Playing);
                m_state_widget.hide();
                m_board.show();
            }
            redraw();
            return;
        }
        return;
    }


}

//notification
PropertyNotification MainWindow::get_notification()
{
    return [this](PropertyID id)->void
        {
            switch (id) {
            case PropertyID::PlayerPositionChanged:
                m_state_widget.update_state(GameStateWidget::State::Playing);
                m_state_widget.hide();
                m_board.show();
                break;
            case PropertyID::PlayerDead:
                m_state_widget.update_state(GameStateWidget::State::Dead);
                m_board.hide();
                m_state_widget.show();
                break;
            case PropertyID::LevelComplete:
                m_state_widget.update_state(GameStateWidget::State::Complete);
                m_board.hide();
                m_state_widget.show();
                break;
            case PropertyID::AllLevelComplete:
                m_state_widget.update_state(GameStateWidget::State::AllComplete);
                m_board.hide();
                m_state_widget.show();
                break;
            case PropertyID::Initialization:
                m_state_widget.update_state(GameStateWidget::State::Initialization);
                m_board.hide();
                m_state_widget.show();
                break;
            case PropertyID::NoChange:
                break;
            default:
                break;
            }
            redraw();
        };
}