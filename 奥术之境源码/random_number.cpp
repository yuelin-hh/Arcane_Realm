#include "random_number.h"

#include<iostream>
#include<random>

extern std::mt19937 gen;

int get_random_number(int min, int max)
{
	std::uniform_real_distribution<>int_dis(min, max);
	return int_dis(gen);
}