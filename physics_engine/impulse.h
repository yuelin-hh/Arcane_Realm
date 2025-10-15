#pragma once

#include "velocity.h"
#include "force.h"

class Impulse
{
public:
	Impulse();
	Impulse(double x, double y);
	Impulse(Velocity v, double m);
	Impulse(Force F, double t);
	~Impulse();

	Impulse operator+(const Impulse& F) const;

	void operator+=(const Impulse& F);

	Impulse operator*(const double& num) const;

	void operator*=(double num);

	Velocity operator/(double m);

	bool operator==(const Impulse& F) const;

	double mgt();

	void clear();

	double x = 0;
	double y = 0;
};