#include "physics_engine_manager.h"
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
	/*for (int i = 1; i <= 39; i++)
	{
		SDL_SetRenderDrawColor(renderer, 100, 255, 100, 100);
		SDL_RenderDrawLine(renderer, i * 32, 0, i * 32, 720);
	}

	for (int i = 1; i <= 22; i++)
	{
		SDL_SetRenderDrawColor(renderer, 100, 255, 100, 100);
		SDL_RenderDrawLine(renderer, 0, i * 32, 1280, i * 32);
	}*/

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
	if (t > 0.5)return;

	int i_dst = 0, j_dst = 0;
	Vector2 distance;
	bool flag;
	double t_current = t;
	double y_time = -1, x_time = -1;

	flag = false;
	distance = box->box->get_velocity() * t;
	t_current = t;

	try {
		while (true)
		{
			if (t_current <= 0.001)
				break;
			if (distance.x <= 0.000001 && distance.x >= -0.000001 && distance.y <= 0.000001 && distance.y >= -0.000001)
				{
					break;
				}
			else if (distance.x <= 0.000001 && distance.x >= -0.000001)
				{
					int i = (int)((box->box->get_position().y + distance.y + box->box->get_size().y / 2 * get_symbol(distance.y)) / 32);

					for (int j = (int)((box->box->get_position().x - box->box->get_size().x / 2) / 32);
						j <= (int)((box->box->get_position().x + box->box->get_size().x / 2) / 32); j++)
					{
						if (tile_map.at(i).at(j).wall == 1)
						{
							i_dst = i, j_dst = j;
							flag = true;
							break;
						}
					}

					if (flag)
					{
						Vector2 temp_distance;
						temp_distance.y = (i_dst * 32 - 16 * get_symbol(distance.y) + 16) - (box->box->get_position().y + box->box->get_size().y / 2 * get_symbol(distance.y)) - get_symbol(distance.y);
						
						box->box->move(temp_distance);
						Impulse I(0, -box->box->get_velocity().y * box->box->get_weight());
						box->box->add_impulse(I);
						if (box->box->is_can_bounce())
						{
							box->box->move(temp_distance - distance);
							box->box->add_impulse(I);
						}
					}
					else
					{
						box->box->move(distance);
					}
					break;
				}
			else if (distance.y <= 0.000001 && distance.y >= -0.000001)
				{
					int j = (int)((box->box->get_position().x + distance.x + box->box->get_size().x / 2 * get_symbol(distance.x)) / 32);

					for (int i = (int)((box->box->get_position().y - box->box->get_size().y / 2) / 32);
						i <= (int)((box->box->get_position().y + box->box->get_size().y / 2) / 32); i++)
					{
						if (tile_map.at(i).at(j).wall == 1)
						{
							i_dst = i, j_dst = j;
							flag = true;
							break;
						}
					}

					if (flag)
					{
						Vector2 temp_distance;
						temp_distance.x = (j_dst * 32 - 16 * get_symbol(distance.x) + 16) - (box->box->get_position().x + box->box->get_size().x / 2 * get_symbol(distance.x)) - get_symbol(distance.x);

						box->box->move(temp_distance);
						Impulse I(-box->box->get_velocity().x * box->box->get_weight(), 0);
						box->box->add_impulse(I);
						if (box->box->is_can_bounce())
						{
							box->box->move(temp_distance - distance);
							box->box->add_impulse(I);
						}
					}
					else
					{
						box->box->move(distance);
					}
					break;
				}
			else
				{
					y_time = -1, x_time = -1;

					i_dst = (int)((box->box->get_position().y + distance.y + box->box->get_size().y / 2 * get_symbol(distance.y)) / 32);
					y_time = ((i_dst * 32 - 16 * get_symbol(distance.y) + 16) - (box->box->get_position().y + box->box->get_size().y / 2 * get_symbol(distance.y)) - get_symbol(distance.y)*2) / box->box->get_velocity().y / 32;

					if (y_time <= t_current)
					{
						flag = false;
						for (int j = int((box->box->get_position().x - box->box->get_size().x / 2 + box->box->get_velocity().x * y_time) / 32);
							j <= int((box->box->get_position().x + box->box->get_size().x / 2 + box->box->get_velocity().x * y_time) / 32); j++)
						{
							if (tile_map.at(i_dst).at(j).wall == 1)
							{
								flag = true;
								break;
							}
						}
						if (!flag)
							y_time = -1;
					}
					else
					{
						y_time = -1;
					}


					j_dst = (int)((box->box->get_position().x + distance.x + box->box->get_size().x / 2 * get_symbol(distance.x)) / 32);
					x_time = ((j_dst * 32 - 16 * get_symbol(distance.x) + 16) - (box->box->get_position().x + box->box->get_size().x / 2 * get_symbol(distance.x)) - get_symbol(distance.x)*2) / box->box->get_velocity().x / 32;

					if (x_time <= t_current)
					{
						flag = false;
						for (int i = int((box->box->get_position().y - box->box->get_size().y / 2 + box->box->get_velocity().y * x_time) / 32);
							i <= int((box->box->get_position().y + box->box->get_size().y / 2 + box->box->get_velocity().y * x_time) / 32); i++)
						{
							if (tile_map.at(i).at(j_dst).wall == 1)
							{
								flag = true;
								break;
							}
						}
						if (!flag)
							x_time = -1;
					}
					else
					{
						x_time = -1;
					}

					if (y_time == -1 && x_time == -1)
					{
						box->box->move(distance);
						break;
					}
					else if (y_time == -1)
					{
						Vector2 distance_temp;
						distance_temp.x = box->box->get_velocity().x * x_time;
						distance_temp.y = distance.y;
						box->box->move(distance_temp);
						Impulse I(-box->box->get_velocity().x * box->box->get_weight(), 0);
						box->box->add_impulse(I);
						if (box->box->is_can_bounce())
						{
							box->box->move(distance_temp - distance);
							box->box->add_impulse(I);
						}
						break;
					}
					else if (x_time == -1)
					{
						Vector2 distance_temp;
						distance_temp.y = box->box->get_velocity().y * y_time;
						distance_temp.x = distance.x;
						box->box->move(distance_temp);
						Impulse I(0, -box->box->get_velocity().y * box->box->get_weight());
						box->box->add_impulse(I);
						if (box->box->is_can_bounce())
						{
							box->box->move(distance_temp - distance);
							box->box->add_impulse(I);
						}
						break;
					}
					else if (y_time < x_time)
					{
						Vector2 distance_temp;
						distance_temp.y = box->box->get_velocity().y * y_time;
						distance_temp.x = box->box->get_velocity().x * y_time;
						box->box->move(distance_temp);
						Impulse I(0, -box->box->get_velocity().y * box->box->get_weight());
						box->box->add_impulse(I);
						t_current -= abs(y_time);
						if (box->box->is_can_bounce())
						{
							box->box->add_impulse(I);
							distance -= distance_temp;
							distance.y = -distance.y;
						}
						else
						{
							distance -= distance_temp;
							distance.y = 0;
						}
						box->box->on_update(y_time);
					}
					else
					{
						Vector2 distance_temp;
						distance_temp.y = box->box->get_velocity().y * x_time;
						distance_temp.x = box->box->get_velocity().x * x_time;
						box->box->move(distance_temp);
						Impulse I(-box->box->get_velocity().x * box->box->get_weight(), 0);
						box->box->add_impulse(I);
						t_current -= abs(x_time);
						if (box->box->is_can_bounce())
						{
							box->box->add_impulse(I);
							distance -= distance_temp;
							distance.y = -distance.y;
						}
						else
						{
							distance -= distance_temp;
							distance.x = 0;
						}
						box->box->on_update(x_time);
					}
				}

		}
	}
	catch(std::out_of_range)
		{
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