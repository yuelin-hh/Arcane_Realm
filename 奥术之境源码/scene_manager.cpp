#include "scene_manager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::on_input(const SDL_Event& event)
{
	current_scene->on_input(event);
}

void SceneManager::on_update(double delta)
{
	current_scene->on_update(delta);
}

void SceneManager::on_render(SDL_Renderer* renderer)
{
	current_scene->on_render(renderer);
}

void SceneManager::switch_to(SceneType name)
{
	switch (name)
	{
	case SceneManager::Menu:
		current_scene = menu_scene;
		break;
	case SceneManager::Select:
		current_scene = select_scene;
		break;
	case SceneManager::Game:
		current_scene = game_scene;
		break;
	default:
		break;
	}
	current_scene->on_enter();
}

void SceneManager::set_menu_scene(std::shared_ptr<Scene> scene)
{
	menu_scene = scene;
	current_scene = menu_scene;
}

void SceneManager::set_select_scene(std::shared_ptr<Scene> scene)
{
	select_scene = scene;
}

void SceneManager::set_game_scene(std::shared_ptr<Scene> scene)
{
	game_scene = scene;
}

void SceneManager::set_role(int code)
{
	role = code;
}

void SceneManager::set_magic(int* magic_list)
{
	this->magic_list = magic_list;
}

int SceneManager::get_role()
{
	return role;
}

int* SceneManager::get_magic_list()
{
	return magic_list;
}