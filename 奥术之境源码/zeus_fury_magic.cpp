#include "zeus_fury_magic.h"

ZeusFuryMagic::ZeusFuryMagic()
{
	consumption = ConfigManager::instance()->zeus_fury_template.consumption;
	cd = ConfigManager::instance()->zeus_fury_template.cd;
	multiplier = ConfigManager::instance()->zeus_fury_template.multiplier;
	radius = ConfigManager::instance()->zeus_fury_template.radius;
	speed = ConfigManager::instance()->zeus_fury_template.speed;

	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_magic = tex_pool.find(ResID::Tex_MagicZeusFury)->second;


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

	need_start_position = true;
	need_target = true;
}

ZeusFuryMagic::~ZeusFuryMagic()
{
}

void ZeusFuryMagic::release(double attack)
{
	BulletManager::instance()->fire_bullet(BulletName::Lighting, target, 0, start_position, attack * multiplier, {});
	Magic::release(attack);
}