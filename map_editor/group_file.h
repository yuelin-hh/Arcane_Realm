#pragma once
#include "button_group.h"
#include "resources_manager.h"
#include "file_manager.h"
#include <iostream>

class GroupFile: public ButtonGroup
{
public:
	GroupFile();
	~GroupFile();

private:
	Button open_file;
	Button new_file;
	Button save_file;
};

GroupFile::GroupFile()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();
	SDL_Texture* tex_ui = tex_pool.find(ResID::Tex_UI)->second;
	SDL_Rect rect;

	open_file.set_anim(tex_ui, 1, 4, { 0 });
	open_file.set_on_click([]() {
		std::wcout << L"Open File" << std::endl; 
		std::wcout << FileManager::instance()->get_current_file() << std::endl;
		});
	rect.x = 0, rect.y = 65, rect.w = 256, rect.h = 62;
	open_file.set_rect(rect);
	button_list.push_back(std::shared_ptr<Button>(&open_file));

	new_file.set_anim(tex_ui, 1, 4, { 1 });
	new_file.set_on_click([]() {
		std::wcout << L"New File" << std::endl; 
		});
	rect.x = 0, rect.y = 129, rect.w = 256, rect.h = 62;
	new_file.set_rect(rect);
	button_list.push_back(std::shared_ptr<Button>(&new_file));

	save_file.set_anim(tex_ui, 1, 4, { 2 });
	save_file.set_on_click([]() {
		std::wcout << L"Save File" << std::endl; 
		});
	rect.x = 0, rect.y = 193, rect.w = 256, rect.h = 62;
	save_file.set_rect(rect);
	button_list.push_back(std::shared_ptr<Button>(&save_file));
}

GroupFile::~GroupFile()
{
}