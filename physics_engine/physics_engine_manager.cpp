#include "physics_engine_manager.h"

PhysicsEngineManager::PhysicsEngineManager()
{
}

PhysicsEngineManager::~PhysicsEngineManager()
{
}

std::shared_ptr<PhysicsBox> PhysicsEngineManager::create_physics_box(Vector2 size, double m, Vector2& position)
{
	code++;
	std::shared_ptr<PhysicsBox> box = std::make_shared<PhysicsBox>(size, m, position, code);
	physics_box_list.push_back(box);
	return box;
}

std::shared_ptr<PhysicsBox> PhysicsEngineManager::create_physics_box(double radius, double m, Vector2& position)
{
	code++;
	std::shared_ptr<PhysicsBox> box = std::make_shared<PhysicsBox>(radius, m, position, code);
	physics_box_list.push_back(box);
	return box;
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
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, j_dst * 32, 0, j_dst * 32, 720);

	SDL_SetRenderDrawColor(renderer, 255, 100, 255, 255);
	SDL_RenderDrawLine(renderer, 0, i_dst * 32, 1280, i_dst * 32);*/

	for (auto box : physics_box_list)
	{
		box->on_render(renderer);
	}
	for (auto box : wall_list)
	{
		box->on_render(renderer);
	}
}

