#pragma once
#include "tile.h"
#include "physics_engine_manager.h"

#include <SDL.h>
#include <string>
#include <fstream>
#include <sstream>

class Map
{
public:
	Map();
	~Map();

	bool load(const std::string& path)
	{
		std::ifstream file(path, std::ios::binary);  // 用二进制模式打开
		if (!file.good()) return false;

		// 检查并跳过BOM
		char bom[3];
		file.read(bom, 3);
		if (static_cast<unsigned char>(bom[0]) != 0xEF ||
			static_cast<unsigned char>(bom[1]) != 0xBB ||
			static_cast<unsigned char>(bom[2]) != 0xBF) {
			// 如果不是BOM，回退文件指针
			file.seekg(0);
		}

		TileMap tile_map_temp;

		int idx_x = -1;
		int idx_y = -1;
		std::string str_line;

		while (std::getline(file, str_line))
		{
			str_line = trim_str(str_line);
			if (str_line.empty())
				continue;

			idx_x = -1 , idx_y++;
			tile_map_temp.emplace_back();

			std::string str_tile;
			std::stringstream str_stream(str_line);
			while (std::getline(str_stream,str_tile,','))
			{
				idx_x++;
				tile_map_temp[idx_y].emplace_back();
				Tile& tile = tile_map_temp[idx_y].back();
				load_tile_from_string(tile, str_tile);
			}

		}

		file.close();

		if (tile_map_temp.empty() || tile_map_temp[0].empty())
			return false;

		tile_map = tile_map_temp;
		build_wall();

		//std::cout << tile_map[0][0].wall;
		return true;
	}

	int get_width() const
	{
		if (tile_map.empty())
			return 0;

		return tile_map[0].size();
	}

	int get_height() const
	{
		return tile_map.size();
	}

	TileMap& get_tile_map()
	{
		return tile_map;
	}

private:
	TileMap tile_map;

	std::string trim_str(const std::string& str)
	{
		size_t begin_idx = str.find_first_not_of(" \t\"");
		if (begin_idx == std::string::npos)
			return "";
		size_t end_idx = str.find_last_not_of(" \t\"");
		size_t idx_range = end_idx - begin_idx + 1;

		return str.substr(begin_idx, idx_range);
	}

	void load_tile_from_string(Tile& tile, const std::string& str)
	{
		std::string str_tidy = trim_str(str);

		std::string str_value;
		std::vector<double> values;
		std::stringstream str_stream(str_tidy);

		while (std::getline(str_stream, str_value, '/'))
		{
			double value;
			try
			{
				value = std::stof(str_value);
			}
			catch (const std::invalid_argument&)
			{
				value = -1;
			}
			values.push_back(value);
		}

		tile.wall = (values.size() < 1 || (values[0] != 0 && values[0] != 1)) ? 0 : values[0];
		tile.u = (values.size() < 2 || (values[1] == -1)) ? 0.2 : values[1];
	}

	void build_wall()
	{
		for (int i = 0; i < get_height(); i++)
		{
			for (int j = 0; j < get_width(); j++)
			{
				if (tile_map[i][j].wall == 1 && tile_map[i][j].wall_box == nullptr)
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
		while (j < get_width() && tile_map[i][j].wall == 1 && tile_map[i][j].wall_box == nullptr)
		{
			num++;
			j++;
		}
		return num;
	}

	int check_in_row(int i, int j)
	{
		int num = 0;
		while (i < get_height() && tile_map[i][j].wall == 1 && tile_map[i][j].wall_box == nullptr)
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

		while (flag && i < get_height())
		{
			for (int idx = j; idx < j + length; idx++)
			{
				if (tile_map[i][idx].wall != 1 || tile_map[i][idx].wall_box != nullptr)
				{
					flag = false;
				}
			}
			i++;
			sum++;
		}
		if (i == get_height())sum++;
		return sum - 1;
	}

	int check_row_in_column(int i, int j, int length)
	{
		int sum = 0;
		bool flag = true;

		while (flag && j < get_width())
		{
			for (int idx = i; idx < i + length; idx++)
			{
				if (tile_map[idx][j].wall != 1 || tile_map[idx][j].wall_box != nullptr)
					flag = false;
			}
			j++;
			sum++;
		}
		if (j == get_width())sum++;
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
				tile_map[idx_y][idx_x].wall_box = box;
			}
		}
	}
};