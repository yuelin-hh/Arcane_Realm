#include "burning_spell_magic.h"

BurningSpellMagic::BurningSpellMagic()
{
	consumption = ConfigManager::instance()->burning_spell_template.consumption;
	cd = ConfigManager::instance()->burning_spell_template.cd;
	multiplier = ConfigManager::instance()->burning_spell_template.multiplier;
	radius = ConfigManager::instance()->burning_spell_template.radius;
	speed = ConfigManager::instance()->burning_spell_template.speed;

	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_magic = tex_pool.find(ResID::Tex_MagicBurningSpell)->second;

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

	buff_manager.set_buff(BuffName::Burn);

	need_target = true;
}

BurningSpellMagic::~BurningSpellMagic()
{
}

void BurningSpellMagic::release(double attack)
{
	BulletManager::instance()->fire_bullet(BulletName::Fireball, target, attack * multiplier, buff_manager.get_buff_list());
	Magic::release(attack);
}