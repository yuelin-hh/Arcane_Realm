#pragma once

#include "magic.h"

class FireballMagic:public Magic
{
public:
	FireballMagic();
	~FireballMagic();

	void release(double attack);
private:

};