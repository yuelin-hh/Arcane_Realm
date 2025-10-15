#pragma once

#include "velocity.h"

class AcceleratedSpeed
{
public:
	AcceleratedSpeed();
	AcceleratedSpeed(double x, double y);

	~AcceleratedSpeed();

	AcceleratedSpeed operator+(const AcceleratedSpeed& a) const;

	void operator+=(const AcceleratedSpeed& a);

	Velocity operator*(const double& num) const;

	void operator*=(double num);

	bool operator==(const AcceleratedSpeed& a) const;

	double mgt();

	void clear();

	double x = 0;
	double y = 0;
};