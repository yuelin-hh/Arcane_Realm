#include "config_manager.h"

ConfigManager::ConfigManager()
{
}

ConfigManager::~ConfigManager()
{
}

bool ConfigManager::load_game_config(const std::string& path)
{
	std::ifstream file(path);
	if (!file.good())return false;

	std::stringstream str_stream;
	str_stream << file.rdbuf(); file.close();

	cJSON* json_root = cJSON_Parse(str_stream.str().c_str());
	if (!json_root || json_root->type != cJSON_Object) return false;

	cJSON* json_basic = cJSON_GetObjectItem(json_root, "basic");
	cJSON* json_player = cJSON_GetObjectItem(json_root, "player");
	cJSON* json_enemy = cJSON_GetObjectItem(json_root, "enemy");
	cJSON* json_magic = cJSON_GetObjectItem(json_root, "magic");
	cJSON* json_buff = cJSON_GetObjectItem(json_root, "buff");

	if (!json_basic || !json_player || !json_enemy || !json_magic || !json_buff
		|| json_basic->type != cJSON_Object
		|| json_player->type != cJSON_Object
		|| json_enemy->type != cJSON_Object
		|| json_magic->type != cJSON_Object
		|| json_buff->type != cJSON_Object)
	{
		cJSON_Delete(json_root);
		return false;
	}

	parse_basic_template(basic_template, json_basic);

	parse_player_template(claude_template, cJSON_GetObjectItem(json_player, "claude"));

	parse_enemy_template(slime_template, cJSON_GetObjectItem(json_enemy, "slime"));
	parse_enemy_template(big_slime_template, cJSON_GetObjectItem(json_enemy, "big_slime"));
	parse_enemy_template(deadman_template, cJSON_GetObjectItem(json_enemy, "deadman"));
	parse_enemy_template(gunner_template, cJSON_GetObjectItem(json_enemy, "gunner"));

	parse_magic_template(fireball_template, cJSON_GetObjectItem(json_magic, "fireball"));
	parse_magic_template(burning_spell_template, cJSON_GetObjectItem(json_magic, "burning_spell"));
	parse_magic_template(minor_healing_spell_template, cJSON_GetObjectItem(json_magic, "minor_healing_spell"));
	parse_magic_template(lighting_strike_template, cJSON_GetObjectItem(json_magic, "lighting_strike"));
	parse_magic_template(wind_spell_template, cJSON_GetObjectItem(json_magic, "wind_spell"));
	parse_magic_template(lava_vortex_template, cJSON_GetObjectItem(json_magic, "lava_vortex"));
	parse_magic_template(zeus_fury_template, cJSON_GetObjectItem(json_magic, "zeus_fury"));

	parse_buff_template(burn_template, cJSON_GetObjectItem(json_buff, "burn"));
	parse_buff_template(recover_template, cJSON_GetObjectItem(json_buff, "recover"));
	parse_buff_template(speed_up_template, cJSON_GetObjectItem(json_buff, "speed_up"));

	cJSON_Delete(json_root);
	return true;
}

void ConfigManager::parse_basic_template(BasicTemplate& tpl, cJSON* json_root)
{
	if (!json_root || json_root->type != cJSON_Object) return;

	cJSON* json_window_title = cJSON_GetObjectItem(json_root, "window_title");
	cJSON* json_window_width = cJSON_GetObjectItem(json_root, "window_width");
	cJSON* json_window_height = cJSON_GetObjectItem(json_root, "window_height");

	if (json_window_title && json_window_title->type == cJSON_String)
		tpl.window_title = json_window_title->valuestring;
	if (json_window_width && json_window_width->type == cJSON_Number)
		tpl.window_width = json_window_width->valueint;
	if (json_window_height && json_window_height->type == cJSON_Number)
		tpl.window_height = json_window_height->valueint;
}

