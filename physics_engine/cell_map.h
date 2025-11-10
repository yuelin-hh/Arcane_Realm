#pragma once
#include "cell.h"
#include "tile.h"

#include <memory>

class CellMap
{
public:
	using CellList = std::vector<std::shared_ptr<Cell>>;

	CellMap();
	CellMap(int x, int y);
	~CellMap();

	void create_map(int x , int y)
	{
		size_x = x;
		size_y = y;
		for (int j = 0; j < y; j++)
		{
			for (int i = 0; i < x; i++)
			{
				std::shared_ptr<Cell> cell = std::make_shared<Cell>(i,j);
				cell_list.push_back(cell);
			}
		}
	}

	std::shared_ptr<Cell> call(int x, int y)
	{
		return cell_list[x + size_x * y];
	}

private:
	int size_x = 0;
	int size_y = 0;
	CellList cell_list;
};