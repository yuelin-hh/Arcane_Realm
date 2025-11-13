#include "map.h"
#include "random.h"
int main()
{
	Map<7, 9> map;

	map.create_tile_map();

	std::cout << map;

	return 0;
}