#include "magic_manager.h"

MagicManager::MagicManager()
{

}

MagicManager::~MagicManager()
{
	for (Magic* magic : magic_list)
		delete magic;
	magic_list.clear();
}

void MagicManager::on_enter(int* magic_list)
{
	int i = 0;
	Magic* magic;
	while (magic_list[i])
	{
		switch (magic_list[i])
		{
		case 1:
			magic = new BurningSpellMagic();
			break;
		case 2:
			magic = new WindSpellMagic();
			break;
		case 3:
			magic = new FireballMagic();
			break;
		case 4:
			magic = new MinorHealingSpellMagic();
			break;
		case 5:
			magic = new LightingStrikeMagic();
			break;
		case 6:
			magic = new LavaVortexMagic();
			break;
		case 7:
			magic = new ZeusFuryMagic();
			break;
		default:
			break;
		}

		this->magic_list.push_back(magic);

		i++;
	}
	set_position_idle();
	magic_amount = this->magic_list.size();
}

void MagicManager::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_1:
			if (magic_number == 1 || magic_amount < 1)
			{
				cancel_choose();
			}
			else
			{
				last_magic_number = magic_number;
				magic_number = 1;
			}
			break;
		case SDLK_2:
			if (magic_number == 2 || magic_amount < 2)
			{
				cancel_choose();
			}
			else
			{
				last_magic_number = magic_number;
				magic_number = 2;
			}
			break;
		case SDLK_3:
			if (magic_number == 3 || magic_amount < 3)
			{
				cancel_choose();
			}
			else
			{
				last_magic_number = magic_number;
				magic_number = 3;
			}
			break;
		case SDLK_4:
			if (magic_number == 4 || magic_amount < 4)
			{
				cancel_choose();
			}
			else
			{
				last_magic_number = magic_number;
				magic_number = 4;
			}
			break;
		case SDLK_5:
			if (magic_number == 5 || magic_amount < 5)
			{
				cancel_choose();
			}
			else
			{
				last_magic_number = magic_number;
				magic_number = 5;
			}
			break;
		case SDLK_6:
			if (magic_number == 6 || magic_amount < 6)
			{
				cancel_choose();
			}
			else
			{
				last_magic_number = magic_number;
				magic_number = 6;
			}
			break;
		case SDLK_7:
			if (magic_number == 6 || magic_amount < 6)
			{
				cancel_choose();
			}
			else
			{
				last_magic_number = magic_number;
				magic_number = 6;
			}
			break;
		default:
			break;
		}
	case SDL_MOUSEWHEEL:
		handleMouseWheelAdvanced(event.wheel);
		break;
	default:
		break;
	}
}

void MagicManager::on_update(double delta)
{
	for (Magic* magic : magic_list)
	{
		magic->check_mp_sufficien(current_mp);
		if (magic->need_player_position)
			magic->set_player_position(player_position);
		magic->on_update(delta);
	}

	if (current_magic == nullptr)
		set_position_idle();
	else
		set_position_choose();
}

void MagicManager::on_render(SDL_Renderer* renderer)
{
	for (Magic* magic : magic_list)
		magic->on_render(renderer);
	if (current_magic != nullptr)
		current_magic->on_render_chose(renderer);
}

void MagicManager::cancel_choose()
{
	last_magic_number = magic_number;
	magic_number = 0;
}

void MagicManager::set_current_mp(double mp)
{
	current_mp = mp;
}

void MagicManager::get_player_position(Vector2 pos)
{
	player_position = pos;
}

void MagicManager::get_last_magic()
{
	int a = magic_number;
	magic_number = last_magic_number;
	last_magic_number = a;
}

void MagicManager::set_position_idle()
{
	int i = 0;

	for (Magic* magic : magic_list)
	{
		magic->set_position(40 + i * 80, 624);
		i++;
	}
}

void MagicManager::set_position_choose()
{
	int i = 0;
	int j = 0;
	bool is_choose_magic = false;

	for (Magic* magic : magic_list)
	{
		if (magic == current_magic)
		{
			is_choose_magic = true;
			j = i;
		}
		i++;
	}
	i = 0;

	for (Magic* magic : magic_list)
	{
		if (i < j)
			magic->set_position(i * 80, 624);
		else if (i == j)
			magic->set_position(40 + i * 80, 624);
		else
			magic->set_position(80 + i * 80, 624);

		i++;
	}
}

void MagicManager::handleMouseWheelAdvanced(SDL_MouseWheelEvent wheel)
{
	float scrollY = (wheel.preciseY != 0.0f) ? wheel.preciseY : (float)wheel.y;
	totalRotation -= scrollY * 1.5;

	if (magic_number == 0)
	{
		totalRotation = 0;
	}
	else if (magic_number < magic_amount && totalRotation > 3)
	{
		last_magic_number = magic_number;
		magic_number++;
		totalRotation = 0;
	}
	else if (magic_number == magic_amount && totalRotation > 3)
	{
		last_magic_number = magic_number;
		magic_number = 1;
		totalRotation = 0;
	}
	else if (magic_number == 1 && totalRotation < -3)
	{
		last_magic_number = magic_number;
		magic_number = magic_amount;
		totalRotation = 0;
	}
	else if (magic_number > 1 && totalRotation < -3)
	{
		last_magic_number = magic_number;
		magic_number--;
		totalRotation = 0;
	}
}