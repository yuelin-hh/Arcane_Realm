#include "select_scene.h"

SelectScene::SelectScene()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_back_ground = tex_pool.find(ResID::Tex_SelectScene)->second;
	SDL_Texture* tex_button = tex_pool.find(ResID::Tex_SelectButtonUI)->second;

	anim_background.set_loop(true);
	anim_background.set_interval(1);
	anim_background.set_frame_data(tex_back_ground, 1, 1, { 0 });

	anim_start.set_loop(true);
	anim_start.set_interval(1);
	anim_start.set_frame_data(tex_button, 1, 2, { 0 });

	anim_handbook.set_loop(true);
	anim_handbook.set_interval(1);
	anim_handbook.set_frame_data(tex_button, 1, 2, { 1 });
}

SelectScene::~SelectScene()
{
}

void SelectScene::on_enter()
{

}

void SelectScene::on_input(const SDL_Event& event)
{
	select.on_input(event);
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			if (event.motion.x >= 85 && event.motion.x <= 213
				&& event.motion.y >= 670 && event.motion.y <= 702)
			{

			}
			else if (event.motion.x >= 299 && event.motion.x <= 427
				&& event.motion.y >= 670 && event.motion.y <= 720)
			{
				on_switch();
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

void SelectScene::on_update(double delta)
{
	select.on_update(delta);
}

void SelectScene::on_render(SDL_Renderer* renderer)
{
	SDL_Point point;
	point.x = 0;
	point.y = 0;
	anim_background.on_render_lock(renderer, point);

	point.x = 85;
	point.y = 670;
	anim_handbook.on_render_lock(renderer, point);
	point.x = 299;
	anim_start.on_render_lock(renderer, point);

	select.on_render(renderer);
}

void SelectScene::on_switch()
{
	role = select.get_role_code();

	if (!role)
		return;

	int magic_amount = select.get_magic_amount();
	for (int i = 0; i < magic_amount; i++)
	{
		magic_list[i] = select.get_magic_code(i);
	}

	SceneManager::instance()->set_role(role);
	SceneManager::instance()->set_magic(magic_list);

	SceneManager::instance()->switch_to(SceneManager::instance()->SceneType::Game);
}