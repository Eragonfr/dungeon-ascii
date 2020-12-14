#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "player.h"
#include "loop.h"


void print() {
	for (int y = 0; y < MAP_HEIGHT; ++y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			printf("%c", getTile(x, y));
		}
		printf("\n");
	}
}

int main() {
	srand((unsigned)time(NULL));

	Player player;
	char *tiles = calloc(MAP_WIDTH*MAP_HEIGHT, sizeof(char));

	player.life = 10;
	player.x = 0;
	player.y = 0;

	tiles = makeMap();
	//print("%s\n", tiles);

	initscr();
	cbreak();
	noecho();

	if (has_colors() == FALSE) {
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	if (can_change_color() == FALSE) {
		endwin();
		printf("Your terminal does not support custom colors\n");
		exit(1);
	}

	start_color();

	init_pair(WALL_PAIR, COLOR_RED, COLOR_RED);
	init_pair(FLOOR_PAIR, COLOR_BLUE, COLOR_BLUE);
	init_pair(VOID_PAIR, COLOR_BLACK, COLOR_BLACK);
	init_pair(PLAYER_PAIR, COLOR_WHITE, COLOR_BLUE);

	tiles = makeMap();

	while (!checkPos(player.x, player.y, tiles) && player.y < MAP_HEIGHT) {
		player.y += 1;
		player.x = 0;
		while (!checkPos(player.x, player.y, tiles) && player.x < MAP_WIDTH) {
			player.x += 1;
		}
	}

	tiles[player.y*MAP_WIDTH+player.x] = '@';

	clear();
	renderMap(tiles, player);

	mainLoop(tiles, player);

	clrtoeol();
	refresh();
	endwin();
	return 0;
}
