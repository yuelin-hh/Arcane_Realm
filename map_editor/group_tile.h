#pragma once
#include "button_group.h"
#include "resources_manager.h"
#include "file_manager.h"
#include <iostream>

class GroupTile: public ButtonGroup
{
public:
	GroupTile();
	~GroupTile();

private:
	Button wall;
	Button grass;
	Button way;
	Button lava;
};

GroupTile::GroupTile()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();
	SDL_Texture* tex_ui = tex_pool.find(ResID::Tex_Tile)->second;
	SDL_Rect rect;

	grass.set_anim(tex_ui, 2, 2, { 0 });
	grass.set_on_click([]() {

		});
	rect.x = 2, rect.y = 67, rect.w = 60, rect.h = 60;
	grass.set_rect(rect);
	button_list.push_back(std::shared_ptr<Button>(&grass));

	wall.set_anim(tex_ui, 2, 2, { 1 });
	wall.set_on_click([]() {

		});
	rect.x = 67, rect.y = 67, rect.w = 60, rect.h = 60;
	wall.set_rect(rect);
	button_list.push_back(std::shared_ptr<Button>(&wall));

	way.set_anim(tex_ui, 2, 2, { 2 });
	way.set_on_click([]() {

		});
	rect.x = 131, rect.y = 67, rect.w = 60, rect.h = 60;
	way.set_rect(rect);
	button_list.push_back(std::shared_ptr<Button>(&way));

	lava.set_anim(tex_ui, 2, 2, { 3 });
	lava.set_on_click([]() {

		});
	rect.x = 195, rect.y = 67, rect.w = 60, rect.h = 60;
	lava.set_rect(rect);
	button_list.push_back(std::shared_ptr<Button>(&lava));
}

GroupTile::~GroupTile()
{
}