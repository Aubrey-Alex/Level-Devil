#include "GameStateWidget.h"
#include <FL/fl_draw.h>

GameStateWidget::GameStateWidget(int x, int y, int w, int h, const char* l)
    : Fl_Group(x, y, w, h, l), m_current_state(State::Initialization)
{
    end();
    box(FL_NO_BOX);
}

GameStateWidget::~GameStateWidget() noexcept
{
}

void GameStateWidget::draw()
{
    // 根据游戏状态调用不同的绘制方法
    switch (m_current_state) {
        case State::Dead:
            draw_game_over();
            break;
        case State::Complete:
            draw_level_complete();
            break;
        case State::Initialization:
            draw_initialization();
            break;
        default:
            break;
    }
}

void GameStateWidget::draw_initialization()
{
    // 创建渐变背景 - 从右下角的红色到左上角的紫色
    for(int i = 0; i < h(); i++) {
        for(int j = 0; j < w(); j++) {
            // 计算渐变色
            double progress_x = (double)j / w();
            double progress_y = (double)i / h();
            double progress = (progress_x + progress_y) / 2.0;
            
            // 从紫色 (147, 39, 143) 渐变到红色 (229, 57, 53)
            int r = 147 + (int)((229 - 147) * progress);
            int g = 39 + (int)((57 - 39) * progress);
            int b = 143 + (int)((53 - 143) * progress);
            
            fl_color(r, g, b);
            fl_point(x() + j, y() + i);
        }
    }

    // 绘制游戏图标（黑色小人和黄色背景）
    int icon_size = 120;
    int icon_x = x() + (w() - icon_size) / 2;
    int icon_y = y() + h() / 3;

    // 绘制黄色背景方块
    fl_color(FL_YELLOW);
    fl_begin_complex_polygon();
    fl_vertex(icon_x, icon_y);
    fl_vertex(icon_x + icon_size, icon_y);
    fl_vertex(icon_x + icon_size, icon_y + icon_size);
    fl_vertex(icon_x, icon_y + icon_size);
    fl_end_complex_polygon();

    // 绘制黑色小人
    fl_color(FL_BLACK);
    int person_width = 40;
    int person_height = 40;
    int person_x = icon_x + (icon_size - person_width) / 2;
    int person_y = icon_y + (icon_size - person_height) / 2;

    // 绘制小人
    fl_rectf(person_x + 14, person_y, 10, 10);      // 头
    fl_rectf(person_x + 12, person_y + 10, 14, 16); // 身体
    fl_rectf(person_x + 8, person_y + 10, 4, 14);   // 左臂
    fl_rectf(person_x + 26, person_y + 10, 4, 14);  // 右臂
    fl_rectf(person_x + 12, person_y + 26, 6, 12);  // 左腿
    fl_rectf(person_x + 20, person_y + 26, 6, 12);  // 右腿

    // 绘制底部的锯齿形状
    fl_color(FL_BLACK);
    int tooth_width = 20;
    int tooth_height = 10;
    int teeth_count = icon_size / tooth_width;
    int teeth_start_x = icon_x;
    int teeth_y = icon_y + icon_size - tooth_height;

    for(int i = 0; i < teeth_count; i++) {
        fl_begin_complex_polygon();
        fl_vertex(teeth_start_x + i * tooth_width, icon_y + icon_size);
        fl_vertex(teeth_start_x + (i + 0.5) * tooth_width, teeth_y);
        fl_vertex(teeth_start_x + (i + 1) * tooth_width, icon_y + icon_size);
        fl_end_complex_polygon();
    }

    // 绘制"PLAY"按钮
    int button_width = 120;
    int button_height = 40;
    int button_x = x() + (w() - button_width) / 2;
    int button_y = icon_y + icon_size + 20;

    // 按钮背景
    fl_color(FL_WHITE);
    fl_rectf(button_x, button_y, button_width, button_height);

    // 按钮文字
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA_BOLD, 24);
    const char* text = "PLAY";
    int text_w = 0, text_h = 0;
    fl_measure(text, text_w, text_h);
    fl_draw(text, 
            button_x + (button_width - text_w) / 2,
            button_y + (button_height + text_h) / 2);

    // 绘制底部标题
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA_BOLD, 32);
    const char* title = "PIXEL PATH";
    fl_measure(title, text_w, text_h);
    fl_draw(title,
            x() + (w() - text_w) / 2,
            button_y + button_height + 40 + text_h);
}

void GameStateWidget::draw_game_over()
{
    // 绘制深红色背景
    fl_color(FL_DARK_RED);
    fl_rectf(x(), y(), w(), h());

    // 设置文本属性
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA_BOLD, 48);
    
    // 绘制"GAME OVER"文本
    const char* text = "GAME OVER";
    int text_w = 0, text_h = 0;
    fl_measure(text, text_w, text_h);
    
    // 在窗口中央绘制文本
    fl_draw(text, 
            x() + (w() - text_w) / 2,
            y() + (h() + text_h) / 2);

    // 添加提示文本
    fl_font(FL_HELVETICA, 20);
    const char* hint = "Press R to Restart";
    fl_measure(hint, text_w, text_h);
    fl_draw(hint,
            x() + (w() - text_w) / 2,
            y() + (h() + text_h) / 2 + 40);
}

void GameStateWidget::draw_level_complete()
{
    // 绘制金色背景
    fl_color(FL_YELLOW);
    fl_rectf(x(), y(), w(), h());

    // 设置文本属性
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA_BOLD, 48);
    
    // 绘制"LEVEL COMPLETE!"文本
    const char* text = "LEVEL COMPLETE!";
    int text_w = 0, text_h = 0;
    fl_measure(text, text_w, text_h);
    
    // 在窗口中央绘制文本
    fl_draw(text, 
            x() + (w() - text_w) / 2,
            y() + (h() + text_h) / 2);

    // 添加提示文本
    fl_font(FL_HELVETICA, 20);
    const char* hint = "Press N for Next Level";
    fl_measure(hint, text_w, text_h);
    fl_draw(hint,
            x() + (w() - text_w) / 2,
            y() + (h() + text_h) / 2 + 40);
} 