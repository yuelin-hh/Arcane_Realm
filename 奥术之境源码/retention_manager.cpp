#include "retention_manager.h"

RetentionManager::RetentionManager()
{
}

RetentionManager::~RetentionManager()
{
	retention_list.clear();
}

void RetentionManager::on_update(double delta)
{

}

void RetentionManager::on_renderer(SDL_Renderer* renderer)
{
	for (RetentionStruct retention : retention_list)
	{
		SDL_Point point;
		point.x = (int)(retention.pos.x - retention.size.x / 2);
		point.y = (int)(retention.pos.y - retention.size.y / 2);
		retention.retention.on_render(renderer, point, retention.angle);
	}
	retention_list.clear();
}

void RetentionManager::set_retention(Animation* anim, Vector2 pos, Vector2 size, double angle)
{
	RetentionStruct retention;
	retention.retention.set_animation(anim);
	retention.pos = pos;
	retention.size = size;
	retention.angle = angle;
	retention_list.push_back(retention);
}