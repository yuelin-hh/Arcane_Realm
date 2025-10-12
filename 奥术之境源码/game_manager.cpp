#include "game_manager.h"

GameManager::GameManager()
{
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 ³õÊ¼»¯Ê§°Ü£¡");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_imgae ³õÊ¼»¯Ê§°Ü£¡");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer ³õÊ¼»¯Ê§°Ü£¡");
	init_assert(!TTF_Init(), u8"SDL_ttf ³õÊ¼»¯Ê§°Ü£¡");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	ConfigManager* config = ConfigManager::instance();

	init_assert(config->load_game_config("config.json"), u8"¼ÓÔØÓÎÏ·ÅäÖÃÊ§°Ü£¡");

	window = SDL_CreateWindow(config->basic_template.window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		config->basic_template.window_width, config->basic_template.window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	init_assert(window, u8"´´½¨ÓÎÏ·´°¿ÚÊ§°Ü£¡");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	SDL_RenderSetLogicalSize(renderer, config->basic_template.window_width, config->basic_template.window_height);
	init_assert(renderer, u8"´´½¨äÖÈ¾Æ÷Ê§°Ü£¡");

	init_assert(ResourcesManager::instance()->load_from_file(renderer), u8"¼ÓÔØÓÎÏ·×ÊÔ´Ê§°Ü£¡");

	menu_scene = std::make_shared<MenuScene>();
	select_scene = std::make_shared<SelectScene>();
	game_scene = std::make_shared<GameScene>();

	SceneManager::instance()->set_menu_scene(menu_scene);
	SceneManager::instance()->set_select_scene(select_scene);
	SceneManager::instance()->set_game_scene(game_scene);

}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int GameManager::run(int argc, char** argv)
{
	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_freq = SDL_GetPerformanceFrequency();

	menu_scene->on_enter();

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

		if (!ConfigManager::instance()->running)
			is_quit = true;
	}
	return 0;
}

void GameManager::init_assert(bool flag, const char* err_msg)
{
	if (flag) return;

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"ÓÎÏ·Æô¶¯Ê§°Ü", err_msg, window);
	exit(-1);
}

void GameManager::on_input()
{
	switch (event.type)
	{
	case SDL_QUIT:
		is_quit = true;
		break;
	default:
		SceneManager::instance()->on_input(event);
		break;
	}

}

void GameManager::on_update(double delta)
{
	SceneManager::instance()->on_update(delta);
}

void GameManager::on_render()
{
	SceneManager::instance()->on_render(renderer);
}