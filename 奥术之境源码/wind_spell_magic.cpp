#include "wind_spell_magic.h"

WindSpellMagic::WindSpellMagic()
{
	consumption = ConfigManager::instance()->wind_spell_template.consumption;
	cd = ConfigManager::instance()->wind_spell_template.cd;
	multiplier = ConfigManager::instance()->wind_spell_template.multiplier;
	radius = ConfigManager::instance()->wind_spell_template.radius;
	speed = ConfigManager::instance()->wind_spell_template.speed;

	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_magic = tex_pool.find(ResID::Tex_MagicWindSpell)->second;

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

	is_self = true;

	buff_manager.set_buff(BuffName::SpeedUp);
}

WindSpellMagic::~WindSpellMagic()
{
}

void WindSpellMagic::release(double attack)
{
	Magic::release(attack);
}