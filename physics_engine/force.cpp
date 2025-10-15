#include "force.h"
#include<cmath>

Force::Force()
{
}

Force::Force(double x,double y):x(x),y(y)
{
}

Force::Force(Vector2 direction, double mgt)
{
	x = direction.normalize().x * mgt;
	y = direction.normalize().y * mgt;
}

Force::~Force()
{
}

Force Force::operator+(const Force& F) const
{
	return Force(x + F.x, y + F.y);
}

void Force::operator+=(const Force& F)
{
	x += F.x, y += F.y;
}

Force Force::operator*(const double& num) const
{
	return Force(x * num, y * num);
}

void Force::operator*=(double num)
{
	x *= num, y *= num;
}

AcceleratedSpeed Force::operator/(double m) const
{
	return AcceleratedSpeed(x / m, y / m);
}

bool Force::operator==(const Force& F) const
{
	return x == F.x && y == F.y;
}

Vector2 Force::direction()
{
	return Vector2(x, y);
}

double Force::mgt()
{
	return sqrt(x * x + y * y);
}

void Force::clear()
{
	x = 0;
	y = 0;
}