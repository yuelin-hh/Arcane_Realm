#pragma once

#include "manager.h"

#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <unordered_map>

enum class ResID
{
	Tex_Map,

	Tex_LockUI,
	Tex_MagicUI,
	Tex_LineUI,
	Tex_ButtonUI,
	Tex_SelectButtonUI,
	Tex_PlayerSelectUI,
	Tex_MagicSelectUI,

	Tex_ClaudeIdle,
	Tex_ClaudeRun,
	Tex_ClaudeWand,
	Tex_ClaudePhoto,

	Tex_SpawnEnemy,
	Tex_Slime,
	Tex_SlimeSketch,
	Tex_Deadman,
	Tex_DeadmanSketch,
	Tex_Gunner,
	Tex_GunnerSketch,

	Tex_BulletClaudeNormalAttack,
	Tex_BulletFireball,
	Tex_BulletLighting,
	Tex_BulletStrike,
	Tex_BulletExplod,
	Tex_BulletLava,


	Tex_EnemyBullet,

	Tex_MagicFireball,
	Tex_MagicBurningSpell,
	Tex_MagicMinorHeslingSpell,
	Tex_MagicLightingStrike,
	Tex_MagicWindSpell,
	Tex_MagicLavaVortex,
	Tex_MagicZeusFury,

	Tex_BuffBurnEffect,
	Tex_BuffRecoverEffect,
	Tex_BuffSpeedUpEffect,

	Tex_StatusBar,
	Tex_AttributeIcon,

	Tex_MainMenuWait,
	Tex_MainMenuChoose,
	Tex_SelectScene,

	Font_Main
};

class ResourcesManager : public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;
protected:
	ResourcesManager();
	~ResourcesManager();

