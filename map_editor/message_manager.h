#pragma once
#include "manager.h"
#include "topic.h"

#include <unordered_map>
#include <string>

class MessageManager: public Manager<MessageManager>
{
	friend class Manager<MessageManager>;
protected:
	MessageManager();
	~MessageManager();
public:
	void create_topic(const std::string& name, const int& max_size = 0, const bool& is_single = false)
	{
		topic_map[name] = Topic(max_size);
		if (is_single) topic_map[name].set_single();
	}

	void send_message(const std::string& name, const std::string& value)
	{
		std::wcout << L"Send" << std::endl;
		if (topic_map.find(name) != topic_map.end())
		{
			topic_map[name].send_message(value);
		}
	}

	std::string read_message(const std::string& name)
	{
		if (topic_map.find(name) != topic_map.end())
		{
			return topic_map[name].read_message();
		}
		return "";
	}
private:
	std::unordered_map<std::string, Topic> topic_map = {};
};

MessageManager::MessageManager()
{
}

MessageManager::~MessageManager()
{
}