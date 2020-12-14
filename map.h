#include "player.h"

#define MAP_WIDTH 80
#define MAP_HEIGHT 20

#define WALL_CHAR '#'
#define FLOOR_CHAR ' '
#define VOID_CHAR '.'
#define PLAYER_CHAR '@'

#define WALL_PAIR	1
#define FLOOR_PAIR	2
#define VOID_PAIR	3
#define PLAYER_PAIR 4


struct Rect {
	int x, y;
	int width, height;
};

enum Direction {
	North,
	South,
	West,
	East,
	DirectionCount,
};

char * makeMap();
char getTile(int x, int y);
void renderMap(const char* map, const Player player);
