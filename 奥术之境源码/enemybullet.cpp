#include "enemybullet.h"

EnemyBullet::EnemyBullet()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_enemy_bullet = tex_pool.find(ResID::Tex_EnemyBullet)->second;

	anim_bullet_fly.set_loop(true);
	anim_bullet_fly.set_interval(0.5);
	anim_bullet_fly.set_frame_data(tex_enemy_bullet, 1, 1, { 0 });

	size.x = 16, size.y = 16;

	anim_current = &anim_bullet_fly;

	collide_box = CollisionManager::instance()->create_collide_box(4, position);
	collide_box->set_layer_src(tools::to_ten("1000"));
	collide_box->set_layer_dst(tools::to_ten("1"));
	collide_box->set_on_collide([&]() {
		is_collide = true;

		collide_box->set_enable(false);
		});
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::on_update(double delta)
{
	if (!is_collide)
	{
		find_ways(delta);
		if ((position - start_pos).length() >= distance)
		{
			is_collide = true;
			collide_box->set_enable(false);
		}
	}
	else
	{
		make_invalid();
	}
	Bullet::on_update(delta);
}

void EnemyBullet::on_render(SDL_Renderer* renderer)
{
	Bullet::on_render(renderer);
}

void EnemyBullet::find_ways(double delta)
{
	position += velocity.normalize() * speed * delta;
}