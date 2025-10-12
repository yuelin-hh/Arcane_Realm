#include "camera_manager.h"

CameraManager::CameraManager()
{
	position.x = 640;
	position.y = 360;

	std::shared_ptr<Vector2> b(&position);
	a = b;
}

CameraManager::~CameraManager()
{
}