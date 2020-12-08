#include <stdio.h>

#include "renderer.h"
#include "map.h"

#ifdef _WIN32

#include <conio.h>

char readInput()
{
	return _getch();
}
#endif

#ifdef __unix__

#include <curses.h>

char readInput()
{
	initscr();
	char ch = getch();
	endwin();

	return ch;
}

#endif

char readInput();

int main()
{
	RgbChar map[MAP_WIDTH*MAP_HEIGHT];
	makeMap(map);

	printf("%c", readInput());

	renderMap(map, sizeof(map) / sizeof(map[0]));

	return 0;
}
