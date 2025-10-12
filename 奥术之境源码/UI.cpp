#include "UI.h"

UI::UI()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_lock_ui = tex_pool.find(ResID::Tex_LockUI)->second;

	anim_ui_lock.set_loop(true);
	anim_ui_lock.set_interval(1);
	anim_ui_lock.set_frame_data(tex_lock_ui, 3, 1, { 1 });

	anim_ui_lock_attack.set_loop(false);
	anim_ui_lock_attack.set_interval(0.3);
	anim_ui_lock_attack.set_frame_data(tex_lock_ui, 3, 1, { 2 });

	anim_ui_lock_current = &anim_ui_lock;

	anim_ui_lock_attack.set_on_finished([&]() {
		anim_ui_lock_current = &anim_ui_lock;
		});
}

UI::~UI()
{
}

void UI::on_update(double delta)
{
	anim_ui_lock_current->on_update(delta);
}

void UI::on_render(SDL_Renderer* renderer)
{
	if (is_show_lock_ui)
	{
		SDL_Point point;
		if (is_lock_ui_on_target)
		{
			point.x = position_target.x - 16;
			point.y = position_target.y - 16 + size_target.y / 2.3;
			anim_ui_lock_current->on_render(renderer, point);
		}
		else if (is_lock_ui_fllow)
		{
			point.x = (int)(mouse_position.x - 16);
			point.y = (int)(mouse_position.y - 16);
			anim_ui_lock_current->on_render_lock(renderer, point);
		}

	}

}

void UI::set_lock_target(std::shared_ptr<Object> enemy)
{
	if (enemy != nullptr)
	{
		position_target = enemy->get_position();
		size_target = enemy->get_size();
		is_lock_ui_on_target = true;
	}
	else is_lock_ui_on_target = false;
}

void UI::on_attack_lock()
{
	anim_ui_lock_current = &anim_ui_lock_attack;
	anim_ui_lock_current->reset();
}

void UI::set_follow_ui_valid(bool flag)
{
	if (flag)
	{
		anim_ui_lock_current = &anim_ui_lock;
	}
	else
	{
		anim_ui_lock_current = &anim_ui_lock_attack;
	}
}