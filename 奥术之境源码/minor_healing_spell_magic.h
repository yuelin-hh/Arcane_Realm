#pragma once

#include "magic.h"

class MinorHealingSpellMagic:public Magic
{
public:
	MinorHealingSpellMagic();
	~MinorHealingSpellMagic();

	void release(double attack);
private:

};