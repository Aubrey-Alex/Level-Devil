#include "GameWidget.h"
#include <FL/fl_draw.h>
#include <FL/Fl.H>

GameWidget::GameWidget(int x, int y, int w, int h, const char *l) : Fl_Group(x, y, w, h, l)
{
    m_box_person = new Fl_Box(x, y, w, h, l); // 初始化Fl_Box
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
    // Draw background (sky) - top two-thirds as yellow
    fl_rectf(x(), y(), w(), h() * 2 / 3, FL_YELLOW);

    // Draw ground - bottom one-third as black
    fl_rectf(x(), y() + h() * 2 / 3, w(), h() / 3, FL_BLACK);

    if (m_pmap != nullptr) {
        for (size_t i = 0; i < m_pmap->get_size(); i++) {
            const auto& actor(m_pmap->get_at(i));

            // Calculate the top-left drawing coordinates for the entity's bounding box.
            // actor.x and actor.y are relative to the map's origin, which is assumed
            // to be aligned with the GameWidget's origin (x(), y()).
            int entity_drawing_x = x() + (int)actor.pos.x;
            int entity_drawing_y = y() + (int)actor.pos.y;

            switch (actor.type) {
                case 'P': // Draw player as a black stick figure
                {
                    fl_color(FL_RED); // Set player color to red

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
                    fl_color(FL_DARK_RED); 
                    fl_rectf(entity_drawing_x, entity_drawing_y, actor.w, actor.h);
                    break;
                }
                case 'D': {
                    fl_color(FL_BLACK); 
                    fl_rect(entity_drawing_x, entity_drawing_y, 40, 40); 
                    fl_color(FL_BLUE); 
                    fl_rectf(entity_drawing_x + 1, entity_drawing_y + 1, 38, 38); 
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
    // Call base class to draw children widgets if any (uncomment if applicable)
    // BaseClass::draw_children();
}