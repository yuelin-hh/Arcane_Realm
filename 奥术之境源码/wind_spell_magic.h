#pragma once
#include "magic.h"

class WindSpellMagic: public Magic
{
public:
	WindSpellMagic();
	~WindSpellMagic();

private:
	void release(double attack);
};