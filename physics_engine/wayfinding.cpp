#include "wayfinding.h"

WayFinding::WayFinding()
{
}

WayFinding::~WayFinding()
{
}

Result WayFinding::find_way(int x1, int y1, int x2, int y2)
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
	result.push_back(std::array<int, 2>{x1, y1});
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