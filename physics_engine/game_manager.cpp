#include "game_manager.h"
#include "object_manager.h"
#include "physics_engine_manager.h"
#include "input_method_manager.h"
#include "map_manager.h"

GameManager::GameManager()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	window = SDL_CreateWindow("physical_engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	InputMethodManager::instance()->SetEnglishInput(window);

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

	InputMethodManager::instance()->RestoreInputMethod();
	return 0;
}

void GameManager::on_input()
{
	switch (event.type)
	{
	case SDL_QUIT:
		is_quit = true;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_q:
			flag = !flag;
			break;
		default:
			break;
		}
		break;
	default:
		ObjectManager::instance()->on_input(event);
		break;
	}
}

void GameManager::on_update(double delta)
{
	MapManager::instance()->on_update(delta);
	ObjectManager::instance()->on_update(delta);
	PhysicsEngineManager::instance()->on_update(delta);
}

void GameManager::on_render()
{
	if (flag)
	{
		for (int i = 1; i <= 39; i++)
		{
			SDL_SetRenderDrawColor(renderer, 100, 255, 100, 100);
			SDL_RenderDrawLine(renderer, i * 32, 0, i * 32, 720);
		}

		for (int i = 1; i <= 22; i++)
		{
			SDL_SetRenderDrawColor(renderer, 100, 255, 100, 100);
			SDL_RenderDrawLine(renderer, 0, i * 32, 1280, i * 32);
		}
	}
	PhysicsEngineManager::instance()->on_render(renderer);
	ObjectManager::instance()->on_render(renderer);
}