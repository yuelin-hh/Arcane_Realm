#include "lava_vortex_bullet.h"

LavaVortexBullet::LavaVortexBullet()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_bullet = tex_pool.find(ResID::Tex_BulletExplod)->second;
	SDL_Texture* tex_lava = tex_pool.find(ResID::Tex_BulletLava)->second;

	anim_bullet_fly.set_loop(false);
	anim_bullet_fly.set_interval(0.1);
	anim_bullet_fly.set_frame_data(tex_bullet, 3, 3, { 0,1,2,3,4,5 });

	anim_smoke.set_loop(false);
	anim_smoke.set_interval(0.1);
	anim_smoke.set_frame_data(tex_bullet, 3, 3, { 6,7,8 });

	anim_bullet_attack.set_loop(false);
	anim_bullet_attack.set_interval(2);
	anim_bullet_attack.set_frame_data(tex_lava, 1, 1, { 0 });

	anim_current = &anim_bullet_fly;

	anim_bullet_fly.set_on_finished([&]() {
		collide_box->resize(distance);
		lava_box->resize(distance);
		collide_box->set_enable(true);
		is_collide = true;
		anim_current = &anim_smoke;
		anim_bullet_attack.set_interval(duration);
		});

	anim_smoke.set_on_finished([&]() {
		is_smoking = false;
		});

	anim_bullet_attack.set_on_finished([&]() {
		lava_box->set_damage(damage * time);
		lava_box->set_enable(true);
		lava_box->set_on_collide([&]() {
			lava_box->make_invalid();
			is_finished = true;
			});
		});

	size.x = 320, size.y = 320;

	collide_box = CollisionManager::instance()->create_collide_box(1, position);
	collide_box->set_layer_src(tools::to_ten("1000"));
	collide_box->set_layer_dst(tools::to_ten("100"));
	collide_box->set_enable(false);
	collide_box->set_on_collide([&]() {
		collide_box->make_invalid();
		});

	lava_box = CollisionManager::instance()->create_collide_box(1, position);
	lava_box->set_layer_src(tools::to_ten("1000"));
	lava_box->set_layer_dst(tools::to_ten("100"));
	lava_box->set_enable(false);
	lava_box->set_on_collide([&]() {
		is_caused_damage = true;
		});

	attack_timer.set_one_shot(false);
	attack_timer.set_wait_time(0.3);
	attack_timer.set_on_timeout([&]() {
		lava_box->set_damage(damage * time);
		lava_box->set_enable(true);
		is_caused_damage = false;
		time = 0;
		});
}

LavaVortexBullet::~LavaVortexBullet()
{
}

void LavaVortexBullet::on_update(double delta)
{
	if (is_finished)
	{
		make_invalid();
		return;
	}

	if (is_collide)
	{
		check_collide(delta);
	}
	Bullet::on_update(delta);
}

void LavaVortexBullet::on_render(SDL_Renderer* renderer)
{
	if (!is_collide || is_smoking)
		Bullet::on_render(renderer);
		
}

void LavaVortexBullet::check_collide(double delta)
{
	anim_bullet_attack.on_update(delta);
	attack_timer.on_update(delta);
	time += delta;
	angle += delta*30;
	RetentionManager::instance()->set_retention(&anim_bullet_attack, position, size, angle);

	if (is_caused_damage)
	{
		lava_box->set_enable(false);
	}
}