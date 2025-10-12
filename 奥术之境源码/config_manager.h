#pragma once

#include "manager.h"

#include <SDL.h>
#include <string>
#include <cJSON.h>
#include <fstream>
#include <sstream>
#include <iostream>

class ConfigManager : public Manager<ConfigManager>
{
	friend class Manager<ConfigManager>;

protected:
	ConfigManager();
	~ConfigManager();
public:
	struct BasicTemplate
	{
		std::string window_title = u8"°ÂÊõÖ®¾³";
		int window_width = 1280;
		int window_height = 720;
	};

	struct PlayerTemplate
	{
		double hp = 500;
		double speed = 3;
		double attack = 1;
		double attack_multiplier = 10;
		double attack_interval = 0.5;
		double attack_radius = 320;
		double bullet_speed = 300;
		double mp = 10;
		double mp_recover = 0.5;
	};

	struct EnemyTemplate
	{
		double hp = 100;
		double speed = 1;
		double damage = 1;
		double attack_radius = 5;
		double view_radius = 200;
		double attack_interval = 2;
	};

	struct MagicTemplate
	{
		double consumption = 2;
		double cd = 1;
		double multiplier = 20;
		double radius = 500;
		double speed = 400;
		double range = 0;
	};

	struct BuffTemplate
	{
		double duration=1;
		double damage = 0;
		double recover = 0;
		double speed_up = 0;
	};

public:
	bool running = true;

	BasicTemplate basic_template;

	PlayerTemplate claude_template;

	EnemyTemplate slime_template;
	EnemyTemplate big_slime_template;
	EnemyTemplate deadman_template;
	EnemyTemplate gunner_template;

	MagicTemplate fireball_template;
	MagicTemplate burning_spell_template;
	MagicTemplate minor_healing_spell_template;
	MagicTemplate lighting_strike_template;
	MagicTemplate wind_spell_template;
	MagicTemplate lava_vortex_template;
	MagicTemplate zeus_fury_template;

	BuffTemplate burn_template;
	BuffTemplate recover_template;
	BuffTemplate speed_up_template;
public:
	bool load_game_config(const std::string& path);

private:
	void parse_basic_template(BasicTemplate& tpl, cJSON* json_root);

	void parse_player_template(PlayerTemplate& tpl, cJSON* json_root);

	void parse_enemy_template(EnemyTemplate& tpl, cJSON* json_root);

	void parse_magic_template(MagicTemplate& tpl, cJSON* json_root);

	void parse_buff_template(BuffTemplate& tpl, cJSON* json_root);
};