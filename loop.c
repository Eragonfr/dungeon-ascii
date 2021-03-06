#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include "input.h"
#include "player.h"
#include "map.h"

_Bool checkPos(int x, int y, char tiles[MAP_WIDTH*MAP_HEIGHT]) {
	int tilePos = y*MAP_WIDTH+x;
	if (tiles[tilePos] == FLOOR_CHAR || tiles[tilePos] == PLAYER_CHAR) {
		return 1;
	}
	else {
		return 0;
	}
}

void mainLoop(char tiles[MAP_WIDTH*MAP_HEIGHT], Player player) {
	int loop, ch, oldx, oldy;
	loop = 1;
	oldy = player.x;
	oldx = player.y;

	while (loop) {
		ch = getch();

		switch(ch) {
			case 'z':
				oldx = player.x;
				oldy = player.y;
				if (checkPos(player.x, player.y - 1, tiles)) {
					player.y--;
					tiles[player.y*MAP_WIDTH+player.x] = PLAYER_CHAR;
					tiles[oldy*MAP_WIDTH+oldx] = FLOOR_CHAR;
				}
				break;
			case 's':
				oldx = player.x;
				oldy = player.y;
				if (checkPos(player.x, player.y + 1, tiles)) {
					player.y++;
					tiles[player.y*MAP_WIDTH+player.x] = PLAYER_CHAR;
					tiles[oldy*MAP_WIDTH+oldx] = FLOOR_CHAR;
				}
				break;
			case 'd':
				oldx = player.x;
				oldy = player.y;
				if (checkPos(player.x + 1, player.y, tiles)) {
					player.x++;
					tiles[player.y*MAP_WIDTH+player.x] = PLAYER_CHAR;
					tiles[oldy*MAP_WIDTH+oldx] = FLOOR_CHAR;
				}
				break;
			case 'q':
				oldx = player.x;
				oldy = player.y;
				if (checkPos(player.x - 1, player.y, tiles)) {
					player.x--;
					tiles[player.y*MAP_WIDTH+player.x] = PLAYER_CHAR;
					tiles[oldy*MAP_WIDTH+oldx] = FLOOR_CHAR;
				}
				break;
			case 65:
				oldx = player.x;
				oldy = player.y;
				if (checkPos(player.x, player.y - 1, tiles)) {
					player.y--;
					tiles[player.y*MAP_WIDTH+player.x] = PLAYER_CHAR;
					tiles[oldy*MAP_WIDTH+oldx] = FLOOR_CHAR;
				}
				break;
			case 66:
				oldx = player.x;
				oldy = player.y;
				if (checkPos(player.x, player.y + 1, tiles)) {
					player.y++;
					tiles[player.y*MAP_WIDTH+player.x] = PLAYER_CHAR;
					tiles[oldy*MAP_WIDTH+oldx] = FLOOR_CHAR;
				}
				break;
			case 67:
				oldx = player.x;
				oldy = player.y;
				if (checkPos(player.x + 1, player.y, tiles)) {
					player.x++;
					tiles[player.y*MAP_WIDTH+player.x] = PLAYER_CHAR;
					tiles[oldy*MAP_WIDTH+oldx] = FLOOR_CHAR;
				}
				break;
			case 68:
				oldx = player.x;
				oldy = player.y;
				if (checkPos(player.x - 1, player.y, tiles)) {
					player.x--;
					tiles[player.y*MAP_WIDTH+player.x] = PLAYER_CHAR;
					tiles[oldy*MAP_WIDTH+oldx] = FLOOR_CHAR;
				}
				break;
			case 127:
				loop = 0;
				break;
			default:
				break;
		}
		attron(COLOR_PAIR(FLOOR_PAIR));
		mvaddch(oldy, oldx, FLOOR_CHAR);
		attroff(COLOR_PAIR(FLOOR_PAIR));
		attron(COLOR_PAIR(PLAYER_PAIR));
		mvaddch(player.y, player.x, PLAYER_CHAR);
		attroff(COLOR_PAIR(PLAYER_PAIR));
		mvprintw(MAP_HEIGHT,0, "X: %d\tY: %d\t OX: %d\tOY: %d\n%d", player.x, player.y, oldx, oldy, ch);
		move(player.y, player.x);
		//renderMap(tiles, player);

		refresh();
	}
}
