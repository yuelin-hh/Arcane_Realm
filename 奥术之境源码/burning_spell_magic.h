#pragma once

#include "magic.h"

class BurningSpellMagic :public Magic
{
public:
	BurningSpellMagic();
	~BurningSpellMagic();

	void release(double attack);

private:

};