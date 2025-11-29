#pragma once
#include "message.h"
#include <list>
class Topic
{
public:
	Topic() {}
	Topic(int max_size) : max_size(max_size) { message_list.resize(max_size); }
	~Topic() { message_list.clear(); }

	//设定消息是否阅读后删除
	void set_single()
	{
		is_single = true;
	}

	void send_message(std::string value)
	{
		message_list.push_back(Message(value));
		if (max_size > 0 && message_list.size() > max_size)
			message_list.pop_front();
	}

	std::string read_message()
	{
		if (message_list.empty()) return "";

		if (is_single)
		{
			std::string value = message_list.front().value;
			message_list.pop_front();
			return value;
		}
		return message_list.back().value;
	}

private:
	bool is_single = false;
	int max_size = 0;
	std::list<Message> message_list;
};