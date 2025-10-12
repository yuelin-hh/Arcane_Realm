#pragma once
#include "manager.h"
#include "scene.h"

#include <SDL.h>

class SceneManager: public Manager<SceneManager>
{
	friend class Manager<SceneManager>;
protected:
	SceneManager();
	~SceneManager();

public:
	enum SceneType
	{
		Menu,
		Select,
		Game
	};

	void on_input(const SDL_Event& event);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void switch_to(SceneType name);

	void set_menu_scene(std::shared_ptr<Scene> scene);

	void set_select_scene(std::shared_ptr<Scene> scene);

	void set_game_scene(std::shared_ptr<Scene> scene);

	void set_role(int code);

	void set_magic(int* magic_list);

	int get_role();

	int* get_magic_list();

public:
	int gamemode = 0;

	int role = 0;
	int* magic_list;

private:
	std::shared_ptr<Scene> menu_scene;
	std::shared_ptr<Scene> select_scene;
	std::shared_ptr<Scene> game_scene;
	std::shared_ptr<Scene> current_scene;
};