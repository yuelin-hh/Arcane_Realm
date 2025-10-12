#include "lava_vortex_magic.h"

LavaVortexMagic::LavaVortexMagic()
{
	consumption = ConfigManager::instance()->lava_vortex_template.consumption;
	cd = ConfigManager::instance()->lava_vortex_template.cd;
	multiplier = ConfigManager::instance()->lava_vortex_template.multiplier;
	radius = ConfigManager::instance()->lava_vortex_template.radius;
	speed = ConfigManager::instance()->lava_vortex_template.speed;
	range = ConfigManager::instance()->lava_vortex_template.range;

	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_magic = tex_pool.find(ResID::Tex_MagicLavaVortex)->second;

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

	need_mouse_position = true;
	need_player_position = true;
}

LavaVortexMagic::~LavaVortexMagic()
{
}

void LavaVortexMagic::release(double attack)
{
	BulletManager::instance()->fire_bullet(BulletName::LavaVortex, attack * multiplier, range, mouse_position, {}, 2);
	Magic::release(attack);
}