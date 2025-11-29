#include "physics_engine_manager.h"
#include "check_manager.h"

#include <algorithm>

PhysicsEngineManager::PhysicsEngineManager()
{
}

PhysicsEngineManager::~PhysicsEngineManager()
{
}

std::shared_ptr<PhysicsBox> PhysicsEngineManager::create_physics_box(Vector2 size, double m, Vector2& position)
{
	code++;
	std::shared_ptr<BoxAndTime> box = std::make_shared<BoxAndTime>();;
	box->box = std::make_shared<PhysicsBox>(size, m, position, code);
	physics_box_list.push_back(box);
	return box->box;
}

std::shared_ptr<PhysicsBox> PhysicsEngineManager::create_physics_box(double radius, double m, Vector2& position)
{
	code++;
	std::shared_ptr<BoxAndTime> box = std::make_shared<BoxAndTime>();
	box->box = std::make_shared<PhysicsBox>(radius, m, position, code);
	physics_box_list.push_back(box);
	return box->box;
}

std::shared_ptr<WallBox> PhysicsEngineManager::create_wall_box(Vector2 pos, Vector2 size)
{
	std::shared_ptr<WallBox> box = std::make_shared<WallBox>(pos, size);
	wall_list.push_back(box);
	return box;
}

void PhysicsEngineManager::on_render(SDL_Renderer* renderer)
{
	for (auto box : physics_box_list)
	{
		box->box->on_render(renderer);
	}

	for (auto box : wall_list)
	{
		box->on_render(renderer);
	}
}

void PhysicsEngineManager::check_collide_with_wall(std::shared_ptr<BoxAndTime> box, double t)
{
	if (check_in_wall(box->box->get_position(), box->box->get_size()))
	{
		box->box->back_to_safe_position();
		box->t -= t;
		return;
	}

	box->box->set_safe_position();
	Vector2 distance = box->box->get_velocity() * t;

	if (check_in_wall(box->box->get_position() + distance, box->box->get_size()))
	{
		if (!check_in_wall(Vector2(box->box->get_position().x + distance.x, box->box->get_position().y), box->box->get_size()))
		{
			box->box->move(Vector2(distance.x, 0));
			box->box->set_velocity(Velocity(box->box->get_velocity().x, 0));
		}
		if (!check_in_wall(Vector2(box->box->get_position().x, box->box->get_position().y + distance.y), box->box->get_size()))
		{
			box->box->move(Vector2(0, distance.y));
			box->box->set_velocity(Velocity(0, box->box->get_velocity().y));
		}
	}
	else
	{
		box->box->move(distance);
	}
	box->t -= t;
}

void PhysicsEngineManager::check_collide_possible(double t)
{
	result_list.clear();

	std::sort(physics_box_list.begin(), physics_box_list.end(), [t](std::shared_ptr<BoxAndTime> a, std::shared_ptr<BoxAndTime> b) {
		return (a->box->get_position() + a->box->get_velocity() * t).x < (b->box->get_position() + b->box->get_velocity() * t).x;
		});

	for (int i = 0; i < physics_box_list.size(); i++)
	{
		physics_box_list[i]->t = t;
		for (int j = i + 1; j < physics_box_list.size(); j++)
		{
			if (((physics_box_list[i]->box->get_position() + physics_box_list[i]->box->get_velocity() * t).x + physics_box_list[i]->box->get_size().x / 2) >
				((physics_box_list[j]->box->get_position() + physics_box_list[j]->box->get_velocity() * t).x - physics_box_list[j]->box->get_size().x / 2))
			{
				std::array<std::shared_ptr<BoxAndTime>, 2> array;
				array[0] = physics_box_list[i];
				array[1] = physics_box_list[j];
				result_list.push_back(array);
			}
			else
				break;
		}
	}

}

void PhysicsEngineManager::check_collide(double t)
{
	for (auto array : result_list)
	{
		if ((array[0]->box->get_position() + array[0]->box->get_velocity() * t).y + array[0]->box->get_size().y / 2 > (array[1]->box->get_position() + array[1]->box->get_velocity() * t).y - array[1]->box->get_size().y / 2 &&
			(array[0]->box->get_position() + array[0]->box->get_velocity() * t).y - array[0]->box->get_size().y / 2 < (array[1]->box->get_position() + array[1]->box->get_velocity() * t).y + array[1]->box->get_size().y / 2)
		{
			make_collision(array[0], array[1], t);
		}
	}
}

