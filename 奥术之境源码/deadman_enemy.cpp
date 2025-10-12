#include "deadman_enemy.h"

DeadmanEnemy::DeadmanEnemy()
{
	static const ResourcesManager::TexturePool& texture_pool
		= ResourcesManager::instance()->get_texture_pool();
	static SDL_Texture* tex_enemy = texture_pool.find(ResID::Tex_Deadman)->second;
	static SDL_Texture* tex_enemy_sketch = texture_pool.find(ResID::Tex_DeadmanSketch)->second;
	static ConfigManager::EnemyTemplate& enemy_template = ConfigManager::instance()->deadman_template;

	anim_idle_left.set_loop(true);
	anim_idle_left.set_interval(0.3);
	anim_idle_left.set_frame_data(tex_enemy, 1, 1, { 0 });
	anim_idle_right.set_loop(true);
	anim_idle_right.set_interval(0.3);
	anim_idle_right.set_frame_data(tex_enemy, 1, 1, { 0 });

	anim_move_left.set_loop(true);
	anim_move_left.set_interval(0.1);
	anim_move_left.set_frame_data(tex_enemy, 1, 1, { 0 });
	anim_move_right.set_loop(true);
	anim_move_right.set_interval(0.1);
	anim_move_right.set_frame_data(tex_enemy, 1, 1, { 0 });

	anim_attack_left.set_loop(true);
	anim_attack_left.set_interval(0.1);
	anim_attack_left.set_frame_data(tex_enemy, 1, 1, { 0 });
	anim_attack_right.set_loop(true);
	anim_attack_right.set_interval(0.1);
	anim_attack_right.set_frame_data(tex_enemy, 1, 1, { 0 });

	anim_idle_left_sketch.set_loop(true);
	anim_idle_left_sketch.set_interval(0.3);
	anim_idle_left_sketch.set_frame_data(tex_enemy_sketch, 1, 1, { 0 });
	anim_idle_right_sketch.set_loop(true);
	anim_idle_right_sketch.set_interval(0.3);
	anim_idle_right_sketch.set_frame_data(tex_enemy_sketch, 1, 1, { 0 });

	anim_move_left_sketch.set_loop(true);
	anim_move_left_sketch.set_interval(0.1);
	anim_move_left_sketch.set_frame_data(tex_enemy_sketch, 1, 1, { 0 });
	anim_move_right_sketch.set_loop(true);
	anim_move_right_sketch.set_interval(0.1);
	anim_move_right_sketch.set_frame_data(tex_enemy_sketch, 1, 1, { 0 });

	anim_attack_left_sketch.set_loop(true);
	anim_attack_left_sketch.set_interval(0.1);
	anim_attack_left_sketch.set_frame_data(tex_enemy_sketch, 1, 1, { 0 });
	anim_attack_right_sketch.set_loop(true);
	anim_attack_right_sketch.set_interval(0.1);
	anim_attack_right_sketch.set_frame_data(tex_enemy_sketch, 1, 1, { 0 });


	hp_max = enemy_template.hp;
	speed = enemy_template.speed;
	damage = enemy_template.damage;
	attack_radius = enemy_template.attack_radius;
	view_radius = enemy_template.view_radius;
	hp = hp_max;

	size.x = 32, size.y = 64;

	Vector2 size_box;
	size_box.x = 24;
	size_box.y = 54;
	anim_current = &anim_idle_left;
	anim_current_sketch = &anim_idle_left_sketch;

	collide_box = CollisionManager::instance()->create_collide_box(size_box, position);
	collide_box->set_layer_src(tools::to_ten("100"));
	collide_box->set_layer_dst(tools::to_ten("10"));
	collide_box->set_enable(false);
	collide_box->set_on_collide([&](double damage, BuffManager::BuffList list) {
		deliver_buff(list);
		cause_damage(damage);
		});
}

DeadmanEnemy::~DeadmanEnemy()
{
	
}