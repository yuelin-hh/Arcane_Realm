#include "physics_collide_box.h"

PhysicsBox::PhysicsBox(Vector2 size, double m, Vector2& position, int code):size(size),m(m),position(position),code(code)
{
	shape = Shape::Square;
}

PhysicsBox::PhysicsBox(double radius, double m, Vector2& position, int code) :radius(radius), m(m), position(position),code(code)
{
	shape = Shape::Circle;
}

PhysicsBox::~PhysicsBox()
{
}

void PhysicsBox::on_render(SDL_Renderer* renderer)
{
	switch (shape)
	{
	case Shape::Square:
		SDL_Rect rect;
		rect.x = int(position.x - size.x / 2);
		rect.y = int(position.y - size.y / 2);
		rect.w = int(size.x);
		rect.h = int(size.y);

		SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
		SDL_RenderDrawRect(renderer, &rect);
		break;
	case Shape::Circle:
		SDL_Point point;
		point.x = (int)(position.x);
		point.y = (int)(position.y);

		circleRGBA(renderer, point.x, point.y, (int)(radius), 255, 100, 100, 255);
		break;
	default:
		break;
	}

}