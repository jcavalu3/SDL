#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "dirt.h"

dirt :: dirt()
{
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 18; x++)
		{
			grid[x][y] = 0;
		}
	}
}

void dirt :: init(int level)
{
	if (level == 0)
	{
		for (int y = 0; y < 30; y++)
		{
			for (int x = 0; x < 18; x++)
			{
				if (( y==11 || y==22 ) && ( x==5|| x==3 || x==4 || x==14 || x==12 || x==13))
				{
					grid[x][y]=0;
				}
				else if(x==9 && y>=3 &&y<=17)
				{
					grid[x][y]=0;
				}
				else
				{	
					grid[x][y] = (y + (level + 3)) / 3;
				}
			}
		}
	}
}

void dirt :: clear()
{
	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 18; x++)
		{
			grid[x][y] = 0;
		}
	}
}

void dirt :: set(int x, int y, int value)
{
	grid[x][y] = value;
}

int dirt :: get(int x, int y)
{
	return(grid[x][y]);
}
