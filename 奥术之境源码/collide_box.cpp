#include "collide_box.h"

#include <SDL2_gfxPrimitives.h>

CollideBox::CollideBox(CollisionShape shape, Vector2 size, const Vector2& position, int code):shape(shape),size(size),position(position),code(code)
{
}

CollideBox::CollideBox(CollisionShape shape, double radius, const Vector2& position, int code):shape(shape),radius(radius),position(position),code(code)
{
}

CollideBox::~CollideBox()
{
	
}

void CollideBox::on_render(SDL_Renderer* renderer)
{
	switch (shape)
	{
	case CollisionShape::Spuare:
		SDL_Rect rect;
		rect.x = int(position.x - size.x / 2);
		rect.y = int(position.y - size.y / 2);
		rect.w = int(size.x);
		rect.h = int(size.y);

		rect.x = (int)(rect.x - CameraManager::instance()->get_position()->x + 640);
		rect.y = (int)(rect.y - CameraManager::instance()->get_position()->y + 360);

		is_enable() ? SDL_SetRenderDrawColor(renderer, 255, 50, 50, 200) : SDL_SetRenderDrawColor(renderer, 50, 50, 255, 200);
		SDL_RenderDrawRect(renderer, &rect);
		break;
	case CollisionShape::Circle:
		SDL_Point point;
		point.x = (int)(position.x - CameraManager::instance()->get_position()->x + 640);
		point.y = (int)(position.y - CameraManager::instance()->get_position()->y + 360);

		is_enable() ? circleRGBA(renderer, point.x, point.y, (int)(radius), 255, 50, 50, 200) : circleRGBA(renderer, point.x, point.y, (int)(radius), 50, 50, 255, 200);
		break;
	default:
		break;
	}
}