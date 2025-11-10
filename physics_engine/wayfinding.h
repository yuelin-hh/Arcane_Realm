#pragma once
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

	void set_map(TileMap& tile_map)
	{
		this->tile_map = tile_map;
		cell_map = std::make_shared<CellMap>(tile_map[0].size(), tile_map.size());
	}

	Result find_way(int x1, int y1, int x2, int y2)
	{
		std::shared_ptr<Cell> start = cell_map->call(x1, y1);
		std::shared_ptr<Cell> target = cell_map->call(x2, y2);
		Tree wait_tree;
		std::vector<std::shared_ptr<Node>> result_list;

		result_list.push_back(std::make_shared<Node>(start, nullptr, 0, distance(start, target)));

		add_to_tree(wait_tree, result_list[0], target);
		while (true)
		{
			if (wait_tree.empty()) return Result();

			std::shared_ptr<Node> current = wait_tree.head();
			wait_tree.pop();
			result_list.push_back(current);

			if (current->cell == target) break;

			add_to_tree(wait_tree, current, target);
		}

		std::shared_ptr<Node> current = result_list[result_list.size() - 1];
		Result result;

		while (current->source->cell != start)
		{
			result.push_back(std::array<int, 2>{current->cell->x, current->cell->y});
			current = current->source;
		}

		std::reverse(result.begin(), result.end());

		for (auto node : result_list)
		{
			node->cell->traversed = false;
		}

		while (!wait_tree.empty())
		{
			wait_tree.head()->cell->traversed = false;
			wait_tree.pop();
		}

		return result;
	}
private:
	std::shared_ptr<CellMap> cell_map = nullptr;
	TileMap tile_map;

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

				s += 16 * (tile_map[temp->x][temp->y].wall ? 1 : tile_map[temp->x][temp->y].u
					+ tile_map[next->x][next->y].wall ? 1 : tile_map[next->x][next->y].u);
				temp = next;
			}

			if (c1->y < c2->y)
			{
				while (temp->y < c2->y)
				{
					next = cell_map->call(temp->x, temp->y + 1);

					s += 16 * (tile_map[temp->x][temp->y].wall ? 1 : tile_map[temp->x][temp->y].u
						+ tile_map[next->x][next->y].wall ? 1 : tile_map[next->x][next->y].u);
					temp = next;
				}
			}
			else
			{
				while (temp->y > c2->y)
				{
					next = cell_map->call(temp->x, temp->y - 1);

					s += 16 * (tile_map[temp->x][temp->y].wall ? 1 : tile_map[temp->x][temp->y].u
						+ tile_map[next->x][next->y].wall ? 1 : tile_map[next->x][next->y].u);
					temp = next;
				}
			}
		}
		else
		{
			while (temp->x > c2->x)
			{
				next = cell_map->call(temp->x - 1, temp->y);

				s += 16 * (tile_map[temp->x][temp->y].wall ? 1 : tile_map[temp->x][temp->y].u
					+ tile_map[next->x][next->y].wall ? 1 : tile_map[next->x][next->y].u);
				temp = next;
			}

			if (c1->y < c2->y)
			{
				while (temp->y < c2->y)
				{
					next = cell_map->call(temp->x, temp->y + 1);

					s += 16 * (tile_map[temp->x][temp->y].wall ? 1 : tile_map[temp->x][temp->y].u
						+ tile_map[next->x][next->y].wall ? 1 : tile_map[next->x][next->y].u);
					temp = next;
				}
			}
			else
			{
				while (temp->y > c2->y)
				{
					next = cell_map->call(temp->x, temp->y - 1);

					s += 16 * (tile_map[temp->x][temp->y].wall ? 1 : tile_map[temp->x][temp->y].u
						+ tile_map[next->x][next->y].wall ? 1 : tile_map[next->x][next->y].u);
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
		if (tile_map[cell->x][cell->y].wall == 1
			|| cell->traversed)
			return false;

		return true;
	}
};