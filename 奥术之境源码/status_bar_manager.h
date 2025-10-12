#pragma once

#include "vector2.h"
#include "animation.h"
#include "manager.h"
#include "resources_manager.h"

#include <SDL.h>
#include <SDL_ttf.h>

class StatusBarManager : public Manager<StatusBarManager>
{
	friend class Manager<StatusBarManager>;
protected:
	StatusBarManager();
	~StatusBarManager();

public:
	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void set_hp(double max_hp, double hp);

	void set_mp(double max_mp, double mp);

private:
	double max_hp;
	double hp;
	double max_mp;
	double mp;

	Vector2 position;

	Animation anim_status_bar;
	Animation anim_photo;

	TTF_Font* font;

	void number_on_renderer(SDL_Renderer* renderer);
};