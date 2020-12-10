#include <stdlib.h>
#include <stdio.h>

#include "input.h"
#include "player.h"
#include "map.h"

void mainLoop(/*RgbChar map[MAP_HEIGHT*MAP_WIDTH],*/ Player player) {
	int loop, ch;
	loop = 1;

	#ifdef __unix__
	initscr();
	clear();
	cbreak();
	noecho();
	refresh();
	#endif

	while (loop) {
		#ifdef __unix__
		ch = getch();
		#endif
		#ifdef _WIN32
		ch = readInput();
		#endif

		switch(ch) {
			case 65:
				player.y++;
				break;
			case 122:
				player.y++;
				break;
			case 66:
				player.y--;
				break;
			case 115:
				player.y--;
				break;
			case 67:
				player.x++;
				break;
			case 100:
				player.x++;
				break;
			case 68:
				player.x--;
				break;
			case 113:
				player.x--;
				break;
			case 10:
				loop = 0;
				break;
			default:
				break;
		}
		clear();
		mvprintw(0, 0, "X : %d Y : %d", player.x, player.y);
		refresh();
	}

	#ifdef __unix__
	clrtoeol();
	refresh();
	endwin();
	#endif
}

int main()
{
	Player player;
	player.life = 10;
	player.x = 20;
	player.y = 10;
	mainLoop(player);
	return 0;
}
