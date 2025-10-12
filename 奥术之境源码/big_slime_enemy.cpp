#include "big_slime_enemy.h"

BigSlimeEnemy::BigSlimeEnemy()
{
	static const ResourcesManager::TexturePool& texture_pool
		= ResourcesManager::instance()->get_texture_pool();
	static SDL_Texture* tex_enemy = texture_pool.find(ResID::Tex_Slime)->second;
	static SDL_Texture* tex_enemy_sketch = texture_pool.find(ResID::Tex_SlimeSketch)->second;
	static ConfigManager::EnemyTemplate& enemy_template = ConfigManager::instance()->big_slime_template;

	anim_spawn.set_scaling(2);

	anim_idle_left.set_loop(true);
	anim_idle_left.set_interval(0.3);
	anim_idle_left.set_scaling(2);
	anim_idle_left.set_frame_data(tex_enemy, 6, 2, { 0,1 });
	anim_idle_right.set_loop(true);
	anim_idle_right.set_interval(0.3);
	anim_idle_right.set_scaling(2);
	anim_idle_right.set_frame_data(tex_enemy, 6, 2, { 6,7 });

	anim_move_left.set_loop(true);
	anim_move_left.set_interval(0.1);
	anim_move_left.set_scaling(2);
	anim_move_left.set_frame_data(tex_enemy, 6, 2, { 0,1 ,2,3,4,5 });
	anim_move_right.set_loop(true);
	anim_move_right.set_interval(0.1);
	anim_move_right.set_scaling(2);
	anim_move_right.set_frame_data(tex_enemy, 6, 2, { 6,7 ,8,9,10,11 });

	anim_ready_left.set_loop(false);
	anim_ready_left.set_interval(0.2);
	anim_ready_left.set_scaling(2);
	anim_ready_left.set_frame_data(tex_enemy, 6, 2, { 0,1 });
	anim_ready_right.set_loop(false);
	anim_ready_right.set_interval(0.2);
	anim_ready_right.set_scaling(2);
	anim_ready_right.set_frame_data(tex_enemy, 6, 2, { 6,7 });

	anim_attack_left.set_loop(false);
	anim_attack_left.set_interval(0.1);
	anim_attack_left.set_scaling(2);
	anim_attack_left.set_frame_data(tex_enemy, 6, 2, { 0,1 ,2,3,4,5 });
	anim_attack_right.set_loop(false);
	anim_attack_right.set_interval(0.1);
	anim_attack_right.set_scaling(2);
	anim_attack_right.set_frame_data(tex_enemy, 6, 2, { 6,7 ,8,9,10,11 });

	anim_idle_left_sketch.set_loop(true);
	anim_idle_left_sketch.set_interval(0.3);
	anim_idle_left_sketch.set_scaling(2);
	anim_idle_left_sketch.set_frame_data(tex_enemy_sketch, 6, 2, { 0,1 });
	anim_idle_right_sketch.set_loop(true);
	anim_idle_right_sketch.set_interval(0.3);
	anim_idle_right_sketch.set_scaling(2);
	anim_idle_right_sketch.set_frame_data(tex_enemy_sketch, 6, 2, { 6,7 });

	anim_move_left_sketch.set_loop(true);
	anim_move_left_sketch.set_interval(0.1);
	anim_move_left_sketch.set_scaling(2);
	anim_move_left_sketch.set_frame_data(tex_enemy_sketch, 6, 2, { 0,1 ,2,3,4,5 });
	anim_move_right_sketch.set_loop(true);
	anim_move_right_sketch.set_interval(0.1);
	anim_move_right_sketch.set_scaling(2);
	anim_move_right_sketch.set_frame_data(tex_enemy_sketch, 6, 2, { 6,7 ,8,9,10,11 });

	anim_ready_left_sketch.set_loop(false);
	anim_ready_left_sketch.set_interval(0.2);
	anim_ready_left_sketch.set_scaling(2);
	anim_ready_left_sketch.set_frame_data(tex_enemy_sketch, 6, 2, { 0,1 });
	anim_ready_right_sketch.set_loop(false);
	anim_ready_right_sketch.set_interval(0.2);
	anim_ready_right_sketch.set_scaling(2);
	anim_ready_right_sketch.set_frame_data(tex_enemy_sketch, 6, 2, { 6,7 });

	anim_attack_left_sketch.set_loop(false);
	anim_attack_left_sketch.set_interval(0.1);
	anim_attack_left_sketch.set_scaling(2);
	anim_attack_left_sketch.set_frame_data(tex_enemy_sketch, 6, 2, { 0,1 ,2,3,4,5 });
	anim_attack_right_sketch.set_loop(false);
	anim_attack_right_sketch.set_interval(0.1);
	anim_attack_right_sketch.set_scaling(2);
	anim_attack_right_sketch.set_frame_data(tex_enemy_sketch, 6, 2, { 6,7 ,8,9,10,11 });

	hp_max = enemy_template.hp;
	speed = enemy_template.speed;
	damage = enemy_template.damage;
	attack_radius = enemy_template.attack_radius;
	view_radius = enemy_template.view_radius;
	attack_interval = enemy_template.attack_interval;
	hp = hp_max;

	size.x = 96, size.y = 96;

	timer_attack_interval.set_one_shot(false);
	timer_attack_interval.set_wait_time(attack_interval);
	timer_attack_interval.set_on_timeout([&]() {
		can_attack = true;
		});

	int a = rand() % 2;
	anim_current = a == 0 ? &anim_idle_left : &anim_idle_right;
	anim_current_sketch = a == 0 ? &anim_idle_left_sketch : &anim_idle_right_sketch;

	Vector2 size_box;
	size_box.x = 64;
	size_box.y = 64;
	anim_current = &anim_idle_left;
	anim_current_sketch = &anim_idle_left_sketch;

	collide_box = CollisionManager::instance()->create_collide_box(size_box, position);
	collide_box->set_layer_src(tools::to_ten("100"));
	collide_box->set_layer_dst(tools::to_ten("10"));
	collide_box->set_enable(false);
	collide_box->set_on_collide([&](double damage, BuffManager::BuffList list) {
		deliver_buff(list);
		cause_damage(damage);
		});

	size_box.x = 48;
	size_box.y = 48;
	attack_box = CollisionManager::instance()->create_collide_box(size_box, position);
	attack_box->set_layer_src(tools::to_ten("1000"));
	attack_box->set_layer_dst(tools::to_ten("1"));
	attack_box->set_enable(false);
	attack_box->set_damage(damage);
	attack_box->set_on_collide([&]() {
		attack_box->set_enable(false);
		});
}

