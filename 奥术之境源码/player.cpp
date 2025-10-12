#include "player.h"
#include "mouse_manager.h"

Player::Player()
{
	timer_show_radius.set_one_shot(true);
	timer_show_radius.set_wait_time(0.5);
	timer_show_radius.set_on_timeout([&]() {
		is_show_attack_radius = false;
		});

	timer_show_sketch.set_one_shot(true);
	timer_show_sketch.set_wait_time(0.075);
	timer_show_sketch.set_on_timeout([&]() {
		is_show_sketch = false;
		collide_box->set_enable(true);
		});


	mouse_position = MouseManager::instance()->get_mouse_position();

	MouseManager::instance()->set_left_button_on_click([&]() {
		try_attack();
		});

	MouseManager::instance()->set_right_button_on_click([&]() {
		if (current_magic != nullptr)
			MagicManager::instance()->cancel_choose();
		});

	MouseManager::instance()->set_middle_button_on_click([&]() {
		MagicManager::instance()->get_last_magic();
		});
}

Player::~Player()
{

}

void Player::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			is_move_left = true;
			break;
		case SDLK_d:
			is_move_right = true;
			break;
		case SDLK_w:
			is_move_up = true;
			break;
		case SDLK_s:
			is_move_down = true;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYUP:
		switch (event.key.keysym.sym)
		{
		case SDLK_a:
			is_move_left = false;
			break;
		case SDLK_d:
			is_move_right = false;
			break;
		case SDLK_w:
			is_move_up = false;
			break;
		case SDLK_s:
			is_move_down = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Player::on_update(double delta)
{
	timer_show_radius.on_update(delta);
	timer_attack_cd.on_update(delta);
	timer_show_sketch.on_update(delta);

	current_magic = MagicManager::instance()->get_current_magic();

	set_ui();
	if (current_magic != nullptr && current_magic->need_target)
	{
		Vector2 pos;

		pos.x = position.x - camera_position.x + 640;
		pos.y = position.y - camera_position.y + 360;

		if ((pos - *mouse_position).length() > current_magic->get_radious())
		{
			UIManager::instance()->ui.set_follow_ui_valid(false);
		}
		else
		{
			UIManager::instance()->ui.set_follow_ui_valid(true);
		}
	}
	else if (last_magic != current_magic)
		UIManager::instance()->ui.set_follow_ui_valid(true);
	Vector2 direction =
		Vector2(is_move_right - is_move_left,
			is_move_down - is_move_up).normalize();

	velocity = direction * speed * change_speed;

	if (velocity.x < 0 && position.x - size.x / 2 + 10 > 0)
		position.x += velocity.x * delta;
	if (velocity.x > 0 && position.x + size.x / 2 - 10 < 2000)
		position.x += velocity.x * delta;
	if (velocity.y < 0 && position.y - size.y / 2 > 0)
		position.y += velocity.y * delta;
	if (velocity.y > 0 && position.y + size.y / 2 < 1232)
		position.y += velocity.y * delta;

	if (mouse_position->x > (position.x - camera_position.x + 640))
		is_facing_right = true;
	else if (mouse_position->x < (position.x - camera_position.x + 640))
		is_facing_right = false;

	if (velocity.x != 0 || velocity.y != 0)
		anim_current = is_facing_right ? &anim_run_right : &anim_run_left;
	else
		anim_current = is_facing_right ? &anim_idle_right : &anim_idle_left;

	anim_current->on_update(delta);
	anim_wand->on_update(delta);

	MagicManager::instance()->set_current_mp(mp);

	last_magic = current_magic;

	buff_manager.set_position(position);

	change_speed = 1;
	for (Buff* buff : buff_manager.get_buff_list())
	{
		hp += buff->cause_recover() * delta;
		change_speed += buff->cause_speed_up();
	}
	buff_manager.on_update(delta);

	if (hp >= hp_max)
		hp = hp_max;

	mp = mp + mp_recover * delta;
	if (mp > mp_max)
		mp = mp_max;

	if (hp <= 0)
		is_dead = true;
}

void Player::on_renderer(SDL_Renderer* renderer)
{
	static SDL_Point point, point_ui, point_cycle;
	point.x = (int)(position.x - size.x / 2);
	point.y = (int)(position.y - size.y / 2);

	point_ui.x = (int)(position.x - 16);
	point_ui.y = (int)(position.y - 4);

	point_cycle.x = (int)(position.x - camera_position.x + 640);
	point_cycle.y = (int)(position.y - camera_position.y + 360);

	if (current_magic == nullptr)
	{
		if (is_show_attack_radius)
		{
			circleRGBA(renderer, point_cycle.x, point_cycle.y, (int)(attack_radius), 51, 197, 224, 175);
		}
	}
	else
	{
		circleRGBA(renderer, point_cycle.x, point_cycle.y, (int)(current_magic->get_radious()), 51, 197, 224, 175);
		if (current_magic->need_mouse_position)
		{
			SDL_Point point_mouse;
			Vector2 center;
			center.x = position.x - camera_position.x + 640;
			center.y = position.y - camera_position.y + 360;
			if ((*mouse_position - center).length() <= current_magic->get_radious())
			{
				point_mouse.x = (int)(mouse_position->x + position.x - camera_position.x);
				point_mouse.y = (int)(mouse_position->y + position.y - camera_position.y);
				circleRGBA(renderer, point_mouse.x, point_mouse.y, (int)(current_magic->get_range()), 51, 197, 224, 175);
			}
			else
			{
				Vector2 relay;
				relay = (*mouse_position - center).normalize() * current_magic->get_radious() + center;
				point_mouse.x = (int)(relay.x);
				point_mouse.y = (int)(relay.y);
				circleRGBA(renderer, point_mouse.x, point_mouse.y, (int)(current_magic->get_range()), 51, 197, 224, 175);
			}
		}
	}

	anim_lock_ui.on_render(renderer, point_ui);

	if(!is_show_sketch)
		anim_current->on_render(renderer, point);

	workout_randian();

	point.x += is_facing_right ? 10 : -10;
	point.y += 8;

	if (!is_show_sketch)
		anim_wand->on_render(renderer, point, angle_anim_rotated);

	buff_manager.on_render(renderer);
}

std::shared_ptr<Object> Player::find_target_enemy(double radious)
{
	return MouseManager::instance()->get_target_enemy(position, radious);
}

void Player::wand_attack()
{
	anim_wand = &anim_wand_attack;
	anim_wand->reset();
	anim_wand->set_on_finished([&]() {
		anim_wand = &anim_wand_idle;
		});
}

void Player::release_magic()
{
	set_magic_parameter();
	if (!current_magic->check_can_fire())
		return;
	current_magic->release(attack);
	mp = mp - current_magic->get_consumption();
	if (current_magic->is_self)
		magic_take_effect();
	MagicManager::instance()->cancel_choose();
}

void Player::set_magic_parameter()
{
	if (current_magic->need_velocity)
		current_magic->set_velocity(workout_shoot_velocity());
	if (current_magic->need_start_position)
	{
		workout_shoot_position();
		current_magic->set_start_position(shoot_position);
	}
	if (current_magic->need_target)
		current_magic->set_target_enemy(find_target_enemy(current_magic->get_radious()));
	if (current_magic->need_mouse_position)
	{
		Vector2 correction;
		correction.x = mouse_position->x - 640 + position.x;
		correction.y = mouse_position->y - 360 + position.y;
		current_magic->set_mouse_position(correction);
	}

}

void Player::workout_randian()
{
	double randian = std::atan2(mouse_position->y - (position.y - camera_position.y + 360),
		mouse_position->x - (position.x - camera_position.x + 640));
	angle_anim_rotated = randian * 180 / 3.14159265 + 90;
}

Vector2 Player::workout_shoot_velocity()
{
	Vector2 shoot_velocity;

	shoot_velocity.x = mouse_position->x - (position.x - camera_position.x + 640);
	shoot_velocity.y = mouse_position->y - (position.y - camera_position.y + 360);

	return shoot_velocity;
}

void Player::workout_shoot_position()
{
	Vector2 correction;
	correction.x = mouse_position->x - (position.x - camera_position.x + 640);
	correction.y = mouse_position->y - (position.y - camera_position.y + 360);
	shoot_position.x = correction.normalize().x * 16 + position.x;
	shoot_position.y = correction.normalize().y * 16 + position.y + 8;
	shoot_position.x += is_facing_right ? 10 : -10;
}

void Player::set_ui()
{
	if (current_magic == nullptr)
	{
		UIManager::instance()->ui.set_lock_target(find_target_enemy(attack_radius));
		UIManager::instance()->ui.set_lock_ui_follow(false);
		UIManager::instance()->ui.set_show_lock_ui(true);
	}
	else if (current_magic->need_target)
	{
		UIManager::instance()->ui.set_lock_ui_follow(true);
		UIManager::instance()->ui.set_show_lock_ui(true);
		UIManager::instance()->ui.set_mouse_position(*mouse_position);
		UIManager::instance()->ui.set_lock_target(find_target_enemy(current_magic->get_radious()));
	}
	else
	{
		UIManager::instance()->ui.set_show_lock_ui(false);
		UIManager::instance()->ui.set_lock_ui_follow(false);
	}
}

void Player::try_attack()
{
	if (current_magic == nullptr)
	{
		if (can_attack)
		{
			wand_attack();
			workout_shoot_position();
			if (find_target_enemy(attack_radius))
			{
				BulletManager::instance()->fire_bullet(BulletName::NormalAttack, find_target_enemy(attack_radius), bullet_speed,
					shoot_position, attack * attack_multiplier, {});
				can_attack = false;
				timer_attack_cd.restart();
			}
			else
			{
				is_show_attack_radius = true;
				timer_show_radius.restart();
				BulletManager::instance()->fire_bullet(BulletName::NormalAttack, workout_shoot_velocity(), bullet_speed, shoot_position, shoot_position,
					attack_radius - (position - shoot_position).length(), attack * attack_multiplier, {});
				can_attack = false;
				timer_attack_cd.restart();
			}
			return;
		}
	}
	else
	{
		release_magic();
	}
}

void Player::magic_take_effect()
{
	buff_manager.deliver_buff(current_magic->get_buff_manager().get_buff_list());
}

void Player::cause_damage(double damage)
{
	hp -= damage;
	is_show_sketch = true;
	collide_box->set_enable(false);
	timer_show_sketch.restart();
}