#pragma once
#include "tile.h"

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

			idx_x = -1, idx_y++;
			tile_map_temp.emplace_back();

			std::string str_tile;
			std::stringstream str_stream(str_line);
			while (std::getline(str_stream, str_tile, ','))
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

	const Tile& call(int x, int y)
	{
		if (y >= 0 && x >= 0 && y < tile_map.size() && x < tile_map[0].size())
			return tile_map[y][x];
		else
			return null_tile;
	}

	int size_x() { return tile_map[0].size(); }
	int size_y() { return tile_map.size(); }

	bool check_is_created() { return is_created; }
	void set_is_created() { is_created = true; }

private:
	Tile null_tile;
	TileMap tile_map;
	bool is_created = false;

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
};

Map::Map()
{
}

Map::~Map()
{
}