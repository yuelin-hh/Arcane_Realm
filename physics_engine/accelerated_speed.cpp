#include "accelerated_speed.h"
#include<cmath>

AcceleratedSpeed::AcceleratedSpeed()
{
}

AcceleratedSpeed::AcceleratedSpeed(double x, double y) :x(x), y(y)
{
}


AcceleratedSpeed::~AcceleratedSpeed()
{
}

AcceleratedSpeed AcceleratedSpeed::operator+(const AcceleratedSpeed& a) const
{
	return AcceleratedSpeed(x + a.x, y + a.y);
}


void AcceleratedSpeed::operator+=(const AcceleratedSpeed& a)
{
	x += a.x, y += a.y;
}


Velocity AcceleratedSpeed::operator*(const double& num) const
{
	return Velocity(x * num, y * num);
}

void AcceleratedSpeed::operator*=(double num)
{
	x *= num, y *= num;
}

bool AcceleratedSpeed::operator==(const AcceleratedSpeed& a) const
{
	return x == a.x && y == a.y;
}

double AcceleratedSpeed::mgt()
{
	return sqrt(x * x + y * y);
}

void AcceleratedSpeed::clear()
{
	x = 0;
	y = 0;
}