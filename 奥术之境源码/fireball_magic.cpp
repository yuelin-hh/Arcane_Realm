#include "fireball_magic.h"

FireballMagic::FireballMagic()
{
	consumption = ConfigManager::instance()->fireball_template.consumption;
	cd = ConfigManager::instance()->fireball_template.cd;
	multiplier = ConfigManager::instance()->fireball_template.multiplier;
	radius = ConfigManager::instance()->fireball_template.radius;
	speed = ConfigManager::instance()->fireball_template.speed;

	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_magic = tex_pool.find(ResID::Tex_MagicFireball)->second;


	anim_magic.set_loop(true);
	anim_magic.set_interval(0.3);
	anim_magic.set_scaling(0.5);
	anim_magic.set_frame_data(tex_magic, 2, 1, { 0 });

	anim_magic_cd.set_loop(false);
	anim_magic_cd.set_interval(cd);
	anim_magic_cd.set_scaling(0.5);
	anim_magic_cd.set_frame_data(tex_magic, 2, 1, { 1 });

	anim_magic_current = &anim_magic;
	size.x = 160, size.y = 256;

	need_velocity = true;
	need_start_position = true;
	need_player_position = true;
}

FireballMagic::~FireballMagic()
{
}

void FireballMagic::release(double attack)
{
	BulletManager::instance()->fire_bullet(BulletName::Fireball, velocity, speed, player_position, start_position,
		(radius - (start_position - player_position).length()), multiplier * attack, buff_manager.get_buff_list());
	Magic::release(attack);
}