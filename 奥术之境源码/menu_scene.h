#pragma once
#include "scene.h"
#include "scene_manager.h"

class MenuScene:public Scene
{
	enum GameMode
	{
		Start,
		Solo,
		Multi
	};
public:
	MenuScene();
	~MenuScene();
	void on_enter();

	void on_input(const SDL_Event& event);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);
private:
	GameMode gamemod=Start;

	bool is_enter = false;
	bool is_show_button = false;

	SDL_Point point_first;
	SDL_Point point_second;
	SDL_Point point_third;

	Animation anim_main_menu_wait;
	Animation anim_main_menu_choose;
	Animation anim_arrtibute_icon;

	Animation anim_button_solo;
	Animation anim_button_multi;
	Animation anim_button_quit;
	Animation anim_button_drill;
	Animation anim_button_train;
	Animation anim_button_multidrill;
	Animation anim_button_fight;
	Animation anim_button_back;

	Animation anim_button_solo_idle;
	Animation anim_button_multi_idle;
	Animation anim_button_quit_idle;
	Animation anim_button_drill_idle;
	Animation anim_button_train_idle;
	Animation anim_button_multidrill_idle;
	Animation anim_button_fight_idle;
	Animation anim_button_back_idle;

	Animation* anim_button_first = nullptr;
	Animation* anim_button_second = nullptr;
	Animation* anim_button_third = nullptr;

	void switch_game_mod(int code);
};