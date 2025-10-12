#pragma once
#include "buff.h"
#include "burn_buff.h"
#include "recover_buff.h"
#include "speed_up_buff.h"

#include<vector>
#include <SDL.h>

class BuffManager
{
public:
	typedef std::vector<Buff*> BuffList;

	BuffManager();
	~BuffManager();

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void set_buff_list(BuffList list);

	void set_buff(BuffName name);

	void deliver_buff(const BuffList& list);

	void set_position(Vector2 pos);

	BuffList get_buff_list()
	{
		return buff_list;
	}

private:
	BuffList buff_list;

	Vector2 position;

	void remove_invalid_buff();
};