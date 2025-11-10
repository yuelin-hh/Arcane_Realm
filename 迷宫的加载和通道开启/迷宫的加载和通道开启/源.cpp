#include "map.h"
#include "random.h"
int main()
{
	Map<7, 7> map;

	map.create_tile_map();

	std::cout << map;

	//std::cout << Random::check(0.3);

	return 0;
}