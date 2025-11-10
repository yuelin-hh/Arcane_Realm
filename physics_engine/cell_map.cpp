#include "cell_map.h"

CellMap::CellMap()
{
}

CellMap::CellMap(int x, int y)
{
	create_map(x, y);
}

CellMap::~CellMap()
{
	cell_list.clear();
}