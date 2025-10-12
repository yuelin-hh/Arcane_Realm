#include "select.h"

Select::Select()
{
	load_config();

	anim_current_role = &anim_empty_role;
}

Select::~Select()
{
	role_list.clear();
	magic_list.clear();
	choose_magic_list.clear();
}

void Select::on_input(const SDL_Event& event)
{
	switch (current_select)
	{
	case Empty:
		on_input_empty(event);
		break;
	case SelectRole:
		on_input_select_role(event);
		break;
	case SelectMagic:
		on_input_select_magic(event);
		break;
	default:
		break;
	}

}

void Select::on_update(double delta)
{
	if (current_role == nullptr)
		anim_current_role = &anim_empty_role;
	else
		anim_current_role = &current_role->anim_role;

	int number = 0;
	for (Role& role : role_list)
	{
		if (role.is_on_show)
		{
			role.point.x = 597 + (int)(number % 2) * 341;
			role.point.y = 16 + (int)(number / 2) * 341;

			number++;
		}
	}
	number = 0;
	for (Magic& magic : magic_list)
	{
		if (magic.is_on_show)
		{
			magic.point.x = 538 + (int)(number % 7) * 106;
			magic.point.y = 16 + (int)(number / 7) * 160;

			number++;
		}
	}

	if (current_role != nullptr)
		while (choose_magic_list.size() > current_role->limit_quantity)
			choose_magic_list.pop_back();


}

void Select::on_render(SDL_Renderer* renderer)
{
	draw_current_role(renderer);

	if (current_role != nullptr)
		draw_current_magic(renderer);

	switch (current_select)
	{
	case Empty:

		break;
	case SelectRole:
		on_render_select_role(renderer);
		break;
	case SelectMagic:
		on_render_select_magic(renderer);
		break;
	default:
		break;
	}
}

void Select::load_config()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();
	SDL_Texture* tex_empty_role = tex_pool.find(ResID::Tex_PlayerSelectUI)->second;
	SDL_Texture* tex_empty_magic = tex_pool.find(ResID::Tex_MagicSelectUI)->second;

	anim_empty_role.set_loop(true);
	anim_empty_role.set_interval(1);
	anim_empty_role.set_frame_data(tex_empty_role, 1, 1, { 0 });

	anim_empty_magic.set_loop(true);
	anim_empty_magic.set_interval(1);
	anim_empty_magic.set_scaling(0.5);
	anim_empty_magic.set_frame_data(tex_empty_magic, 1, 1, { 0 });


	SDL_Texture* tex_claude = tex_pool.find(ResID::Tex_ClaudePhoto)->second;

	Claude.code = 1;
	Claude.limit_quantity = 6;
	Claude.anim_role.set_loop(true);
	Claude.anim_role.set_interval(1);
	Claude.anim_role.set_scaling(0.4);
	Claude.anim_role.set_frame_data(tex_claude, 1, 1, { 0 });
	role_list.push_back(Claude);

	SDL_Texture* tex_burning_spell = tex_pool.find(ResID::Tex_MagicBurningSpell)->second;
	SDL_Texture* tex_wind_spell = tex_pool.find(ResID::Tex_MagicWindSpell)->second;
	SDL_Texture* tex_fireball = tex_pool.find(ResID::Tex_MagicFireball)->second;
	SDL_Texture* tex_minor_hesling_spell = tex_pool.find(ResID::Tex_MagicMinorHeslingSpell)->second;
	SDL_Texture* tex_lighting_strike = tex_pool.find(ResID::Tex_MagicLightingStrike)->second;
	SDL_Texture* tex_lava_vortex = tex_pool.find(ResID::Tex_MagicLavaVortex)->second;
	SDL_Texture* tex_zeus_fury = tex_pool.find(ResID::Tex_MagicZeusFury)->second;

	BurningSpell.code = 1;
	BurningSpell.anim_magic.set_loop(true);
	BurningSpell.anim_magic.set_interval(1);
	BurningSpell.anim_magic.set_scaling(0.5);
	BurningSpell.anim_magic.set_frame_data(tex_burning_spell, 2, 1, { 0 });
	magic_list.push_back(BurningSpell);

	WindSpell.code = 2;
	WindSpell.anim_magic.set_loop(true);
	WindSpell.anim_magic.set_interval(1);
	WindSpell.anim_magic.set_scaling(0.5);
	WindSpell.anim_magic.set_frame_data(tex_wind_spell, 2, 1, { 0 });
	magic_list.push_back(WindSpell);

	Fireball.code = 3;
	Fireball.anim_magic.set_loop(true);
	Fireball.anim_magic.set_interval(1);
	Fireball.anim_magic.set_scaling(0.5);
	Fireball.anim_magic.set_frame_data(tex_fireball, 2, 1, { 0 });
	magic_list.push_back(Fireball);

	MinorHealingSpell.code = 4;
	MinorHealingSpell.anim_magic.set_loop(true);
	MinorHealingSpell.anim_magic.set_interval(1);
	MinorHealingSpell.anim_magic.set_scaling(0.5);
	MinorHealingSpell.anim_magic.set_frame_data(tex_minor_hesling_spell, 2, 1, { 0 });
	magic_list.push_back(MinorHealingSpell);

	LightingStrike.code = 5;
	LightingStrike.anim_magic.set_loop(true);
	LightingStrike.anim_magic.set_interval(1);
	LightingStrike.anim_magic.set_scaling(0.5);
	LightingStrike.anim_magic.set_frame_data(tex_lighting_strike, 2, 1, { 0 });
	magic_list.push_back(LightingStrike);

	LavaVortex.code = 6;
	LavaVortex.anim_magic.set_loop(true);
	LavaVortex.anim_magic.set_interval(1);
	LavaVortex.anim_magic.set_scaling(0.5);
	LavaVortex.anim_magic.set_frame_data(tex_lava_vortex, 2, 1, { 0 });
	magic_list.push_back(LavaVortex);

	ZeusFury.code = 7;
	ZeusFury.anim_magic.set_loop(true);
	ZeusFury.anim_magic.set_interval(1);
	ZeusFury.anim_magic.set_scaling(0.5);
	ZeusFury.anim_magic.set_frame_data(tex_zeus_fury, 2, 1, { 0 });
	magic_list.push_back(ZeusFury);
}

