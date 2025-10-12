#include "burn_buff.h"

BurnBuff::BurnBuff()
{
	duration = ConfigManager::instance()->burn_template.duration;
	damage = ConfigManager::instance()->burn_template.damage;

	const ResourcesManager::TexturePool& tex_pool
		= ResourcesManager::instance()->get_texture_pool();

	SDL_Texture* tex_effect = tex_pool.find(ResID::Tex_BuffBurnEffect)->second;

	anim_effect.set_loop(true);
	anim_effect.set_interval(0.2);
	anim_effect.set_frame_data(tex_effect, 2, 2, { 0,1,2,3 });

	timer.set_one_shot(true);
	timer.set_wait_time(duration);
	timer.restart();
	timer.set_on_timeout([&]() {
		Buff::make_invalid();
		});

	name = BuffName::Burn;
	size.x = 32, size.y = 32;
}

BurnBuff::~BurnBuff()
{
}