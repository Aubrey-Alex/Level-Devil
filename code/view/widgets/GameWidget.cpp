#include "GameWidget.h"
#include <FL/fl_draw.h>
#include <FL/Fl.H>

GameWidget::GameWidget(int x, int y, int w, int h, const char *l) : Fl_Group(x, y, w, h, l)
{
    m_box_person = new Fl_Box(x, y, w, h, l);
    end();
    box(FL_NO_BOX);
    m_pmap = nullptr;
}

GameWidget::~GameWidget() noexcept
{
    delete m_box_person;
}

void GameWidget::draw()
{
    draw_game();
}

void GameWidget::draw_game()
{
    // Draw background (sky) - top two-thirds as yellow
    fl_color(255,193,69);
    fl_rectf(x(), y(), w(), h() * 2 / 3);

    if (m_pmap != nullptr) {
        for (size_t i = 0; i < m_pmap->get_size(); i++) {
            const auto& actor(m_pmap->get_at(i));

            // Calculate the top-left drawing coordinates for the entity's bounding box.
            int entity_drawing_x = x() + (int)actor.pos.x;
            int entity_drawing_y = y() + (int)actor.pos.y;

            switch (actor.type) {
                case 'P': // Draw player as a black stick figure
                {
                    fl_color(FL_BLACK); // Set player color to red

                    // 以40x40为基准绘制stickman
                    // Head (10x10 pixels) - centered horizontally
                    fl_rectf(entity_drawing_x + 14, entity_drawing_y, 10, 10);
                    // Body (14x16 pixels) - below head
                    fl_rectf(entity_drawing_x + 12, entity_drawing_y + 10, 14, 16);
                    // Left Arm (4x14 pixels) - extending from left side of body
                    fl_rectf(entity_drawing_x + 8, entity_drawing_y + 10, 4, 14);
                    // Right Arm (4x14 pixels) - extending from right side of body
                    fl_rectf(entity_drawing_x + 26, entity_drawing_y + 10, 4, 14);
                    // Left Leg (6x12 pixels) - extending from bottom-left of body
                    fl_rectf(entity_drawing_x + 12, entity_drawing_y + 26, 6, 12);
                    // Right Leg (6x12 pixels) - extending from bottom-right of body
                    fl_rectf(entity_drawing_x + 20, entity_drawing_y + 26, 6, 12);

                    break;
                }
                case 'W': {
                    fl_color(137,99,28);
                    fl_rectf(entity_drawing_x, entity_drawing_y, actor.w, actor.h);
                    break;
                }
                case 'H': { // 隐藏墙体显示为背景色
                    fl_color(255,193,69);
                    fl_rectf(entity_drawing_x, entity_drawing_y, actor.w, actor.h);
                    break;
                }
                // "D" for Door
                case 'D': { 
                    // --- 设定40x40的尺寸 ---
                    // 空处的尺寸为2
                    const int space = 3; 
                    const int width = 40;
                    const int height = 40;
                    // 为了方便计算，设定绘图原点为左上角
                    const int ox = entity_drawing_x;
                    const int oy = entity_drawing_y;
        
                    // --- 颜色定义 ---
                    const unsigned char frame_r = 137, frame_g = 99, frame_b = 28;       // 暗棕色门框
                    const unsigned char opening_r = 150, opening_g = 168, opening_b = 126; // 灰绿色门洞
        
                    // 1. 绘制暗棕色的门框 (Frame)
                    fl_color(frame_r, frame_g, frame_b);
                    
                    // 门框左立柱 
                    fl_rectf(ox + 0*space,  oy + 2*space,  2*space,  height - 2*space);
                    // 门框右立柱 
                    fl_rectf(ox + width - 2*space, oy + 2*space,  2*space,  height - 2*space);
        
                    // 门框的弧形顶部 
                    // 最顶层 
                    fl_rectf(ox + 2*space,  oy + 0*space,  width - 4*space,  2*space);
                    // 左中间层 
                    fl_rectf(ox + 1*space,  oy + 1*space,  2*space,  2*space);
                    // 右中间层 
                    fl_rectf(ox + width - 3*space,  oy + 1*space,  2*space,  2*space);
        
                    // 灰绿色的门洞 
                    fl_color(opening_r, opening_g, opening_b);
        
                    // 门洞的主体部分 (一个14x13的矩形)
                    fl_rectf(ox + 2*space,  oy + 3*space,  width - 4*space, height - 3*space);
                    fl_rectf(ox + 3*space,  oy + 2*space,  width - 6*space, 1*space);
        
                    break;
                }
                case 'S': {
                    fl_color(FL_BLACK);
                    fl_polygon(entity_drawing_x, entity_drawing_y + 13, 
                               entity_drawing_x + 9, entity_drawing_y,   
                               entity_drawing_x + 18, entity_drawing_y + 13); 
                    fl_polygon(entity_drawing_x + 18, entity_drawing_y + 13,
                               entity_drawing_x + 27, entity_drawing_y,
                               entity_drawing_x + 36, entity_drawing_y + 13);
                    fl_polygon(entity_drawing_x + 36, entity_drawing_y + 13,
                               entity_drawing_x + 45, entity_drawing_y,
                               entity_drawing_x + 54, entity_drawing_y + 13);
                    break;
                }
                default:
                    break;
            }
        }
    }
}