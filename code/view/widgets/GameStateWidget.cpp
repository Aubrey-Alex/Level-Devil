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
        case State::AllComplete:
            draw_all_complete();
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
    int icon_y = y() + h() / 3 - 23;

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
    int person_width = 60;
    int person_height = 51;
    int person_x = icon_x + (icon_size - person_width) / 2;
    int person_y = icon_y + (icon_size - person_height) / 2 - 7;

    // 绘制小人
    fl_rectf(person_x + 25, person_y + 0, 14, 14);      
    fl_rectf(person_x + 12, person_y + 14, 34, 20); 
    fl_rectf(person_x + 19, person_y + 34, 27, 15);   
    fl_rectf(person_x + 4, person_y + 46, 29, 10);  
    fl_rectf(person_x + 45, person_y + 40, 10, 20);  

    // 绘制底部的锯齿形状
    fl_color(FL_BLACK);
    int tooth_width = 20;
    int tooth_height = 15;
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
    // int button_width = 120;
    // int button_height = 40;
    // int button_x = x() + (w() - button_width) / 2;
    // int button_y = icon_y + icon_size + 20;
    // // 按钮背景
    // fl_color(FL_WHITE);
    // fl_rectf(button_x, button_y, button_width, button_height);

    int button_width = 120;
    int button_height = 40;
    int button_x = x() + (w() - button_width) / 2;
    // 将按钮紧贴在图标下方，留出10像素间距
    int button_y = icon_y + icon_size + 20; 
    int radius = 10; // 圆角半径

    // 绘制圆角矩形背景
    fl_color(FL_WHITE);
    // 先画中间的主体部分
    fl_rectf(button_x + radius, button_y, button_width - 2*radius, button_height);
    // 再画左右两边的部分，以连接圆角
    fl_rectf(button_x, button_y + radius, button_width, button_height - 2*radius);
    // 最后用fl_pie画四个角的1/4圆
    fl_pie(button_x, button_y, radius*2, radius*2, 90, 180); // 左上角
    fl_pie(button_x + button_width - radius*2, button_y, radius*2, radius*2, 0, 90); // 右上角
    fl_pie(button_x, button_y + button_height - radius*2, radius*2, radius*2, 180, 270); // 左下角
    fl_pie(button_x + button_width - radius*2, button_y + button_height - radius*2, radius*2, radius*2, 270, 360); // 右下角

    // 按钮文字
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA_BOLD, 24);
    const char* text = "PLAY";
    int text_w = 0, text_h = 0;
    fl_measure(text, text_w, text_h);
    fl_draw(text, 
            button_x + (button_width - text_w) / 2,
            button_y + (button_height + text_h - 10) / 2);
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
    fl_draw(text, 
            x() + (w() - text_w) / 2,
            y() + (h() - text_h) / 2);

    // 修正提示文本
    fl_font(FL_HELVETICA, 20);
    const char* hint = "Press Enter to Restart";
    fl_measure(hint, text_w, text_h); // 复用变量，不要再声明
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
    fl_draw(text, 
            x() + (w() - text_w) / 2,
            y() + (h() - text_h) / 2);

    // 修正提示文本
    fl_font(FL_HELVETICA, 20);
    const char* hint = "Press Enter for Next Level";
    fl_measure(hint, text_w, text_h); // 复用变量，不要再声明
    fl_draw(hint,
            x() + (w() - text_w) / 2,
            y() + (h() + text_h) / 2 + 40);
}

void GameStateWidget::draw_all_complete()
{
    // 创建渐变背景 - 从右下角的蓝色到左上角的紫色
    for(int i = 0; i < h(); i++) {
        for(int j = 0; j < w(); j++) {
            double progress_x = (double)j / w();
            double progress_y = (double)i / h();
            double progress = (progress_x + progress_y) / 2.0;
            int r = 80 + (int)((147 - 80) * progress);
            int g = 80 + (int)((39 - 80) * progress);
            int b = 200 + (int)((143 - 200) * progress);
            fl_color(r, g, b);
            fl_point(x() + j, y() + i);
        }
    }
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA_BOLD, 48);
    const char* text = "CONGRATULATIONS!";
    int text_w = 0, text_h = 0;
    fl_measure(text, text_w, text_h);
    fl_draw(text, 
            x() + (w() - text_w) / 2,
            y() + (h() - text_h) / 2 - 40);

    fl_font(FL_HELVETICA_BOLD, 32);
    const char* subtext = "ALL LEVELS COMPLETE";
    fl_measure(subtext, text_w, text_h); // 复用变量，不要再声明
    fl_draw(subtext,
            x() + (w() - text_w) / 2,
            y() + (h() - text_h) / 2 + 20);

    fl_font(FL_HELVETICA, 20);
    const char* hint = "Press Enter to Exit";
    fl_measure(hint, text_w, text_h); // 复用变量，不要再声明
    fl_draw(hint,
            x() + (w() - text_w) / 2,
            y() + (h() + text_h) / 2 + 60);
}