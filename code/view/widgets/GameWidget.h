#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include "../../common/game_map.h"
#include <FL/Fl_Group.H> 
#include <FL/Fl_Box.H>

class GameWidget : public Fl_Group
{
private:
	typedef Fl_Group  BaseClass;

public:
	GameWidget(int x, int y, int w, int h, const char *l = nullptr);
	GameWidget(const GameWidget&) = delete;
	~GameWidget() noexcept;

	GameWidget& operator=(const GameWidget&) = delete;

//properties
	void set_map(const GameMap* pmap) noexcept
	{
		m_pmap = pmap;
	}
	
	// 设置死亡次数
	void set_death_count(int count) noexcept
	{
		m_death_count = count;
		redraw(); // 重绘以更新显示
	}

protected:
	void draw() override;

private:
	Fl_Box* m_box_person;
	const GameMap* m_pmap;
	int m_death_count; // 死亡次数

	// 游戏核心界面绘制
	void draw_game();
	// 绘制死亡次数
	void draw_death_count();
};

#endif // GAME_WIDGET_H