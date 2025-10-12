#pragma once
#include <string>

namespace tools
{
	int power(int times);

	int to_ten(std::string num);

	/*std::string to_two(int num)
	{
		std::string sum = "";
		while (num != 0)
		{
			if (num % 2)
				sum = "1" + sum;
			else
				sum = "0" + sum;
			num = num / 2;
		}
		return sum;
	}*/

	
}