#pragma once
#include "manager.h"

class GameManager: public Manager<GameManager>
{
	friend class Manager<GameManager>;
public:
	int run(int argc, char** argv);
protected:
	GameManager();
	~GameManager();
private:
	SDL_Event event;
	bool is_quit = false;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;


	void on_input();

	void on_update(double delta);

	void on_render();
};