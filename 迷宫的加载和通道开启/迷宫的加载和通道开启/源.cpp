#include "map.h"

int main()
{
	Map<7, 7> map;

	map.create_tile_map();

	std::cout << map;
	return 0;
}