void PhysicsEngineManager::check_collide_with_wall(double t)
{
	
	Vector2 distance;
	bool flag;
	double t_current = t;
	double y_time = -1, x_time = -1;

	for (auto box : physics_box_list)
	{
		flag = false;
		distance = box->get_velocity() * t;
		t_current = t;

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
				int i = (int)((box->get_position().y + distance.y + box->get_size().y / 2 * get_symbol(distance.y)) / 32);

				for (int j = (int)((box->get_position().x - box->get_size().x / 2) / 32);
					j <= (int)((box->get_position().x + box->get_size().x / 2) / 32); j++)
				{
					if (tile_map[i][j].wall == 1)
					{
						i_dst = i, j_dst = j;
						flag = true;
						break;
					}
				}

				if (flag)
				{
					Vector2 temp_distance;
					temp_distance.y = (i_dst * 32 - 16 * get_symbol(distance.y) + 16) - (box->get_position().y + box->get_size().y / 2 * get_symbol(distance.y));
					box->move(temp_distance);
					Impulse I(0, -box->get_velocity().y * box->get_weight());
					box->add_impulse(I);
					if (box->is_can_bance())
					{
						box->move(temp_distance - distance);
						box->add_impulse(I);
					}
				}
				else
				{
					box->move(distance);
				}
				break;
			}
			else if (distance.y <= 0.000001 && distance.y >= -0.000001)
			{
				int j = (int)((box->get_position().x + distance.x + box->get_size().x / 2 * get_symbol(distance.x)) / 32);

				for (int i = (int)((box->get_position().y - box->get_size().y / 2) / 32);
					i <= (int)((box->get_position().y + box->get_size().y / 2) / 32); i++)
				{
					if (tile_map[i][j].wall == 1)
					{
						i_dst = i, j_dst = j;
						flag = true;
						break;
					}
				}

				if (flag)
				{
					Vector2 temp_distance;
					temp_distance.x = (j_dst * 32 - 16 * get_symbol(distance.x) + 16) - (box->get_position().x + box->get_size().x / 2 * get_symbol(distance.x));
					box->move(temp_distance);
					Impulse I(-box->get_velocity().x * box->get_weight(), 0);
					box->add_impulse(I);
					if (box->is_can_bance())
					{
						box->move(temp_distance - distance);
						box->add_impulse(I);
					}
				}
				else
				{
					box->move(distance);
				}
				break;
			}
			else
			{
				y_time = -1, x_time = -1;

				i_dst = (int)((box->get_position().y + distance.y + box->get_size().y / 2 * get_symbol(distance.y)) / 32);
				if (i_dst != (int)((box->get_position().y + box->get_size().y / 2 * get_symbol(distance.y)) / 32))
				{
					
					y_time = ((i_dst * 32 - 16 * get_symbol(distance.y) + 16) - (box->get_position().y + box->get_size().y / 2 * get_symbol(distance.y))) / box->get_velocity().y/32;
					//std::cout <<"y:" << y_time <<"  "<< t_current << std::endl;
					//std::cout << distance.y / box->get_velocity().y << std::endl;
					//std::cout << (i_dst * 32 - 16 * get_symbol(distance.y) + 16) - (box->get_position().y + box->get_size().y / 2 * get_symbol(distance.y)) << "\n";
					if (y_time <= t_current)
					{
						//std::cout << 1;
						flag = false;
						for (int j = int((box->get_position().x - box->get_size().x / 2 + box->get_velocity().x * y_time) / 32);
							j <= int((box->get_position().x + box->get_size().x / 2 + box->get_velocity().x * y_time) / 32); j++)
						{
							if (tile_map[i_dst][j].wall == 1)
							{
								//std::cout << i_dst << "  " << j << std::endl;
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
				}
				
				j_dst = (int)((box->get_position().x + distance.x + box->get_size().x / 2 * get_symbol(distance.x)) / 32);
				if (j_dst != (int)((box->get_position().x + box->get_size().x / 2 * get_symbol(distance.x)) / 32))
				{
					
					x_time = ((j_dst * 32 - 16 * get_symbol(distance.x) + 16) - (box->get_position().x + box->get_size().x / 2 * get_symbol(distance.x))) / box->get_velocity().x/32;
					//std::cout <<"x:" << x_time <<"  "<<t_current << std::endl;
					//std::cout << distance.x / box->get_velocity().x << std::endl;
					//std::cout << (j_dst * 32 - 16 * get_symbol(distance.x) + 16) - (box->get_position().x + box->get_size().x / 2 * get_symbol(distance.x)) << "\n";

					if (x_time <= t_current)
					{
						//std::cout << 1;
						flag = false;
						for (int i = int((box->get_position().y - box->get_size().y / 2 + box->get_velocity().y * x_time) / 32);
							i <= int((box->get_position().y + box->get_size().y / 2 + box->get_velocity().y * x_time) / 32); i++)
						{
							if (tile_map[i][j_dst].wall == 1)
							{
								//std::cout << i << "  " << j_dst << std::endl;
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
				}

				//std::cout << distance.x << "  " << distance.y << std::endl;
				//std::cout << i_dst << "  " << j_dst << "\n\n";
				if (y_time == -1 && x_time == -1)
				{
					box->move(distance);
					break;
				}
				else if (y_time == -1)
				{
					Vector2 distance_temp;
					distance_temp.x = box->get_velocity().x * x_time;
					distance_temp.y = distance.y;
					box->move(distance_temp);
					Impulse I(-box->get_velocity().x * box->get_weight(), 0);
					box->add_impulse(I);
					if (box->is_can_bance())
					{
						box->move(distance_temp - distance);
						box->add_impulse(I);
					}
					break;
				}
				else if (x_time == -1)
				{
					Vector2 distance_temp;
					distance_temp.y = box->get_velocity().y * y_time;
					distance_temp.x = distance.x;
					box->move(distance_temp);
					Impulse I(0, -box->get_velocity().y * box->get_weight());
					box->add_impulse(I);
					if (box->is_can_bance())
					{
						box->move(distance_temp - distance);
						box->add_impulse(I);
					}
					break;
				}
				else if (y_time < x_time)
				{
					Vector2 distance_temp;
					distance_temp.y = box->get_velocity().y * y_time;
					distance_temp.x = box->get_velocity().x * y_time;
					box->move(distance_temp);
					Impulse I(0, -box->get_velocity().y * box->get_weight());
					box->add_impulse(I);
					t_current -= abs(y_time);
					if (box->is_can_bance())
					{
						box->add_impulse(I);
						distance -= distance_temp;
						distance.y = -distance.y;
					}
					else
					{
						distance -= distance_temp;
						distance.y = 0;
					}
					box->on_update(y_time);
				}
				else
				{
					Vector2 distance_temp;
					distance_temp.y = box->get_velocity().y * x_time;
					distance_temp.x = box->get_velocity().x * x_time;
					box->move(distance_temp);
					Impulse I(-box->get_velocity().x * box->get_weight(), 0);
					box->add_impulse(I);
					t_current -= abs(x_time);
					if (box->is_can_bance())
					{
						box->add_impulse(I);
						distance -= distance_temp;
						distance.y = -distance.y;
					}
					else
					{
						distance -= distance_temp;
						distance.x = 0;
					}
					box->on_update(x_time);
				}
			}

		}
	}
}