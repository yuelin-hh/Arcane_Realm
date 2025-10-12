#include "enemy.h"

Enemy::Enemy()
{
	timer_sketch.set_one_shot(true);
	timer_sketch.set_wait_time(0.075);

	timer_buff_damage.set_one_shot(false);
	timer_buff_damage.set_wait_time(0.5);
	timer_buff_damage.set_on_timeout([&]() {
		if (buff_damage >= 0.001)
		{
			cause_damage(buff_damage);
			buff_damage = 0;
		}
		});

	static const ResourcesManager::TexturePool& texture_pool
		= ResourcesManager::instance()->get_texture_pool();
	static SDL_Texture* tex_spawn = texture_pool.find(ResID::Tex_SpawnEnemy)->second;

	anim_spawn.set_loop(false);
	anim_spawn.set_interval(0.3);
	anim_spawn.set_frame_data(tex_spawn, 2, 1, { 0,1 });

	anim_spawn.set_on_finished([&]()
		{
			is_on_spawn = false;
		});
}

Enemy::~Enemy()
{
}

void Enemy::on_update(double delta)
{
	if (!check_can_update(delta)) return;

	buff_on_update(delta);

	if (is_find_target)
	{
		if ((position - player_position).length() > attack_radius && state == State::Nullptr)
			way_finding(delta);
		else if ((position - player_position).length() <= attack_radius && state == State::Nullptr && can_attack)
		{
			attack(delta);
		}
		else if (state != State::Nullptr && can_attack)
			attack(delta);
	}
	else
	{
		lock_target();
	}

	anim_current->on_update(delta);
	anim_current_sketch->on_update(delta);
	
	timer_sketch.on_update(delta);
	timer_attack_interval.on_update(delta);
}

void Enemy::on_render(SDL_Renderer* renderer)
{
	SDL_Point point;
	point.x = (int)(position.x - size.x / 2);
	point.y = (int)(position.y - size.y / 2);

	if (is_on_spawn)
	{
		anim_spawn.on_render(renderer, point);
		return;
	}

	if (!is_show_sketch)
		anim_current->on_render(renderer, point);
	else
		anim_current_sketch->on_render(renderer, point);

	buff_manager.on_render(renderer);
}

void Enemy::cause_damage(double attack)
{
	is_find_target = true;
	show_sketch();
	hp -= attack;
}

void Enemy::buff_on_update(double delta)
{
	buff_manager.set_position(position);

	timer_buff_damage.on_update(delta);
	for (Buff* buff : buff_manager.get_buff_list())
	{
		buff_damage += buff->cause_damage() * delta;
	}
	buff_manager.on_update(delta);
}

bool Enemy::check_can_update(double delta)
{
	if (is_on_spawn)
	{
		anim_spawn.on_update(delta);
		return false;
	}

	if (hp <= 0)
	{
		make_invalid();
		collide_box->set_enable(false);
		collide_box->make_invalid();
		is_dead();
		return false;
	}
		
	collide_box->set_enable(true);
	return true;
}

void Enemy::lock_target()
{
	if ((player_position - position).length() <= view_radius)
		is_find_target = true;
}

void Enemy::way_finding(double delta)
{
	velocity = player_position - position;

	if (velocity.x < 0)
	{
		anim_current = &anim_move_right;
		anim_current_sketch = &anim_move_right_sketch;
	}
	else if (velocity.x > 0)
	{
		anim_current = &anim_move_left;
		anim_current_sketch = &anim_move_left_sketch;
	}

	position += velocity.normalize() * speed * delta;
}

void Enemy::show_sketch()
{
	is_show_sketch = true;
	timer_sketch.restart();
	timer_sketch.set_on_timeout([&]() {
		is_show_sketch = false;
		});
}

void Enemy::attack(double delta)
{
}

void Enemy::is_dead()
{

}

void Enemy::finish_attack()
{
	state = State::Nullptr;

	if (velocity.x < 0)
	{
		anim_current = &anim_idle_right;
		anim_current_sketch = &anim_idle_right_sketch;
	}
	else if (velocity.x > 0)
	{
		anim_current = &anim_idle_left;
		anim_current_sketch = &anim_idle_left_sketch;
	}

	can_attack = false;
}