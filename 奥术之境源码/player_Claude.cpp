#include "player_Claude.h"

PlayerClaude::PlayerClaude()
{
	hp_max = ConfigManager::instance()->claude_template.hp;
	speed = ConfigManager::instance()->claude_template.speed;
	attack = ConfigManager::instance()->claude_template.attack;
	attack_multiplier = ConfigManager::instance()->claude_template.attack_multiplier;
	attack_interval = ConfigManager::instance()->claude_template.attack_interval;
	attack_radius = ConfigManager::instance()->claude_template.attack_radius;
	bullet_speed = ConfigManager::instance()->claude_template.bullet_speed;
	mp_max = ConfigManager::instance()->claude_template.mp;
	mp_recover = ConfigManager::instance()->claude_template.mp_recover;

	hp = hp_max;
	mp = mp_max;

	timer_attack_cd.set_one_shot(false);
	timer_attack_cd.set_wait_time(attack_interval);
	timer_attack_cd.set_on_timeout([&]()
		{
			can_attack = true;
		});

	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_player_idle = tex_pool.find(ResID::Tex_ClaudeIdle)->second;
	SDL_Texture* tex_player_run = tex_pool.find(ResID::Tex_ClaudeRun)->second;
	SDL_Texture* tex_wand = tex_pool.find(ResID::Tex_ClaudeWand)->second;
	SDL_Texture* tex_lock_ui = tex_pool.find(ResID::Tex_LockUI)->second;


	anim_lock_ui.set_loop(true);
	anim_lock_ui.set_interval(1);
	anim_lock_ui.set_frame_data(tex_lock_ui, 3, 1, { 0 });

	anim_idle_left.set_loop(true);
	anim_idle_left.set_interval(0.3);
	anim_idle_left.set_frame_data(tex_player_idle, 2, 2, { 2,3 });
	anim_idle_right.set_loop(true);
	anim_idle_right.set_interval(0.3);
	anim_idle_right.set_frame_data(tex_player_idle, 2, 2, { 0,1 });

	anim_run_left.set_loop(true);
	anim_run_left.set_interval(0.2);
	anim_run_left.set_frame_data(tex_player_run, 2, 2, { 2,3 });
	anim_run_right.set_loop(true);
	anim_run_right.set_interval(0.2);
	anim_run_right.set_frame_data(tex_player_run, 2, 2, { 0,1 });

	anim_wand_idle.set_loop(true);
	anim_wand_idle.set_interval(0.3);
	anim_wand_idle.set_frame_data(tex_wand, 2, 2, { 0,1 });
	anim_wand_attack.set_loop(false);
	anim_wand_attack.set_interval(0.2);
	anim_wand_attack.set_frame_data(tex_wand, 2, 2, { 2,3 });

	position.x = 640;
	position.y = 320;

	size.x = 64, size.y = 64;

	anim_wand = &anim_wand_idle;

	Vector2 size_box;
	size_box.x = size.x / 2.3;
	size_box.y = size.y / 1.5;
	
	collide_box = CollisionManager::instance()->create_collide_box(size_box, position);
	collide_box->set_layer_src(tools::to_ten("1"));
	collide_box->set_layer_dst(tools::to_ten("0"));
	collide_box->set_on_collide([&](double damage,BuffManager::BuffList list) {
		deliver_buff(list);
		cause_damage(damage);
		});

}

PlayerClaude::~PlayerClaude()
{
	collide_box->make_invalid();
}