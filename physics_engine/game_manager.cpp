#include "game_manager.h"
#include "object_manager.h"
#include "physics_engine_manager.h"

GameManager::GameManager()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "0");

	window = SDL_CreateWindow("physical_engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	SDL_RenderSetLogicalSize(renderer, 1280, 720);

}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
}

int GameManager::run(int argc, char** argv)
{
	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_freq = SDL_GetPerformanceFrequency();

	while (!is_quit)
	{
		while (SDL_PollEvent(&event))
			on_input();
		Uint64 current_counter = SDL_GetPerformanceCounter();
		double delta = (double)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		if (delta * 1000 < 1000.0 / 120)
			SDL_Delay((Uint32)(1000.0 / 120 - delta * 1000));

		on_update(delta);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		on_render();

		SDL_RenderPresent(renderer);
	}

	return 0;
}

void GameManager::on_input()
{
	switch (event.type)
	{
	case SDL_QUIT:
		is_quit = true;
		break;
	default:
		
		break;
	}
}

void GameManager::on_update(double delta)
{
	ObjectManager::instance()->on_update(delta);
	PhysicsEngineManager::instance()->on_update(delta);
}

void GameManager::on_render()
{
	PhysicsEngineManager::instance()->on_render(renderer);
	ObjectManager::instance()->on_render(renderer);
}