#include "fireball_bullet.h"

FireballBullet::FireballBullet()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_bullet = tex_pool.find(ResID::Tex_BulletFireball)->second;

	anim_bullet_fly.set_loop(true);
	anim_bullet_fly.set_interval(0.1);
	anim_bullet_fly.set_frame_data(tex_bullet, 2, 2, { 0,1 });

	anim_bullet_attack.set_loop(false);
	anim_bullet_attack.set_interval(0.2);
	anim_bullet_attack.set_frame_data(tex_bullet, 2, 2, { 2,3 });

	size.x = 32, size.y = 32;

	anim_current = &anim_bullet_fly;

	Vector2 size_box;
	size_box.x = 16;
	size_box.y = 16;
	
	collide_box = CollisionManager::instance()->create_collide_box(size_box, position);
	collide_box->set_layer_src(tools::to_ten("1000"));
	collide_box->set_layer_dst(tools::to_ten("100"));
	collide_box->set_enable(false);
	collide_box->set_self(true);
	collide_box->set_on_collide([&]() {
		is_collide = true;
		collide_box->set_enable(false);

		damage_box->set_damage(damage);
		damage_box->set_enable(true);

		anim_current = &anim_bullet_attack;
		anim_bullet_attack.set_on_finished([&]() {
			make_invalid();
			});
		});

	damage_box = CollisionManager::instance()->create_collide_box(14, position);
	damage_box->set_layer_src(tools::to_ten("1000"));
	damage_box->set_layer_dst(tools::to_ten("100"));
	damage_box->set_enable(false);
	damage_box->set_on_collide([&]() {
		damage_box->make_invalid();
		});
}

FireballBullet::~FireballBullet()
{
}

void FireballBullet::on_update(double delta)
{
	
	switch (type)
	{
	case Line:
		if (!is_collide)
		{
			collide_box->set_enable(true);
			find_ways(delta);
			if ((position - start_pos).length() >= distance)
			{
				is_collide = true;
				collide_box->set_enable(false);
				anim_current = &anim_bullet_attack;
				anim_bullet_attack.set_on_finished([&]() {
					make_invalid();
					});
			}
		}
		break;
	case Assign:
		position = target->get_position();
		if (!is_collide)
		{
			is_collide = true;
			anim_current = &anim_bullet_attack;
			anim_bullet_attack.reset();
			anim_bullet_attack.set_on_finished([&]() {
				deliver_buff(target);
				make_invalid();
				});
		}
		break;
	default:
		break;
	}
	Bullet::on_update(delta);
}

void FireballBullet::on_render(SDL_Renderer* renderer)
{
	Bullet::on_render(renderer);
}

void FireballBullet::find_ways(double delta)
{
	position += velocity.normalize() * speed * delta;
}