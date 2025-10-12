#define SDL_MAIN_HANDLED

#include "game_manager.h"

#include<random>

std::random_device rd;
std::mt19937 gen(rd());

int main(int argc, char** argv)
{
	return GameManager::instance()->run(argc, argv);
}