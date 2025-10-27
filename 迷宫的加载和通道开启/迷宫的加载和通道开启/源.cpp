#include <stdio.h>
#include<graphics.h>
#include<time.h>
#include<stdlib.h>

char random();
bool feasibility();
void finish();

char board_data[7][7] =
{
	{ '-', '-', '-', '-', '-', '-', '-' },
	{ '-','-','-','-','-','-','-' },
	{ '-','-','-','-','-','-','-' },
	{ '-','-','-','-','-','-','-' },
	{ '-','-','-','-','-','-','-' },
	{ '-','-','-','-','-','-','-' },
	{ '-','-','-','-','-','-','-' }
};
int main()
{
	bool running = 1;
	srand((unsigned)time(NULL));
	initgraph(1280, 720);
	
		while (running)
		{
			while (feasibility())
			{

			}
		}
	
}

char random()
{
	int min = 0, max = 1000;
	int range_random = rand() % (max - min + 1) + min;
	if (range_random >= 0 && range_random <= 250)
		return 'T';
	if(range_random>250&& range_random<=500)
		return 'B';
	if(range_random>500&& range_random<=750)
		return 'L';
	if(range_random>750&& range_random<=1000)
		return 'R';
}

bool feasibility(char *a)
{
	if ()
	{ }
	return 0;
}

void finish()
{

}

