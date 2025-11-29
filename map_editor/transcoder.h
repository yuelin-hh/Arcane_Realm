#pragma once
#include "message.h"

class Transcoder
{
public:
	Transcoder();
	~Transcoder();

	static std::string trans_int_message(const int& value)
	{
		return std::to_string(value);
	}

	static int read_int_message(const std::string value)
	{
		return std::stoi(value);
	}
private:

};

Transcoder::Transcoder()
{
}

Transcoder::~Transcoder()
{
}