#pragma once
#include "button_group.h"
#include "resources_manager.h"
#include "message_manager.h"
#include "transcoder.h"

#include <iostream>

class GroupSelect: public ButtonGroup
{
public:
	GroupSelect();
	~GroupSelect();

private:
	Button file;
	Button tile;
	std::string topic_select = "select";
};

GroupSelect::GroupSelect()
{
	MessageManager::instance()->create_topic(topic_select, 10, true);

	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();
	SDL_Texture* tex_ui = tex_pool.find(ResID::Tex_UI)->second;
	SDL_Rect rect;

	file.set_anim(tex_ui, 2, 4, { 6 });
	file.set_on_click([this]() {
		std::wcout << L"File" << std::endl;
		MessageManager::instance()->send_message(topic_select, Transcoder::trans_int_message(0));
		});
	rect.x = 1, rect.y = 0, rect.w = 126, rect.h = 62;
	file.set_rect(rect);
	button_list.push_back(std::shared_ptr<Button>(&file));

	tile.set_anim(tex_ui, 2, 4, { 7 });
	tile.set_on_click([this]() {
		std::wcout << L"Tile" << std::endl; 
		MessageManager::instance()->send_message(topic_select, Transcoder::trans_int_message(1));
		});
	rect.x = 130, rect.y = 0, rect.w = 126, rect.h = 62;
	tile.set_rect(rect);
	button_list.push_back(std::shared_ptr<Button>(&tile));
}

GroupSelect::~GroupSelect()
{
}