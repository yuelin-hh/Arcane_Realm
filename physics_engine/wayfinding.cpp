#include "wayfinding.h"

WayFinding::WayFinding()
{
}

WayFinding::~WayFinding()
{
}

//Result WayFinding::find_way(int x1, int y1, int x2, int y2)
//{
//	std::shared_ptr<Cell> start = cell_map->call(x1, y1);
//	std::shared_ptr<Cell> target = cell_map->call(x2, y2);
//	Tree wait_tree;
//	std::vector<std::shared_ptr<Node>> result_list;
//	
//	result_list.push_back(std::make_shared<Node>(start, nullptr, 0, distance(start, target)));
//	
//	add_to_tree(wait_tree, result_list[0], target);
//	
//	while (true)
//	{
//		if (wait_tree.empty()) return Result();
//
//		std::shared_ptr<Node> current = wait_tree.head();
//		wait_tree.pop();
//
//		result_list.push_back(current);
//
//		if (current->cell == target) break;
//
//		add_to_tree(wait_tree, current, target);
//	}
//
//	std::shared_ptr<Node> current = result_list[result_list.size() - 1];
//	Result result;
//
//	while (current->source->cell != start)
//	{
//		result.push_back(std::array<int, 2>{current->cell->x, current->cell->y});
//		current = current->source;
//	}
//	result.push_back(std::array<int, 2>{x1, y1});
//	std::reverse(result.begin(), result.end());
//
//	for (auto node : result_list)
//	{
//		node->cell->traversed = false;
//	}
//
//	while (!wait_tree.empty())
//	{
//		wait_tree.head()->cell->traversed = false;
//		wait_tree.pop();
//	}
//
//	return result;
//}

Result WayFinding::find_way(int x1, int y1, int x2, int y2) {
    std::shared_ptr<Cell> start = cell_map->call(x1, y1);
    std::shared_ptr<Cell> target = cell_map->call(x2, y2);
    Tree wait_tree;

    // 重置所有单元格的遍历状态
    for (int x = 0; x < map->size_x(); x++) {
        for (int y = 0; y < map->size_y(); y++) {
            cell_map->call(x, y)->traversed = false;
        }
    }

    // 添加起点
    auto start_node = std::make_shared<Node>(start, nullptr, 0,
        std::abs(x1 - x2) + std::abs(y1 - y2));  // 曼哈顿距离
    wait_tree.insert(start, nullptr, 0, std::abs(x1 - x2) + std::abs(y1 - y2));
    start->traversed = true;

    while (!wait_tree.empty()) {
        std::shared_ptr<Node> current = wait_tree.head();
        wait_tree.pop();

        // 检查是否到达目标
        if (current->cell->x == x2 && current->cell->y == y2) {
            // 重建路径
            Result result;
            std::shared_ptr<Node> path_node = current;

            while (path_node != nullptr) {
                result.push_back(std::array<int, 2>{path_node->cell->x, path_node->cell->y});
                path_node = path_node->source;
            }

            std::reverse(result.begin(), result.end());
            return result;
        }

        // 扩展当前节点
        add_to_tree(wait_tree, current, target);
    }

    return Result();  // 没有找到路径
}