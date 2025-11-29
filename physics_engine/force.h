#pragma once
#include "accelerated_speed.h"

class Force
{
public:
	Force();
	Force(double x,double y);
	Force(Vector2 direction, double mgt);
	Force(Vector2 direction);
	~Force();

	Force operator+(const Force& F) const;

	void operator+=(const Force& F);

	Force operator*(const double& num) const;

	void operator*=(double num);

	AcceleratedSpeed operator/(double m) const;

	bool operator==(const Force& F) const;

	Vector2 direction();

	double mgt();

	void clear();

	double x = 0;
	double y = 0;
};