BigSlimeEnemy::~BigSlimeEnemy()
{
	attack_box->make_invalid();
}

void BigSlimeEnemy::attack(double delta)
{
	if (state == State::Nullptr)
	{

		have_caused_damage = false;
		state = State::Ready;
		velocity = player_position - position;

		if (velocity.x < 0)
		{
			anim_current = &anim_ready_right;
			anim_current_sketch = &anim_ready_right_sketch;
		}
		else if (velocity.x > 0)
		{
			anim_current = &anim_ready_left;
			anim_current_sketch = &anim_ready_left_sketch;
		}
		anim_current->reset();
		anim_current_sketch->reset();
		anim_current->set_on_finished([&]() {
			state = State::Switch;
			});
	}
	else if (state == State::Switch)
	{
		if (velocity.x < 0)
		{
			anim_current = &anim_attack_right;
			anim_current_sketch = &anim_attack_right_sketch;
		}
		else if (velocity.x > 0)
		{
			anim_current = &anim_attack_left;
			anim_current_sketch = &anim_attack_left_sketch;
		}
		anim_current->reset();
		anim_current_sketch->reset();
		anim_current->set_on_finished([&]() {
			finish_attack();
			});
		state = State::Attack;
		attack_box->set_enable(true);
	}
	else if (state == State::Attack)
	{
		position += velocity.normalize() * speed * delta * 3;
	}

}

void BigSlimeEnemy::is_dead()
{
	attack_box->set_enable(false);
}

void BigSlimeEnemy::finish_attack()
{
	attack_box->set_enable(false);
	Enemy::finish_attack();
}