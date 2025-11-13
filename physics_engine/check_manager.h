#pragma once
#include "manager.h"
#include "map.h"
#include "vector2.h"

class CheckManager : public Manager<CheckManager>
{
	friend class Manager<CheckManager>;
protected:
	CheckManager();
	~CheckManager();
public:
	void set_map(Map* map)
	{
		this->map = map;
	}

	bool check_no_wall_in_line(const Vector2& position, Vector2 distance)
	{
		// 处理接近零的距离
		if (std::fabs(distance.x) < 0.01 && std::fabs(distance.y) < 0.01)
			return true;

		Vector2 start = position;
		Vector2 end = position + distance;

		// 转换为网格坐标
		int startX = static_cast<int>(start.x / 32);
		int startY = static_cast<int>(start.y / 32);
		int endX = static_cast<int>(end.x / 32);
		int endY = static_cast<int>(end.y / 32);

		// 处理垂直移动
		if (std::fabs(distance.x) < 0.01) {
			int yStep = (distance.y > 0) ? 1 : -1;
			for (int y = startY; y != endY + yStep; y += yStep) {
				if (map->call(startX, y).wall == 1)
					return false;
			}
			return true;
		}

		// 处理水平移动
		if (std::fabs(distance.y) < 0.01) {
			int xStep = (distance.x > 0) ? 1 : -1;
			for (int x = startX; x != endX + xStep; x += xStep) {
				if (map->call(x, startY).wall == 1)
					return false;
			}
			return true;
		}

		// 使用 Bresenham 算法进行斜线检测
		int dx = std::abs(endX - startX);
		int dy = std::abs(endY - startY);
		int x = startX;
		int y = startY;
		int n = 1 + dx + dy;
		int x_inc = (endX > startX) ? 1 : -1;
		int y_inc = (endY > startY) ? 1 : -1;
		int error = dx - dy;
		dx *= 2;
		dy *= 2;

		for (; n > 0; --n) {
			if (map->call(x, y).wall == 1)
				return false;

			if (error > 0) {
				x += x_inc;
				error -= dy;
			}
			else {
				y += y_inc;
				error += dx;
			}
		}

		return true;
	}

	bool check_no_wall_in_rect(const Vector2& position, const Vector2& size, Vector2 distance)
	{
		Vector2 a(position.x - size.x / 2, position.y - size.y / 2);
		if (!check_no_wall_in_line(a, distance))return false;
		a.x += size.x;
		if (!check_no_wall_in_line(a, distance))return false;
		a.x += size.x;
		a.y += size.y;
		if (!check_no_wall_in_line(a, distance))return false;
		a.y -= size.y;
		if (!check_no_wall_in_line(a, distance))return false;

		return true;
	}

	bool check_no_wall_between_two_points(const Vector2& position1, const Vector2& position2)
	{
		return check_no_wall_in_line(position1, position2 - position1);
	}
private:
	Map* map = nullptr;
};