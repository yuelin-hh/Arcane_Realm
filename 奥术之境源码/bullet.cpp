#include "bullet.h"

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	if(collide_box)
		collide_box->make_invalid();
}

void Bullet::on_update(double delta)
{
	anim_current->on_update(delta);
}

void Bullet::on_render(SDL_Renderer* renderer)
{
	SDL_Point point;

	point.x = (int)(position.x - size.x / 2);
	point.y = (int)(position.y - size.y / 2);
	anim_current->on_render(renderer, point);
}

void Bullet::set_bullet_parameter(double damage, double speed, std::shared_ptr<Object> target, Vector2 pos, BuffManager::BuffList list)
{
	this->target = target;
	this->speed = speed;
	position = pos;
	target_size = target->get_size();
	this->damage = damage;
	type = BulletType::Trace;
	buff_manager.deliver_buff(list);
	if (collide_box)
	{
		collide_box->set_damage(damage);
		collide_box->set_buff(list);
	}
}

void Bullet::set_bullet_parameter(double damage, double distance, double speed, Vector2 shoot_velocity, Vector2 start_pos, Vector2 pos, BuffManager::BuffList list)
{
	velocity = shoot_velocity;
	this->speed = speed;
	this->start_pos = start_pos;
	position = pos;
	this->distance = distance;
	this->damage = damage;
	type = BulletType::Line;
	buff_manager.deliver_buff(list);
	if (collide_box)
	{
		collide_box->set_damage(damage);
		collide_box->set_buff(list);
	}
}

void Bullet::set_bullet_parameter(double damage, std::shared_ptr<Object> target, BuffManager::BuffList list)
{
	this->target = target;
	this->damage = damage;
	type = BulletType::Assign;
	buff_manager.deliver_buff(list);
	if (collide_box)
	{
		collide_box->set_damage(damage);
		collide_box->set_buff(list);
	}
}

void Bullet::set_bullet_parameter(double damage, double distance, Vector2 pos, BuffManager::BuffList list, double duration)
{
	position = pos;
	this->damage = damage;
	this->distance = distance;
	type = BulletType::AOE;
	buff_manager.deliver_buff(list);
	anim_bullet_fly.reset();
	this->duration = duration;
	if (collide_box)
	{
		collide_box->set_damage(damage);
		collide_box->set_buff(list);
	}
}

void Bullet::deliver_buff(std::shared_ptr<Object> enemy)
{
	enemy->deliver_buff(buff_manager.get_buff_list());
}