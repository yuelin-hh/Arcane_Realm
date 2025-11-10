#pragma once
#include <iostream>
#include <array>

enum class Element
{
	Null = 0,
	Start,
	Room
};

template<int size_x, int size_y>
class Map
{
public:
	using TileMap = std::array<std::array<Element, size_x>, size_y>;
	Map()
	{
		for (auto& line : tile_map)
		{
			for (auto& one : line)
			{
				one = Element::Null;
			}
		}
	}
	~Map(){}
	
	void create_tile_map()
	{
		//填入随机生成地图的算法
	}

	friend std::ostream& operator<< (std::ostream& os, Map<size_x, size_y> map)
	{
		for (const auto& line : map.tile_map)
		{
			for (const auto& one : line)
			{
				switch (one)
				{
				case Element::Null:
					os << "1";
					break;
				case Element::Start:
					os << "#";
					break;
				case Element::Room:
					os << "O";
					break;
				default:
					break;
				}
				os << " ";
			}
			os << std::endl;
		}
		return os;
	}

private:
	 TileMap tile_map;
};