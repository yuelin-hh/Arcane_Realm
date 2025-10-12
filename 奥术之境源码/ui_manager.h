#pragma once

#include "manager.h"
#include "UI.h"

#include <SDL.h>

class UIManager : public Manager<UIManager>
{
	friend class Manager<UIManager>;
protected:
	UIManager();
	~UIManager();

public:
	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	UI ui;
};