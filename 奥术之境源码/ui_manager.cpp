#include "ui_manager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::on_update(double delta)
{
	ui.on_update(delta);
}

void UIManager::on_render(SDL_Renderer* renderer)
{
	ui.on_render(renderer);
}