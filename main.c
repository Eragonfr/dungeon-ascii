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
	RgbChar *map = calloc(MAP_WIDTH*MAP_HEIGHT, sizeof(RgbChar));
	RgbChar init = {0, 0, 0, 0};
	map[0] = init;
	map = makeMap(map);

	renderMap(map, MAP_WIDTH * MAP_HEIGHT);

	printf("%c", readInput());
	return 0;
}
