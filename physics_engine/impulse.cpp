#include "impulse.h"
#include<cmath>

Impulse::Impulse()
{
}

Impulse::Impulse(double x, double y) :x(x), y(y)
{
}

Impulse::Impulse(Velocity v, double m)
{
	x = v.x * m;
	y = v.y * m;
}

Impulse::Impulse(Force F, double t)
{
	x = F.x * t;
	y = F.y * t;
}

Impulse::~Impulse()
{
}

Impulse Impulse::operator+(const Impulse& I) const
{
	return Impulse(x + I.x, y + I.y);
}

void Impulse::operator+=(const Impulse& I)
{
	x += I.x, y += I.y;
}

Impulse Impulse::operator*(const double& num) const
{
	return Impulse(x * num, y * num);
}

void Impulse::operator*=(double num)
{
	x *= num, y *= num;
}

Velocity Impulse::operator/(double m)
{
	return Velocity(x / m, y / m);
}

bool Impulse::operator==(const Impulse& I) const
{
	return x == I.x && y == I.y;
}

double Impulse::mgt()
{
	return sqrt(x * x + y * y);
}

void Impulse::clear()
{
	x = 0;
	y = 0;
}