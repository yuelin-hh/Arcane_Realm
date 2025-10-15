#pragma once
#include "vector2.h"

class Velocity
{
public:
	Velocity();
	Velocity(double x, double y);
	Velocity(Vector2 direction, double mgt);
	~Velocity();

	Velocity operator+(const Velocity& F) const;

	void operator+=(const Velocity& F);


	Vector2 operator*(const double& num) const;

	void operator*=(double num);

	bool operator==(const Velocity& F) const;

	Vector2 direction();

	double mgt();

	double get_speed_in_direction(Vector2& direction);

	double x = 0;
	double y = 0;
};