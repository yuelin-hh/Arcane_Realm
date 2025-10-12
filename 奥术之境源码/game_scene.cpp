#include "game_scene.h"

GameScene::GameScene()
{
	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_map = tex_pool.find(ResID::Tex_Map)->second;

	map.set_loop(true);
	map.set_interval(0.1);
	map.set_frame_data(tex_map, 1, 1, { 0 });
}

GameScene::~GameScene()
{
}

void GameScene::on_enter()
{
	PlayerManager::instance()->on_enter(SceneManager::instance()->get_role());
	MagicManager::instance()->on_enter(SceneManager::instance()->get_magic_list());
	EnemyManager::instance()->set_gamemod(SceneManager::instance()->gamemode);
}

void GameScene::on_input(const SDL_Event& event)
{
	MouseManager::instance()->on_input(event);
	PlayerManager::instance()->on_input(event);
	MagicManager::instance()->on_input(event);
}

void GameScene::on_update(double delta)
{
	PlayerManager::instance()->on_update(delta);
	MagicManager::instance()->on_update(delta);
	UIManager::instance()->on_update(delta);
	CameraManager::instance()->on_update(delta);
	BulletManager::instance()->on_update(delta);
	EnemyManager::instance()->on_update(delta);
	StatusBarManager::instance()->on_update(delta);
	CollisionManager::instance()->on_update(delta);

	if (PlayerManager::instance()->check_dead())
		ConfigManager::instance()->running = false;
}

void GameScene::on_render(SDL_Renderer* renderer)
{
	SDL_Point point = { 0, 0 };
	map.on_render(renderer, point);

	RetentionManager::instance()->on_renderer(renderer);
	UIManager::instance()->on_render(renderer);
	EnemyManager::instance()->on_render(renderer);
	BulletManager::instance()->on_render(renderer);
	PlayerManager::instance()->on_render(renderer);
	CollisionManager::instance()->on_render(renderer);
	MagicManager::instance()->on_render(renderer);
	StatusBarManager::instance()->on_render(renderer);
}