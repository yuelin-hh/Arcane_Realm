#pragma once
struct Cell
{
	Cell();
	Cell(int x, int y);

	int x = 0;
	int y = 0;

	bool traversed = false;

};