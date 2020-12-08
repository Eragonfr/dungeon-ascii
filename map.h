#include "rgbchar.h"

#define MAP_WIDTH 80
#define MAP_HEIGHT 20

/*
#define WALL_FULL_CHAR "█"
#define WALL_UP_CHAR "▀"
#define WALL_DOWN_CHAR "▄"
*/

#define WALL_COLOR 255, 0, 0
#define FLOOR_COLOR 169, 169, 169
#define VOID_COLOR 0, 0, 0

struct Rect {
	int x, y;
	int width, height;
};

enum Tile {
	Unused		= ' ',
	Floor		= '.',
	Corridor	= ',',
	Wall		= '#',
	ClosedDoor	= '+',
	OpenDoor	= '-',
};

enum Direction {
	North,
	South,
	West,
	East,
	DirectionCount,
};

void makeMap(RgbChar * map);
