#include "normal_attack_bullet.h"

NormalAttackBullet::NormalAttackBullet()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_bullet = tex_pool.find(ResID::Tex_BulletClaudeNormalAttack)->second;

	anim_bullet_fly.set_loop(true);
	anim_bullet_fly.set_interval(0.3);
	anim_bullet_fly.set_frame_data(tex_bullet, 1, 2, { 0 });

	anim_bullet_attack.set_loop(false);
	anim_bullet_attack.set_interval(0.3);
	anim_bullet_attack.set_frame_data(tex_bullet, 1, 2, { 1 });

	anim_current = &anim_bullet_fly;
	size.x = 32, size.y = 32;

	Vector2 size_box;
	size_box.x = 8;
	size_box.y = 8;

	collide_box = CollisionManager::instance()->create_collide_box(	size_box, position);
	collide_box->set_layer_src(tools::to_ten("1000"));
	collide_box->set_layer_dst(tools::to_ten("100"));
	collide_box->set_on_collide([&]() {
		is_collide = true;
		collide_box->set_enable(false);
		anim_current = &anim_bullet_attack;
		anim_bullet_attack.set_on_finished([&]() {
			make_invalid();
			});
		});
}

NormalAttackBullet::~NormalAttackBullet()
{
	
}

void NormalAttackBullet::on_update(double delta)
{
	switch (type)
	{
	case Trace:
		if (!is_collide)
		{
			find_ways_trace(delta);
		}
		break;
	case Line:
		if (!is_collide)
		{
			find_ways_line(delta);
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
	default:
		break;
	}
	Bullet::on_update(delta);
}

void NormalAttackBullet::on_render(SDL_Renderer* renderer)
{
	Bullet::on_render(renderer);
}

void NormalAttackBullet::find_ways_trace(double delta)
{
	if (target->can_remove())
	{
		is_collide = true;
		anim_current = &anim_bullet_attack;
		anim_bullet_attack.set_on_finished([&]() {
			make_invalid();
			});
		target = nullptr;
	}
	else
	{
		target_position = target->get_position();
	}
	velocity.x = (target_position.x - position.x);
	velocity.y = (target_position.y - position.y);

	position += velocity.normalize() * speed * delta;
}

void NormalAttackBullet::find_ways_line(double delta)
{
	position += velocity.normalize() * speed * delta;
}