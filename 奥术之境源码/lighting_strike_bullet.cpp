#include "lighting_strike_bullet.h"

LightingStrikeBullet::LightingStrikeBullet()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_lighting = tex_pool.find(ResID::Tex_BulletLighting)->second;
	SDL_Texture* tex_strike = tex_pool.find(ResID::Tex_BulletStrike)->second;

	anim_bullet_fly.set_loop(false);
	anim_bullet_fly.set_interval(0.1);
	anim_bullet_fly.set_frame_data(tex_lighting, 1, 1, { 0 });

	anim_bullet_fly.set_on_finished([&]() {
		is_collide = true;
		collide_box->resize(distance);
		collide_box->set_enable(true);
		anim_current = &anim_bullet_attack;
	});

	anim_bullet_attack.set_loop(false);
	anim_bullet_attack.set_interval(0.2);
	anim_bullet_attack.set_frame_data(tex_strike, 1, 1, { 0 });

	anim_bullet_attack.set_on_finished([&]() {
		make_invalid();
	});

	anim_current = &anim_bullet_fly;

	size.x = 128, size.y = 128;

	collide_box = CollisionManager::instance()->create_collide_box(1, position);
	collide_box->set_layer_src(tools::to_ten("1000"));
	collide_box->set_layer_dst(tools::to_ten("100"));
	collide_box->set_enable(false);
	collide_box->set_on_collide([&]() {
		collide_box->make_invalid();
		});
}

LightingStrikeBullet::~LightingStrikeBullet()
{
}

void LightingStrikeBullet::on_update(double delta)
{
	Bullet::on_update(delta);
}

void LightingStrikeBullet::on_render(SDL_Renderer* renderer)
{
	SDL_Point point;

	if (!is_collide)
	{
		point.x = (int)(position.x - 16);
		point.y = (int)(position.y - 64);
		for (int i = 1; i <= 15; i++)
		{
			anim_current->on_render(renderer, point);
			point.y -= 64;
		}
	}
	else
	{
		point.x = (int)(position.x - 16);
		point.y = (int)(position.y - 64);
		for (int i = 1; i <= 15; i++)
		{
			anim_bullet_fly.on_render(renderer, point);
			point.y -= 64;
		}
		point.x = (int)(position.x - size.x / 2);
		point.y = (int)(position.y - size.y / 2);
		anim_current->on_render(renderer, point);
	}
}