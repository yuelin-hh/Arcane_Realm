#pragma once
#include <random>

class Random
{
public:
	Random(){}
	~Random(){}

	static bool check(double p)
	{
		static std::random_device rd;
		static std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dis(0.0, 1.0); 
		double r_d = dis(gen);

		return r_d < p;
	}
};