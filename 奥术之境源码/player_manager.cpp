#include "player_manager.h"

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::on_enter(int role)
{
	switch (role)
	{
	case 1:
		player = std::make_unique<PlayerClaude>();
		break;
	default:
		break;
	}
}

void PlayerManager::on_input(const SDL_Event& event)
{
	player->on_input(event);
}

void PlayerManager::on_update(double delta)
{
	player->get_camera_position(*CameraManager::instance()->get_position());
	player->on_update(delta);
	CameraManager::instance()->set_player_position(player->get_position());

	StatusBarManager::instance()->set_hp(player->get_max_hp(), player->get_hp());
	StatusBarManager::instance()->set_mp(player->get_max_mp(), player->get_mp());

	MagicManager::instance()->get_player_position(player->get_position());
}

void PlayerManager::on_render(SDL_Renderer* renderer)
{
	player->on_renderer(renderer);
}