void Select::draw_current_role(SDL_Renderer* renderer)
{
	SDL_Point point;
	point.x = 128;
	point.y = 30;
	anim_current_role->on_render_lock(renderer, point);
}

void Select::draw_current_magic(SDL_Renderer* renderer)
{
	int number = 0;
	for (Magic* magic : choose_magic_list)
	{
		SDL_Point point;
		point.x = 48 + (number % 4) * 112;
		point.y = 360 + (int)(number / 4) * 160;
		number++;
		Magic& M = *magic;
		M.anim_magic.on_render_lock(renderer, point);
	}
	for (int i = choose_magic_list.size(); i < current_role->limit_quantity; i++)
	{
		SDL_Point point;
		point.x = 48 + (number % 4) * 112;
		point.y = 360 + (int)(number / 4) * 160;
		number++;
		anim_empty_magic.on_render_lock(renderer, point);
	}
}

void Select::on_input_empty(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			if (event.motion.x >= 128 && event.motion.x <= 384
				&& event.motion.y >= 30 && event.motion.y <= 286)
			{
				current_select = SelectRole;
			}
		case SDL_BUTTON_MIDDLE:
			break;
		default:
			break;
		}
	default:
		break;
	}
}

void Select::on_input_select_role(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			if (event.motion.x >= 128 && event.motion.x <= 348
				&& event.motion.y >= 30 && event.motion.y <= 286
				&& current_role != nullptr)
			{
				current_role->is_on_show = true;
				current_role = nullptr;

				for (int i = 0; i < choose_magic_list.size(); i++)
				{
					choose_magic_list.at(i)->is_on_show = true;
				}
				choose_magic_list.clear();
			}
			else if (event.motion.x >= 16 && event.motion.x <= 496
				&& event.motion.y >= 300 && event.motion.y <= 704
				&& current_role != nullptr)
			{
				current_select = SelectMagic;
			}
			else
			{
				for (Role& role : role_list)
				{
					if (event.motion.x >= role.point.x && event.motion.x <= role.point.x + 256
						&& event.motion.y >= role.point.y && event.motion.y <= role.point.y + 256
						&& role.is_on_show)
					{
						current_role = &role;
						role.is_on_show = false;
						break;
					}
				}
			}
		default:
			break;
		}
	default:
		break;
	}
}

void Select::on_input_select_magic(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			if (event.motion.x >= 128 && event.motion.x <= 348
				&& event.motion.y >= 30 && event.motion.y <= 286)
			{
				current_select = SelectRole;
			}
			else
			{
				for (Magic& magic : magic_list)
				{
					if (event.motion.x >= magic.point.x && event.motion.x <= magic.point.x + 80
						&& event.motion.y >= magic.point.y && event.motion.y <= magic.point.y + 128
						&& magic.is_on_show && choose_magic_list.size() < current_role->limit_quantity)
					{
						choose_magic_list.push_back(&magic);
						magic.is_on_show = false;
						break;
					}
				}

				if (event.motion.x >= 48 && event.motion.x <= 464
					&& event.motion.y >= 360 && event.motion.y <= 648)
				{
					if ((event.motion.x - 48) % 112 <= 80 && (event.motion.y - 360) % 160 <= 128)
					{
						int index;
						index = (int)((event.motion.x - 48) / 112) + (int)((event.motion.y - 360) / 160) * 4;

						if (index < choose_magic_list.size())
							give_back(index);
					}
				}
			}
		default:
			break;
		}
	default:
		break;
	}
}

void Select::on_render_select_role(SDL_Renderer* renderer)
{
	for (Role& role : role_list)
	{
		if (!role.is_on_show)
			continue;

		role.anim_role.on_render_lock(renderer, role.point);
	}

	SDL_Rect rect;

	rect.x = 128;
	rect.y = 30;
	rect.h = 256;
	rect.w = 256;
	SDL_SetRenderDrawColor(renderer, 255, 242, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);

}

void Select::on_render_select_magic(SDL_Renderer* renderer)
{
	SDL_Rect rect;

	rect.x = 16;
	rect.y = 326;
	rect.h = 378;
	rect.w = 480;
	SDL_SetRenderDrawColor(renderer, 255, 242, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);

	for (Magic& magic : magic_list)
	{
		if (!magic.is_on_show)
			continue;

		magic.anim_magic.on_render_lock(renderer, magic.point);
	}
}

void Select::give_back(int index)
{
	choose_magic_list.at(index)->is_on_show = true;
	choose_magic_list.erase(choose_magic_list.begin() + index);
}