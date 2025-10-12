#pragma once
#include "scene.h"
#include "scene_manager.h"

class GameScene:public Scene
{
public:
	GameScene();
	~GameScene();
	void on_enter();

	void on_input(const SDL_Event& event);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

private:
	Animation map;
};