#include "lighting_bullet.h"

LightingBullet::LightingBullet()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_lighting = tex_pool.find(ResID::Tex_BulletLighting)->second;

	anim_bullet_fly.set_loop(false);
	anim_bullet_fly.set_interval(0.2);
	anim_bullet_fly.set_frame_data(tex_lighting, 1, 1, { 0 });

	anim_current = &anim_bullet_fly;

	anim_bullet_fly.set_on_finished([&]() {
		make_invalid();
		});

	size.x = 32, size.y = 64;

	target_list = CollisionManager::instance()->get_collide_box_list();
}

LightingBullet::~LightingBullet()
{
	for (auto box : box_list)
	{
		box->make_invalid();
	}
	box_list.clear();
	position_list.clear();
}

void LightingBullet::on_update(double delta)
{
	if (!is_collide)
	{
		find_way();
		target_list.clear();
	}
	else if(flag)
	{
		for (auto box : box_list)
		{
			box->set_enable(false);
		}
		flag = false;
	}
	Bullet::on_update(delta);
}

void LightingBullet::on_render(SDL_Renderer* renderer)
{
	std::shared_ptr<CollideBox> last_enemy = nullptr;

	for (auto enemy : box_list)
	{
		if (last_enemy == nullptr)
			draw_lighting(renderer, position, enemy->get_position());
		else
			draw_lighting(renderer, last_enemy->get_position(), enemy->get_position());

		last_enemy = enemy;
	}
}

void LightingBullet::find_way()
{
	Vector2 pos = target->get_position();

	creat_collide_box(target->get_collide_box());

	for (int i = 1; i <= 4; i++)
	{
		double distance = 0;
		std::shared_ptr<CollideBox> target_enemy = nullptr;

		for (auto enemy : target_list)
		{
			if (!enemy->is_enable() || enemy->get_layer_src() != 4)
				continue;

			if ((distance == 0 || (enemy->get_position() - pos).length() <= distance) && check_repetieion(enemy))
			{
				distance = (enemy->get_position() - pos).length();
				target_enemy = enemy;
			}
		}

		if (distance <= 400 && target_enemy != nullptr)
		{

			creat_collide_box(target_enemy);
			pos = target_enemy->get_position();

		}
		else
		{
			break;
		}
	}

	is_collide = true;
}

bool LightingBullet::check_repetieion(std::shared_ptr<CollideBox> target)
{
	for (auto enemy : box_list)
	{
		if (enemy->get_lock_target() == target->get_code())
			return false;
	}
	return true;
}

void LightingBullet::draw_lighting(SDL_Renderer* renderer, Vector2 pos1, Vector2 pos2)
{
	Vector2 direction = pos2 - pos1;
	double distance = direction.length();
	double angle = atan2(direction.y, direction.x) * 180.0 / M_PI + 90;

	int segments = (int)(distance / size.y) + 1;

	double increment = direction.length() / segments;

	for (int i = 0; i < segments; i++)
	{
		Vector2 segment_pos = pos1 + direction.normalize()*increment * (i + 0.5);
		SDL_Point point;
		point.x = (int)(segment_pos.x - size.x / 2);
		point.y = (int)(segment_pos.y - size.y / 2);
		anim_current->on_render(renderer, point, angle);
	}
}

void LightingBullet::creat_collide_box(std::shared_ptr<CollideBox> target_box)
{
	
	std::shared_ptr<Vector2> pos = std::make_shared<Vector2>();
	pos->x = target_box->get_position().x;
	pos->y = target_box->get_position().y;
	std::shared_ptr<CollideBox> box = CollisionManager::instance()->create_collide_box(1, *pos);
	box->set_layer_src(tools::to_ten("1000"));
	box->set_layer_dst(tools::to_ten("100"));
	box->set_damage(damage);
	box->set_lock(target_box->get_code());
	box->set_on_collide([&]() {
		std::cout << 1;
		});
	box_list.push_back(box);
	position_list.push_back(pos);
}
