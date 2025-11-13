#pragma once
#include "map.h"
#include "cell_map.h"
#include "tree.h"

#include <cmath>
#include <vector>
#include <array>
#include <list>

using Result = std::vector<std::array<int, 2>>;

class WayFinding
{
public:
	WayFinding();
	~WayFinding();

	void set_map(Map* map)
	{
		this->map = map;
		cell_map = std::make_shared<CellMap>(map->size_x(),map->size_y());
	}

	Result find_way(int x1, int y1, int x2, int y2);
private:
	std::shared_ptr<CellMap> cell_map = nullptr;
	Map* map;

	double distance(std::shared_ptr<Cell> c1, std::shared_ptr<Cell> c2)
	{
		std::shared_ptr<Cell> temp = c1;
		std::shared_ptr<Cell> next = c2;
		double s = 0;
		
		if (c1->x < c2->x)
		{
			while (temp->x < c2->x)
			{
				next = cell_map->call(temp->x + 1, temp->y);

				s += 16 * (map->call(temp->x, temp->y).wall ? 1 : map->call(temp->x, temp->y).u
					+ map->call(next->x,next->y).wall ? 1 : map->call(next->x,next->y).u + 2);
				temp = next;
			}

			if (c1->y < c2->y)
			{
				while (temp->y < c2->y)
				{
					next = cell_map->call(temp->x, temp->y + 1);

					s += 16 * (map->call(temp->x, temp->y).wall ? 1 : map->call(temp->x, temp->y).u
						+ map->call(next->x, next->y).wall ? 1 : map->call(next->x, next->y).u + 2);
					temp = next;
				}
			}
			else
			{
				while (temp->y > c2->y)
				{
					next = cell_map->call(temp->x, temp->y - 1);

					s += 16 * (map->call(temp->x, temp->y).wall ? 1 : map->call(temp->x, temp->y).u
						+ map->call(next->x, next->y).wall ? 1 : map->call(next->x, next->y).u + 2);
					temp = next;
				}
			}
		}
		else
		{
			while (temp->x > c2->x)
			{
				next = cell_map->call(temp->x - 1, temp->y);

				s += 16 * (map->call(temp->x, temp->y).wall ? 1 : map->call(temp->x, temp->y).u
					+ map->call(next->x, next->y).wall ? 1 : map->call(next->x, next->y).u + 2);
				temp = next;
			}

			if (c1->y < c2->y)
			{
				while (temp->y < c2->y)
				{
					next = cell_map->call(temp->x, temp->y + 1);

					s += 16 * (map->call(temp->x, temp->y).wall ? 1 : map->call(temp->x, temp->y).u
						+ map->call(next->x, next->y).wall ? 1 : map->call(next->x, next->y).u + 2);
					temp = next;
				}
			}
			else
			{
				while (temp->y > c2->y)
				{
					next = cell_map->call(temp->x, temp->y - 1);

					s += 16 * (map->call(temp->x, temp->y).wall ? 1 : map->call(temp->x, temp->y).u
						+ map->call(next->x, next->y).wall ? 1 : map->call(next->x, next->y).u + 2);
					temp = next;
				}
			}
		}
		
		return s;
	}

	void add_to_tree(Tree& tree, std::shared_ptr<Node> node, std::shared_ptr<Cell> target)
	{
		std::shared_ptr<Cell> current = cell_map->call(node->cell->x + 1, node->cell->y);
		if (check_valible(current))
		{
			tree.insert(current, node, (node->c_cost + distance(current, node->cell)), distance(current, target));
			current->traversed = true;
		}

		current = cell_map->call(node->cell->x - 1, node->cell->y);
		if (check_valible(current))
		{
			tree.insert(current, node, (node->c_cost + distance(current, node->cell)), distance(current, target));
			current->traversed = true;
		}

		current = cell_map->call(node->cell->x, node->cell->y + 1);
		if (check_valible(current))
		{
			tree.insert(current, node, (node->c_cost + distance(current, node->cell)), distance(current, target));
			current->traversed = true;
		}

		current = cell_map->call(node->cell->x, node->cell->y - 1);
		if (check_valible(current))
		{
			tree.insert(current, node, (node->c_cost + distance(current, node->cell)), distance(current, target));
			current->traversed = true;
		}
	}

	bool check_valible(std::shared_ptr<Cell> cell)
	{
		if (map->call(cell->x,cell->y).wall == 1
			|| cell->traversed)
			return false;

		return true;
	}
};