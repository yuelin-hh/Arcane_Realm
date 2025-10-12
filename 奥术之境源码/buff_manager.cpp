#include "buff_manager.h"

BuffManager::BuffManager()
{
}

BuffManager::~BuffManager()
{
	for (Buff* buff : buff_list)
		delete buff;
	buff_list.clear();
}

void BuffManager::on_update(double delta)
{
	for (Buff* buff : buff_list)
	{
		buff->on_update(delta);
		buff->set_position(position);
	}
	remove_invalid_buff();
}

void BuffManager::on_render(SDL_Renderer* renderer)
{
	for (Buff* buff : buff_list)
	{
		buff->on_render(renderer);
	}
}

void BuffManager::set_buff_list(BuffList list)
{
	buff_list = list;
}

void BuffManager::set_buff(BuffName name)
{
	Buff* buff;
	switch (name)
	{
	case Burn:
		buff = new BurnBuff();
		break;
	case Recover:
		buff = new RecoverBuff();
		break;
	case SpeedUp:
		buff = new SpeedUpBuff();
		break;
	default:
		break;
	}
	buff_list.push_back(buff);
}

void BuffManager::deliver_buff(const BuffList& list)
{
	bool flag;
	for (Buff* buff : list)
	{
		flag = true;
		for (Buff* buff_have : buff_list)
		{
			if (buff->name == buff_have->name)
			{
				buff->reset();
				flag = false;
				break;
			}
		}
		if (flag)
		{
			set_buff(buff->name);
		}
	}
}

void BuffManager::set_position(Vector2 pos)
{
	position = pos;
}

void BuffManager::remove_invalid_buff()
{
	buff_list.erase(std::remove_if(buff_list.begin(), buff_list.end(),
		[](const Buff* buff)
		{
			bool deletable = buff->can_remove();
			if (deletable) delete buff;
			return deletable;
		}), buff_list.end());
}