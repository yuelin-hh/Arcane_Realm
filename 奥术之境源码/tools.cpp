#include "tools.h"

namespace tools
{
	int power(int times)
	{
		int product = 1;
		for (int i = 0; i < times; i++)
		{
			product = product * 2;
		}
		return product;
	}

	int to_ten(std::string num)
	{
		int sum = 0;
		for (int i = 0; i < num.size(); i++)
		{
			if (num[i] == '1')
			{
				sum += power(num.size() - i - 1);
			}
		}
		return sum;
	}

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