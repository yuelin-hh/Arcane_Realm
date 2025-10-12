#include "menu_scene.h"

#ifdef _DEBUG
#define IS_DEBUG true
#else
#define IS_DEBUG false
#endif // _DEBUG


MenuScene::MenuScene()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_menu_wait = tex_pool.find(ResID::Tex_MainMenuWait)->second;
	SDL_Texture* tex_menu_choose = tex_pool.find(ResID::Tex_MainMenuChoose)->second;
	SDL_Texture* tex_button = tex_pool.find(ResID::Tex_ButtonUI)->second;
	SDL_Texture* tex_icon = tex_pool.find(ResID::Tex_AttributeIcon)->second;

	anim_main_menu_wait.set_loop(true);
	anim_main_menu_wait.set_interval(0.15);
	anim_main_menu_wait.set_frame_data(tex_menu_wait, 2, 2, { 0,1,2,3 });

	anim_main_menu_choose.set_loop(false);
	anim_main_menu_choose.set_interval(0.1);
	anim_main_menu_choose.set_frame_data(tex_menu_choose, 2, 2, { 0,1,2,3 });

	anim_button_solo.set_loop(true);
	anim_button_solo.set_interval(0.4);
	anim_button_solo.set_frame_data(tex_button, 2, 8, { 0 });
	anim_button_solo_idle.set_loop(true);
	anim_button_solo_idle.set_interval(0.1);
	anim_button_solo_idle.set_frame_data(tex_button, 2, 8, { 1 });

	anim_button_multi.set_loop(true);
	anim_button_multi.set_interval(0.1);
	anim_button_multi.set_frame_data(tex_button, 2, 8, { 6 });
	anim_button_multi_idle.set_loop(true);
	anim_button_multi_idle.set_interval(0.1);
	anim_button_multi_idle.set_frame_data(tex_button, 2, 8, { 7 });

	anim_button_quit.set_loop(true);
	anim_button_quit.set_interval(0.1);
	anim_button_quit.set_frame_data(tex_button, 2, 8, { 14 });
	anim_button_quit_idle.set_loop(true);
	anim_button_quit_idle.set_interval(0.1);
	anim_button_quit_idle.set_frame_data(tex_button, 2, 8, { 15 });

	anim_button_drill.set_loop(true);
	anim_button_drill.set_interval(0.1);
	anim_button_drill.set_frame_data(tex_button, 2, 8, { 4 });
	anim_button_drill_idle.set_loop(true);
	anim_button_drill_idle.set_interval(0.1);
	anim_button_drill_idle.set_frame_data(tex_button, 2, 8, { 5 });

	anim_button_train.set_loop(true);
	anim_button_train.set_interval(0.1);
	anim_button_train.set_frame_data(tex_button, 2, 8, { 2 });
	anim_button_train_idle.set_loop(true);
	anim_button_train_idle.set_interval(0.1);
	anim_button_train_idle.set_frame_data(tex_button, 2, 8, { 3 });

	anim_button_multidrill.set_loop(true);
	anim_button_multidrill.set_interval(0.1);
	anim_button_multidrill.set_frame_data(tex_button, 2, 8, { 8 });
	anim_button_multidrill_idle.set_loop(true);
	anim_button_multidrill_idle.set_interval(0.1);
	anim_button_multidrill_idle.set_frame_data(tex_button, 2, 8, { 9 });

	anim_button_fight.set_loop(true);
	anim_button_fight.set_interval(0.1);
	anim_button_fight.set_frame_data(tex_button, 2, 8, { 10 });
	anim_button_fight_idle.set_loop(true);
	anim_button_fight_idle.set_interval(0.1);
	anim_button_fight_idle.set_frame_data(tex_button, 2, 8, { 11 });

	anim_button_back.set_loop(true);
	anim_button_back.set_interval(0.1);
	anim_button_back.set_frame_data(tex_button, 2, 8, { 12 });
	anim_button_back_idle.set_loop(true);
	anim_button_back_idle.set_interval(0.1);
	anim_button_back_idle.set_frame_data(tex_button, 2, 8, { 13 });

	anim_arrtibute_icon.set_loop(true);
	anim_arrtibute_icon.set_interval(0.5);
	anim_arrtibute_icon.set_scaling(4);
	anim_arrtibute_icon.set_frame_data(tex_icon, 4, 4, { 0,1,2,3,4,5,6,7,14,9,10,11,12,13 });

	anim_button_first = &anim_button_solo;
	anim_button_second = &anim_button_multi;
	anim_button_third = &anim_button_quit;

	point_first.x = 100, point_first.y = 420;
	point_second.x = 100, point_second.y = 520;
	point_third.x = 100, point_third.y = 620;


}