void PhysicsEngineManager::make_collision(std::shared_ptr<BoxAndTime> box1, std::shared_ptr<BoxAndTime> box2, double t)
{
	double time_x = -1, time_y = -1;
	double distance_y= box1->box->get_position().y - box2->box->get_position().y;

	if (!(box1->box->get_velocity().x - box2->box->get_velocity().x <= 0.001 && box1->box->get_velocity().x - box2->box->get_velocity().x >= -0.001))
		time_x = (-box1->box->get_position().x + box2->box->get_position().x + box1->box->get_size().x / 2 + box2->box->get_size().x / 2) / (box1->box->get_velocity().x - box2->box->get_velocity().x) / 32;
	
	if (!(box1->box->get_velocity().y - box2->box->get_velocity().y <= 0.001 && box1->box->get_velocity().y - box2->box->get_velocity().y >= -0.001))
		time_y = (box1->box->get_size().y / 2 + box2->box->get_size().y / 2 - distance_y * get_symbol(distance_y)) / (box1->box->get_velocity().y - box2->box->get_velocity().y) / 32;
	
	

	if (time_x < 0 || time_x > t) time_x = -1;
	if (time_y < 0 || time_y > t) time_y = -1;

	if (time_y == -1 && time_x != -1)
	{
		check_collide_with_wall(box1, time_x);
		check_collide_with_wall(box2, time_x);
		add_impulse(box1->box, box2->box, true);
	}
	else if (time_y != -1 && time_x == -1)
	{
		check_collide_with_wall(box1, time_y);
		check_collide_with_wall(box2, time_y);
		if (distance_y > 0)
			add_impulse(box2->box, box1->box, false);
		else
			add_impulse(box1->box, box2->box, false);
	}
	else if (time_y < time_x)
	{
		check_collide_with_wall(box1, time_y);
		check_collide_with_wall(box2, time_y);
		if (distance_y > 0)
			add_impulse(box2->box, box1->box, false);
		else
			add_impulse(box1->box, box2->box, false);
	}
	else
	{
		if (time_x != -1)
		{
			check_collide_with_wall(box1, time_x);
			check_collide_with_wall(box2, time_x);
		}
		else
		{
			check_collide_with_wall(box1, t);
			check_collide_with_wall(box2, t);
		}
		add_impulse(box1->box, box2->box, true);
	}
}

void PhysicsEngineManager::add_impulse(std::shared_ptr<PhysicsBox> box1, std::shared_ptr<PhysicsBox> box2, bool is_left_and_right)
{
	double v1, v2, v_;
	if (is_left_and_right)
	{
		switch (box1->is_can_bounce() + box2->is_can_bounce())
		{
		case 2:
			v1 = ((2 * box2->get_weight() * box2->get_velocity().x + (box1->get_weight() - box2->get_weight()) * box1->get_velocity().x)) / (box1->get_weight() + box2->get_weight());
			v2 = ((2 * box1->get_weight() * box1->get_velocity().x + (box2->get_weight() - box1->get_weight()) * box2->get_velocity().x)) / (box1->get_weight() + box2->get_weight());
			
			box1->add_impulse(Impulse(Velocity(v1 - box1->get_velocity().x, 0), box1->get_weight()));
			box2->add_impulse(Impulse(Velocity(v2 - box2->get_velocity().x, 0), box2->get_weight()));
			break;
		case 1:
			v_ = (box1->get_velocity().x * box1->get_weight() + box2->get_velocity().x * box2->get_weight()) / (box1->get_weight() + box2->get_weight());
			box1->add_impulse(Impulse(Velocity(v_ - box1->get_velocity().x, 0), box1->get_weight()));
			box2->add_impulse(Impulse(Velocity(v_ - box2->get_velocity().x, 0), box2->get_weight()));
			break;
		case 0:
			v_ = (box1->get_velocity().x * box1->get_weight() + box2->get_velocity().x * box2->get_weight()) / (box1->get_weight() + box2->get_weight());
			box1->add_impulse(Impulse(Velocity(v_ - box1->get_velocity().x, 0), box1->get_weight()));
			box2->add_impulse(Impulse(Velocity(v_ - box2->get_velocity().x, 0), box2->get_weight()));
			break;
		default:
			break;
		}
	}
	else
	{
		switch (box1->is_can_bounce() + box2->is_can_bounce())
		{
		case 2:
			v1 = ((2 * box2->get_weight() * box2->get_velocity().y + (box1->get_weight() - box2->get_weight()) * box1->get_velocity().y)) / (box1->get_weight() + box2->get_weight());
			v2 = ((2 * box1->get_weight() * box1->get_velocity().y + (box2->get_weight() - box1->get_weight()) * box2->get_velocity().y)) / (box1->get_weight() + box2->get_weight());
			box1->add_impulse(Impulse(Velocity(0, v1 - box1->get_velocity().y), box1->get_weight()));
			box2->add_impulse(Impulse(Velocity(0, v2 - box2->get_velocity().y), box2->get_weight()));
			break;
		case 1:
			v_ = (box1->get_velocity().y * box1->get_weight() + box2->get_velocity().y * box2->get_weight()) / (box1->get_weight() + box2->get_weight());
			box1->add_impulse(Impulse(Velocity(0, v_ - box1->get_velocity().y), box1->get_weight()));
			box2->add_impulse(Impulse(Velocity(0, v_ - box2->get_velocity().y), box2->get_weight()));
			break;
		case 0:
			v_ = (box1->get_velocity().y * box1->get_weight() + box2->get_velocity().y * box2->get_weight()) / (box1->get_weight() + box2->get_weight());
			box1->add_impulse(Impulse(Velocity(0, v_  - box1->get_velocity().y), box1->get_weight()));
			box2->add_impulse(Impulse(Velocity(0, v_  - box2->get_velocity().y), box2->get_weight()));
			break;
		default:
			break;
		}
	}
}