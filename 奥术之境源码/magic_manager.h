#pragma once

#include "manager.h"
#include "magic.h"
#include "fireball_magic.h"
#include "burning_spell_magic.h"
#include "minor_healing_spell_magic.h"
#include "lighting_strike_magic.h"
#include "wind_spell_magic.h"
#include "lava_vortex_magic.h"
#include "zeus_fury_magic.h"

#include <SDL.h>

class MagicManager : public Manager<MagicManager>
{
	friend class Manager<MagicManager>;
public:
	typedef std::vector<Magic*> MagicList;

	void on_enter(int* magic_list);

	void on_input(const SDL_Event& event);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	Magic* get_current_magic()
	{
		if (magic_number != 0)
			current_magic = magic_list[magic_number - 1];
		else
			current_magic = nullptr;
		return current_magic;
	}

	void cancel_choose();

	void set_current_mp(double mp);

	void get_player_position(Vector2 pos);

	void get_last_magic();

private:
	double current_mp;
	float totalRotation = 0;

	int magic_number = 0;
	int last_magic_number = 0;
	int magic_amount = 0;

	MagicList magic_list;
	Magic* current_magic = nullptr;

	Vector2 player_position;

	void set_position_idle();

	void set_position_choose();

	void handleMouseWheelAdvanced(SDL_MouseWheelEvent wheel);

protected:
	MagicManager();
	~MagicManager();
};