void ConfigManager::parse_player_template(PlayerTemplate& tpl, cJSON* json_root)
{
	if (!json_root || json_root->type != cJSON_Object) return;

	cJSON* json_hp = cJSON_GetObjectItem(json_root, "hp");
	cJSON* json_speed = cJSON_GetObjectItem(json_root, "speed");
	cJSON* json_attack = cJSON_GetObjectItem(json_root, "attack");
	cJSON* json_attack_multiplier = cJSON_GetObjectItem(json_root, "attack_multiplier");
	cJSON* json_attack_interval = cJSON_GetObjectItem(json_root, "attack_interval");
	cJSON* json_attack_radius = cJSON_GetObjectItem(json_root, "attack_radius");
	cJSON* json_bullet_speed = cJSON_GetObjectItem(json_root, "bullet_speed");
	cJSON* json_mp = cJSON_GetObjectItem(json_root, "mp");
	cJSON* json_mp_recover = cJSON_GetObjectItem(json_root, "mp_recover");

	if (json_hp && json_hp->type == cJSON_Number)
		tpl.hp = json_hp->valuedouble;
	if (json_speed && json_speed->type == cJSON_Number)
		tpl.speed = json_speed->valuedouble;
	if (json_attack && json_attack->type == cJSON_Number)
		tpl.attack = json_attack->valuedouble;
	if (json_attack_multiplier && json_attack_multiplier->type == cJSON_Number)
		tpl.attack_multiplier = json_attack_multiplier->valuedouble;
	if (json_attack_interval && json_attack_interval->type == cJSON_Number)
		tpl.attack_interval = json_attack_interval->valuedouble;
	if (json_attack_radius && json_attack_radius->type == cJSON_Number)
		tpl.attack_radius = json_attack_radius->valuedouble;
	if (json_bullet_speed && json_bullet_speed->type == cJSON_Number)
		tpl.bullet_speed = json_bullet_speed->valuedouble;
	if (json_mp && json_mp->type == cJSON_Number)
		tpl.mp = json_mp->valuedouble;
	if (json_mp_recover && json_mp_recover->type == cJSON_Number)
		tpl.mp_recover = json_mp_recover->valuedouble;
}

void ConfigManager::parse_enemy_template(EnemyTemplate& tpl, cJSON* json_root)
{
	if (!json_root || json_root->type != cJSON_Object) return;

	cJSON* json_hp = cJSON_GetObjectItem(json_root, "hp");
	cJSON* json_speed = cJSON_GetObjectItem(json_root, "speed");
	cJSON* json_damage = cJSON_GetObjectItem(json_root, "damage");
	cJSON* json_attack_radius = cJSON_GetObjectItem(json_root, "attack_radius");
	cJSON* json_view_radius = cJSON_GetObjectItem(json_root, "view_radius");
	cJSON* json_attack_interval = cJSON_GetObjectItem(json_root, "attack_interval");

	if (json_hp && json_hp->type == cJSON_Number)
		tpl.hp = json_hp->valuedouble;
	if (json_speed && json_speed->type == cJSON_Number)
		tpl.speed = json_speed->valuedouble;
	if (json_damage && json_damage->type == cJSON_Number)
		tpl.damage = json_damage->valuedouble;
	if (json_attack_radius && json_attack_radius->type == cJSON_Number)
		tpl.attack_radius = json_attack_radius->valuedouble;
	if (json_view_radius && json_view_radius->type == cJSON_Number)
		tpl.view_radius = json_view_radius->valuedouble;
	if (json_attack_interval && json_attack_interval->type == cJSON_Number)
		tpl.attack_interval = json_attack_interval->valuedouble;
}

void ConfigManager::parse_magic_template(MagicTemplate& tpl, cJSON* json_root)
{
	if (!json_root || json_root->type != cJSON_Object) return;

	cJSON* json_consumption = cJSON_GetObjectItem(json_root, "consumption");
	cJSON* json_cd = cJSON_GetObjectItem(json_root, "cd");
	cJSON* json_multiplier = cJSON_GetObjectItem(json_root, "multiplier");
	cJSON* json_radius = cJSON_GetObjectItem(json_root, "radius");
	cJSON* json_speed = cJSON_GetObjectItem(json_root, "speed");
	cJSON* json_range = cJSON_GetObjectItem(json_root, "range");

	if (json_consumption && json_consumption->type == cJSON_Number)
		tpl.consumption = json_consumption->valuedouble;
	if (json_cd && json_cd->type == cJSON_Number)
		tpl.cd = json_cd->valuedouble;
	if (json_multiplier && json_multiplier->type == cJSON_Number)
		tpl.multiplier = json_multiplier->valuedouble;
	if (json_radius && json_radius->type == cJSON_Number)
		tpl.radius = json_radius->valuedouble;
	if (json_speed && json_speed->type == cJSON_Number)
		tpl.speed = json_speed->valuedouble;
	if (json_range && json_range->type == cJSON_Number)
		tpl.range = json_range->valuedouble;
}

void ConfigManager::parse_buff_template(BuffTemplate& tpl, cJSON* json_root)
{
	if (!json_root || json_root->type != cJSON_Object) return;

	cJSON* json_duration = cJSON_GetObjectItem(json_root, "duration");
	cJSON* json_damage = cJSON_GetObjectItem(json_root, "damage");
	cJSON* json_recover = cJSON_GetObjectItem(json_root, "recover");
	cJSON* json_speed_up = cJSON_GetObjectItem(json_root, "speed_up");

	if (json_duration && json_duration->type == cJSON_Number)
		tpl.duration = json_duration->valuedouble;
	if (json_damage && json_damage->type == cJSON_Number)
		tpl.damage = json_damage->valuedouble;
	if (json_recover && json_recover->type == cJSON_Number)
		tpl.recover = json_recover->valuedouble;
	if (json_speed_up && json_speed_up->type == cJSON_Number)
		tpl.speed_up = json_speed_up->valuedouble;
}