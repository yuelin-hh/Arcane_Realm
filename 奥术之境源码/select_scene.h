#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "select.h"

class SelectScene:public Scene
{
public:
	SelectScene();
	~SelectScene();
	void on_enter();

	void on_input(const SDL_Event& event);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

private:
	Animation anim_background;
	Animation anim_start;
	Animation anim_handbook;

	Select select;

	int magic_list[10] = { 0 };
	int role = 0;
	void on_switch();
};