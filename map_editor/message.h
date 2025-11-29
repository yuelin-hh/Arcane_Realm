#pragma once
#include <string>

class Message
{
public:
	Message(std::string value):value(value) {}
	Message(){}
	~Message(){}

	std::string value;
};