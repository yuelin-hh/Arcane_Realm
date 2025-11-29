#pragma once
#include "map.h"
#include "physics_engine_manager.h"

class CreateWallTool
{
private:
	CreateWallTool();
	~CreateWallTool();
public:
	void set_map(Map* map)
	{
		this->map = map;
	}

	void create_wall()
	{
		if (map && !map->check_is_created())
		{
			build_wall();
			map->set_is_created();
		}
	}

	static CreateWallTool* instance()
	{
		if (!create_wall_tool)
			create_wall_tool = new CreateWallTool();

		return create_wall_tool;
	}

private:
	Map* map;
	static CreateWallTool* create_wall_tool;

	void build_wall()
	{
		for (int i = 0; i < map->get_height(); i++)
		{
			for (int j = 0; j < map->get_width(); j++)
			{
				if (map->get_tile_map()[i][j].wall == 1 && map->get_tile_map()[i][j].wall_box == nullptr)
				{
					//std::cout << i << "  " << j << "  " << (tile_map[i][j].wall_box == nullptr) << std::endl;
					int x = check_in_column(i, j);
					int y = check_in_row(i, j);

					if (x >= y)
					{
						fill_wall(i, j, check_column_in_row(i, j, x), x);
					}
					else
					{
						fill_wall(i, j, y, check_row_in_column(i, j, y));
					}
				}
			}
		}
	}

	int check_in_column(int i, int j)
	{
		int num = 0;
		while (j < map->get_width() && map->get_tile_map()[i][j].wall == 1 && map->get_tile_map()[i][j].wall_box == nullptr)
		{
			num++;
			j++;
		}
		return num;
	}

	int check_in_row(int i, int j)
	{
		int num = 0;
		while (i < map->get_height() && map->get_tile_map()[i][j].wall == 1 && map->get_tile_map()[i][j].wall_box == nullptr)
		{
			num++;
			i++;
		}
		return num;
	}

	int check_column_in_row(int i, int j, int length)
	{
		int sum = 0;
		bool flag = true;

		while (flag && i < map->get_height())
		{
			for (int idx = j; idx < j + length; idx++)
			{
				if (map->get_tile_map()[i][idx].wall != 1 || map->get_tile_map()[i][idx].wall_box != nullptr)
				{
					flag = false;
				}
			}
			i++;
			sum++;
		}
		if (i == map->get_height())sum++;
		return sum - 1;
	}

	int check_row_in_column(int i, int j, int length)
	{
		int sum = 0;
		bool flag = true;

		while (flag && j < map->get_width())
		{
			for (int idx = i; idx < i + length; idx++)
			{
				if (map->get_tile_map()[idx][j].wall != 1 || map->get_tile_map()[idx][j].wall_box != nullptr)
					flag = false;
			}
			j++;
			sum++;
		}
		if (j == map->get_width())sum++;
		return sum - 1;
	}

	void fill_wall(int i, int j, int height, int width)
	{
		Vector2 pos(j * 32, i * 32);

		Vector2 size(width * 32, height * 32);

		std::shared_ptr<WallBox> box = PhysicsEngineManager::instance()->create_wall_box(pos, size);

		for (int idx_y = i; idx_y < i + height; idx_y++)
		{
			for (int idx_x = j; idx_x < j + width; idx_x++)
			{
				map->get_tile_map()[idx_y][idx_x].wall_box = box;
			}
		}
	}
};