#include "velocity.h"
#include<cmath>

Velocity::Velocity()
{
}

Velocity::Velocity(double x, double y) :x(x), y(y)
{
}

Velocity::Velocity(Vector2 direction, double mgt)
{
	x = direction.normalize().x * mgt;
	y = direction.normalize().y * mgt;
}

Velocity::~Velocity()
{
}

Velocity Velocity::operator+(const Velocity& F) const
{
	return Velocity(x + F.x, y + F.y);
}

void Velocity::operator+=(const Velocity& F)
{
	x += F.x, y += F.y;
}

Vector2 Velocity::operator*(const double& num) const
{
	return Vector2(x * num * 32, y * num * 32);
}

void Velocity::operator*=(double num)
{
	x *= num, y *= num;
}

bool Velocity::operator==(const Velocity& F) const
{
	return x == F.x && y == F.y;
}

Vector2 Velocity::direction()
{
	return Vector2(x, y);
}

double Velocity::mgt()
{
	return sqrt(x * x + y * y);
}

double Velocity::get_speed_in_direction(Vector2& direction)
{
	double radian = std::atan2(direction.y, direction.x);
	return x * cos(radian) + y * sin(radian);
}