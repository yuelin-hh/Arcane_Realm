#pragma once

#include "animation.h"
#include "resources_manager.h"

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <vector>

enum CurrentSelect
{
	Empty,
	SelectRole,
	SelectMagic
};

class Select
{
public:
	struct Role
	{
		Animation anim_role;
		int code = 0;
		int limit_quantity = 6;
		bool is_on_show = true;
		SDL_Point point;
	};

	struct Magic
	{
		Animation anim_magic;
		int code = 0;
		bool is_on_show = true;
		SDL_Point point;
	};

	using RoleList = std::vector<Role>;
	using MagicList = std::vector<Magic>;
	using ChooseList = std::vector<Magic*>;

	Select();
	~Select();

	void on_input(const SDL_Event& event);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);
	
	int get_role_code()
	{
		if (current_role == nullptr)
			return 0;

		return current_role->code;
	}

	int get_magic_amount()
	{
		return choose_magic_list.size();
	}

	int get_magic_code(int index)
	{
		return choose_magic_list.at(index)->code;
	}

private:
	CurrentSelect current_select = Empty;
	Role* current_role = nullptr;

	Animation anim_empty_role;
	Animation anim_empty_magic;

	Animation* anim_current_role;
	Animation* anim_current_magic;

	RoleList role_list;
	MagicList magic_list;
	ChooseList choose_magic_list;

	Role Claude;

	Magic BurningSpell;
	Magic WindSpell;
	Magic Fireball;
	Magic MinorHealingSpell;
	Magic LightingStrike;
	Magic LavaVortex;
	Magic ZeusFury;


private:
	void load_config();

	void draw_current_role(SDL_Renderer* renderer);

	void draw_current_magic(SDL_Renderer* renderer);

	void on_input_empty(const SDL_Event& event);

	void on_input_select_role(const SDL_Event& event);

	void on_input_select_magic(const SDL_Event& event);

	void on_render_select_role(SDL_Renderer* renderer);

	void on_render_select_magic(SDL_Renderer* renderer);

	void give_back(int index);
};