MenuScene::~MenuScene()
{
}

void MenuScene::on_enter()
{
	if (IS_DEBUG)
	{
		SceneManager::instance()->gamemode = 1;
		SceneManager::instance()->switch_to(SceneManager::instance()->SceneType::Select);
	}
}

void MenuScene::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (!is_enter)
		{
			is_enter = true;
			anim_main_menu_choose.reset();
			anim_main_menu_choose.set_on_finished([&]() {
				is_show_button = true;
				});
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			if (event.motion.x >= 100 && event.motion.x <= 356
				&& event.motion.y >= 420 && event.motion.y <= 484)
			{
				switch_game_mod(1);
			}
			else if (event.motion.x >= 100 && event.motion.x <= 356
				&& event.motion.y >= 520 && event.motion.y <= 584)
			{
				switch_game_mod(2);
			}
			else if (event.motion.x >= 100 && event.motion.x <= 356
				&& event.motion.y >= 620 && event.motion.y <= 684)
			{
				switch_game_mod(3);
			}
			break;
		case SDL_BUTTON_MIDDLE:
			break;
		default:
			break;
		}

	default:
		break;
	}
}

void MenuScene::on_update(double delta)
{
	anim_main_menu_wait.on_update(delta);
	anim_main_menu_choose.on_update(delta);
	anim_arrtibute_icon.on_update(delta);
}

void MenuScene::on_render(SDL_Renderer* renderer)
{
	SDL_Point point;
	point.x = 0;
	point.y = 0;
	if (is_enter)
	{
		anim_main_menu_choose.on_render_lock(renderer, point);
		if (is_show_button)
		{
			point.x = 850;
			point.y = 400;
			anim_arrtibute_icon.on_render_lock(renderer, point);

			anim_button_first->on_render_lock(renderer, point_first);
			anim_button_second->on_render_lock(renderer, point_second);
			anim_button_third->on_render_lock(renderer, point_third);
		}
	}
	else
	{
		anim_main_menu_wait.on_render_lock(renderer, point);
	}
}

void MenuScene::switch_game_mod(int code)
{
	switch (code)
	{
	case 1:
		switch (gamemod)
		{
		case MenuScene::Start:
			gamemod = Solo;
			break;
		case MenuScene::Solo:
			SceneManager::instance()->gamemode = 0;
			SceneManager::instance()->switch_to(SceneManager::instance()->SceneType::Select);
			break;
		case MenuScene::Multi:
			break;
		default:
			break;
		}
		break;
	case 2:
		switch (gamemod)
		{
		case MenuScene::Start:
			gamemod = Multi;
			break;
		case MenuScene::Solo:
			SceneManager::instance()->gamemode = 1;
			SceneManager::instance()->switch_to(SceneManager::instance()->SceneType::Select);
			break;
		case MenuScene::Multi:
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (gamemod)
		{
		case MenuScene::Start:
			ConfigManager::instance()->running = false;
			break;
		case MenuScene::Solo:
			gamemod = Start;
			break;
		case MenuScene::Multi:
			gamemod = Start;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	switch (gamemod)
	{
	case MenuScene::Start:
		anim_button_first = &anim_button_solo;
		anim_button_second = &anim_button_multi;
		anim_button_third = &anim_button_quit;
		break;
	case MenuScene::Solo:
		anim_button_first = &anim_button_drill;
		anim_button_second = &anim_button_train;
		anim_button_third = &anim_button_back;
		break;
	case MenuScene::Multi:
		anim_button_first = &anim_button_multidrill;
		anim_button_second = &anim_button_fight;
		anim_button_third = &anim_button_back;
		break;
	default:
		break;
	}
}