public:
	typedef std::unordered_map<ResID, TTF_Font*> FontPool;
	typedef std::unordered_map<ResID, Mix_Chunk*> SoundPool;
	typedef std::unordered_map<ResID, Mix_Music*> MusicPool;
	typedef std::unordered_map<ResID, SDL_Texture*> TexturePool;

	bool load_from_file(SDL_Renderer* renderer)
	{
		texture_pool[ResID::Tex_Map] = IMG_LoadTexture(renderer, "resources/map.png");

		texture_pool[ResID::Tex_LockUI] = IMG_LoadTexture(renderer, "resources/lock_ui.png");
		texture_pool[ResID::Tex_MagicUI] = IMG_LoadTexture(renderer, "resources/magic_ui.png");
		texture_pool[ResID::Tex_LineUI] = IMG_LoadTexture(renderer, "resources/line_ui.png");
		texture_pool[ResID::Tex_ButtonUI] = IMG_LoadTexture(renderer, "resources/button_ui.png");
		texture_pool[ResID::Tex_SelectButtonUI] = IMG_LoadTexture(renderer, "resources/select_scene_button_ui.png");
		texture_pool[ResID::Tex_PlayerSelectUI] = IMG_LoadTexture(renderer, "resources/player_select_ui.png");
		texture_pool[ResID::Tex_MagicSelectUI] = IMG_LoadTexture(renderer, "resources/magic_select_ui.png");

		texture_pool[ResID::Tex_ClaudeIdle] = IMG_LoadTexture(renderer, "resources/Claude_idle.png");
		texture_pool[ResID::Tex_ClaudeRun] = IMG_LoadTexture(renderer, "resources/Claude_run.png");
		texture_pool[ResID::Tex_ClaudeWand] = IMG_LoadTexture(renderer, "resources/Claude_wand.png");
		texture_pool[ResID::Tex_ClaudePhoto] = IMG_LoadTexture(renderer, "resources/Claude_photo.png");

		texture_pool[ResID::Tex_SpawnEnemy] = IMG_LoadTexture(renderer, "resources/spawn_enemy.png");
		texture_pool[ResID::Tex_Slime] = IMG_LoadTexture(renderer, "resources/slime.png");
		texture_pool[ResID::Tex_SlimeSketch] = IMG_LoadTexture(renderer, "resources/slime_sketch.png");
		texture_pool[ResID::Tex_Deadman] = IMG_LoadTexture(renderer, "resources/deadman.png");
		texture_pool[ResID::Tex_DeadmanSketch] = IMG_LoadTexture(renderer, "resources/deadman_sketch.png");
		texture_pool[ResID::Tex_Gunner] = IMG_LoadTexture(renderer, "resources/gunner.png");
		texture_pool[ResID::Tex_GunnerSketch] = IMG_LoadTexture(renderer, "resources/gunner_sketch.png");

		texture_pool[ResID::Tex_BulletClaudeNormalAttack] = IMG_LoadTexture(renderer, "resources/Claude_normal_attack.png");
		texture_pool[ResID::Tex_BulletFireball] = IMG_LoadTexture(renderer, "resources/fireball.png");
		texture_pool[ResID::Tex_BulletLighting] = IMG_LoadTexture(renderer, "resources/lighting.png");
		texture_pool[ResID::Tex_BulletStrike] = IMG_LoadTexture(renderer, "resources/strike.png");
		texture_pool[ResID::Tex_BulletExplod] = IMG_LoadTexture(renderer, "resources/explod.png");
		texture_pool[ResID::Tex_BulletLava] = IMG_LoadTexture(renderer, "resources/lava.png");

		texture_pool[ResID::Tex_EnemyBullet] = IMG_LoadTexture(renderer, "resources/enemy_bullet.png");

		texture_pool[ResID::Tex_StatusBar] = IMG_LoadTexture(renderer, "resources/status_bar.png");
		texture_pool[ResID::Tex_AttributeIcon] = IMG_LoadTexture(renderer, "resources/attribute_icon.png");

		texture_pool[ResID::Tex_MagicFireball] = IMG_LoadTexture(renderer, "resources/magic_fireball.png");
		texture_pool[ResID::Tex_MagicBurningSpell] = IMG_LoadTexture(renderer, "resources/magic_burning_spell.png");
		texture_pool[ResID::Tex_MagicMinorHeslingSpell] = IMG_LoadTexture(renderer, "resources/magic_minor_healing_spell.png");
		texture_pool[ResID::Tex_MagicLightingStrike] = IMG_LoadTexture(renderer, "resources/magic_lighting_strike.png");
		texture_pool[ResID::Tex_MagicWindSpell] = IMG_LoadTexture(renderer, "resources/magic_wind_spell.png");
		texture_pool[ResID::Tex_MagicLavaVortex] = IMG_LoadTexture(renderer, "resources/magic_lava_vortex.png");
		texture_pool[ResID::Tex_MagicZeusFury] = IMG_LoadTexture(renderer, "resources/magic_zeus_fury.png");

		texture_pool[ResID::Tex_BuffBurnEffect] = IMG_LoadTexture(renderer, "resources/burn_effect.png");
		texture_pool[ResID::Tex_BuffRecoverEffect] = IMG_LoadTexture(renderer, "resources/recover_effect.png");
		texture_pool[ResID::Tex_BuffSpeedUpEffect] = IMG_LoadTexture(renderer, "resources/speed_up_effect.png");

		texture_pool[ResID::Tex_MainMenuWait] = IMG_LoadTexture(renderer, "resources/main_menu_wait.png");
		texture_pool[ResID::Tex_MainMenuChoose] = IMG_LoadTexture(renderer, "resources/main_menu_choose.png");
		texture_pool[ResID::Tex_SelectScene] = IMG_LoadTexture(renderer, "resources/select_scene.png");

		for (const auto& pair : texture_pool)
			if (!pair.second) return false;

		font_pool[ResID::Font_Main] = TTF_OpenFont("resources/ipix.ttf", 12);

		for (const auto& pair : font_pool)
			if (!pair.second) return false;

		return true;
	}

	const FontPool& get_font_pool()
	{
		return font_pool;
	}

	const SoundPool& get_sound_pool()
	{
		return sound_pool;
	}

	const MusicPool& get_music_pool()
	{
		return music_pool;
	}

	const TexturePool& get_texture_pool()
	{
		return texture_pool;
	}

private:
	FontPool font_pool;
	SoundPool sound_pool;
	MusicPool music_pool;
	TexturePool texture_pool;
};