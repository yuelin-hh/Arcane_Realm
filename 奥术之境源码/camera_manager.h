#pragma once

#include "manager.h"
#include "vector2.h"

class CameraManager : public Manager<CameraManager>
{
	friend class Manager<CameraManager>;
public:
	void on_update(double delta)
	{
	}

	void set_player_position(Vector2 pos)
	{
		position = pos;
	}

	const std::shared_ptr<Vector2> get_position()
	{
		
		return a;
	}

	const std::shared_ptr<Vector2> get_player_position()
	{
		
		return a;
	}

protected:
	Vector2 position;
	std::shared_ptr<Vector2> a;

	CameraManager();
	~CameraManager();
private:
};