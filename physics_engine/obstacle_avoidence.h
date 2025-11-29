#pragma once
#include "map.h"

class ObstacleAvoidence
{
protected:
	ObstacleAvoidence();
	~ObstacleAvoidence();
public:
	static ObstacleAvoidence* instance()
	{
		if (!obstacle_avoidence)
			obstacle_avoidence = new ObstacleAvoidence();

		return obstacle_avoidence;
	}

	Vector2 get_force(const Vector2& position)
	{
		Vector2 force;
		int x = position.x / 32;
		int y = position.y / 32;
	}
private:
	static ObstacleAvoidence* obstacle_avoidence;
};