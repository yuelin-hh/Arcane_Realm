#pragma once
#include <iostream>
#include <array>
#include <list>

#include "random.h"

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
	using TileMap = std::array<std::array<Element, size_y>, size_x>;
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
		int start_x, start_y;
		random_start(start_x, start_y);
		wait_list.push_back(std::array<int, 2>{start_x, start_y});

		while (!wait_list.empty())
		{
			extend(wait_list.front()[0], wait_list.front()[1]);
			wait_list.pop_front();
		}
	}

	friend std::ostream& operator<< (std::ostream& os, Map<size_x, size_y> map)
	{
		for (int i = 0; i < size_y ; i++)
		{
			for (int j = 0; j < size_x; j++)
			{
				switch (map.tile_map[j][i])
				{
				case Element::Null:
					os << " ";
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
	 std::list<std::array<int, 2>> wait_list;
	 void random_start(int& x, int& y)
	 {
		 int x_range1 = size_x > 2 ? size_x - 2 : size_x;
		 int y_range1 = size_y > 2 ? size_y - 2 : size_y;
		 int x_range2 = size_x > 2 ? 1 : 0;
		 int y_range2 = size_y > 2 ? 1 : 0;

		 x = rand() % x_range1 + x_range2;
		 y = rand() % y_range1 + y_range2;

		 while (Random::check(0.5))
		 {
			 x = rand() % x_range1 + x_range2;
		 }
		 while (Random::check(0.5))
		 {
			 y = rand() % y_range1 + y_range2;
		 }

		 tile_map[x][y] = Element::Start;
	 }

	 void creat_room(int x, int y)
	 {
		 if (Random::check(0.5)) return;

		 if (tile_map[x][y] == Element::Null)
		 {
			 tile_map[x][y] = Element::Room;
			 wait_list.push_back(std::array<int, 2>{x, y});
		 }
	 }

	 void extend(int x, int y)
	 {
		 if (x > 0)creat_room(x - 1, y);
		 if (y > 0)creat_room(x , y - 1);
		 if (x < size_x - 1)creat_room(x + 1, y);
		 if (y < size_y - 1)creat_room(x, y + 1);
	 }
};