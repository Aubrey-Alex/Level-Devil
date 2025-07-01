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
    

protected:
	void draw() override;

private:
	Fl_Box* m_box_person;

private:
	//properties
	const GameMap* m_pmap;
    
};

#endif // GAME_WIDGET_H