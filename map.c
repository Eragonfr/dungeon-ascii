#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

#include "map.h"
#include "rand.h"

int rooms_latest = 0;
int exits_latest = 0;
char tiles[MAP_WIDTH*MAP_HEIGHT];
struct Rect exits[MAP_WIDTH*MAP_HEIGHT];
struct Rect rooms[50];

char* setTile(int x, int y, char tile);
_Bool generate(int maxFeatures);
_Bool createFeature();
_Bool placeRect(const struct Rect rect, const char tile);
_Bool makeCorridor(int x, int y, enum Direction dir);
_Bool createFeature(int x, int y, enum Direction dir);
_Bool makeRoom(int x, int y, enum Direction dir, _Bool firstRoom);

char getTile(int x, int y) {
	if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) {
		return VOID_CHAR;
	}

	return tiles[x + y * MAP_WIDTH];
}

char* setTile(int x, int y, char tile) {
	tiles[x + y * MAP_WIDTH] = tile;
	return tiles;
}

_Bool createFeatureOne() {
	int r, x, y;

	for (int i = 0; i < 1000; ++i) {
		if (exits_latest == 0) {
			break;
		}

		r = randInRange(0, sizeof(exits)/sizeof(exits[0]));
		x = randInRange(exits[r].x, exits[r].x + exits[r].width - 1);
		y = randInRange(exits[r].y, exits[r].y + exits[r].height - 1);

		for (int j = 0; j < DirectionCount; ++j) {
			enum Direction dir = {j};
			if (createFeature(x, y, dir)) {
				struct Rect rect = {};
				exits[r] = rect;
				return 1;
			}
		}
	}
	return 0;
}

_Bool makeRoom(int x, int y, enum Direction dir, _Bool firstRoom) {
	static const int minRoomSize = 3;
	static const int maxRoomSize = 6;

	struct Rect room;
	room.width = randInRange(minRoomSize, maxRoomSize);
	room.height = randInRange(minRoomSize, maxRoomSize);

	if (dir == North) {
		room.x = x - room.width / 2;
		room.y = y - room.height;
	}

	else if (dir == South) {
		room.x = x - room.width / 2;
		room.y = y + 1;
	}

	else if (dir == West) {
		room.x = x - room.width;
		room.y = y - room.height / 2;
	}

	else if (dir == East) {
		room.x = x + 1;
		room.y = y - room.height / 2;
	}

	if (placeRect(room, FLOOR_CHAR)) {
		rooms[rooms_latest] = room;
		rooms_latest++;

		if (dir != South || firstRoom) {
			struct Rect rect = {room.x, room.y - 1, room.width, 1};
			exits[exits_latest] = rect;
			exits_latest++;
		}
		if (dir != North || firstRoom) {
			struct Rect rect = {room.x, room.y + room.height, room.width, 1};
			exits[exits_latest] = rect;
			exits_latest++;
		}
		if (dir != East || firstRoom) {
			struct Rect rect = {room.x - 1, room.y, 1, room.height};
			exits[exits_latest] = rect;
			exits_latest++;
		}
		if (dir != West || firstRoom) {
			struct Rect rect = {room.x + room.width, room.y, 1, room.height};
			exits[exits_latest] = rect;
			exits_latest++;
		}
		return 1;
	}
	return 0;
}

_Bool placeRect(const struct Rect rect, const char tile) {
	if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > MAP_WIDTH - 1 || rect.y + rect.height > MAP_HEIGHT - 1) {
		return 0;
	}

	for (int y = rect.y; y < rect.y + rect.height; ++y) {
		for (int x = rect.x; x < rect.x + rect.width; ++x) {
			if (getTile(x, y) != VOID_CHAR) {
				return 0;
			}
		}
	}

	for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y) {
		for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x) {
			if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height) {
				setTile(x, y, WALL_CHAR);
			}
			else {
				setTile(x, y, tile);
			}
		}
	}
	return 1;
}

_Bool makeCorridor(int x, int y, enum Direction dir) {
	static const int minCorridorLength = 3;
	static const int maxCorridorLength = 6;

	struct Rect corridor;
	corridor.x = x;
	corridor.y = y;

	if (randomBool()) {
		corridor.width = randInRange(minCorridorLength, maxCorridorLength);
		corridor.height = 1;

		if (dir == North) {
			corridor.y = y - 1;

			if (randomBool()) {
				corridor.x = x - corridor.width + 1;
			}
		}

		else if (dir == South) {
			corridor.y = y + 1;

			if (randomBool()) {
				corridor.x = x - corridor.width + 1;
			}
		}

		else if (dir == West) {
			corridor.x = x - corridor.width;
		}

		else if (dir == East) {
			corridor.x = x + 1;
		}
	}
	else {
		corridor.width = 1;
		corridor.height = randInRange(minCorridorLength, maxCorridorLength);

		if (dir == North) corridor.y = y - corridor.height;

		else if (dir == South) corridor.y = y + 1;

		else if (dir == West) {
			corridor.x = x - 1;

			if (randomBool()){
				corridor.y = y - corridor.height + 1;
			}
		}
		else if (dir == East) {
			corridor.x = x + 1;

			if (randomBool()) {
				corridor.y = y - corridor.height + 1;
			}
		}
	}

	if (placeRect(corridor, FLOOR_CHAR)) {
		if (dir != South && corridor.width != 1) {
			struct Rect rect = {corridor.x, corridor.y - 1, corridor.width, 1};
			exits[exits_latest] = rect;
			exits_latest++;
		}
		if (dir != North && corridor.width != 1) {
			struct Rect rect = {corridor.x, corridor.y + corridor.height, corridor.width, 1};
			exits[exits_latest] = rect;
			exits_latest++;
		}
		if (dir != East && corridor.height != 1) {
			struct Rect rect = {corridor.x - 1, corridor.y, 1, corridor.height};
			exits[exits_latest] = rect;
			exits_latest++;
		}
		if (dir != West && corridor.height != 1) {
			struct Rect rect = {corridor.x + corridor.width, corridor.y, 1, corridor.height};
			exits[exits_latest] = rect;
			exits_latest++;
		}
		return 1;
	}
	return 0;
}

_Bool createFeature(int x, int y, enum Direction dir) {
	int dx;
	int dy;

	dx = 0;
	dy = 0;

	if (dir == North) {
		dy = 1;
	}
	else if (dir == South) {
		dy = -1;
	}
	else if (dir == West) {
		dx = 1;
	}
	else if (dir == East) {
		dx = -1;
	}

	if (getTile(x + dx, y + dy) != FLOOR_CHAR) {
		return 0;
	}

	if (makeCorridor(x, y, dir)) {
		setTile(x, y, FLOOR_CHAR);
		return 1;
	}

	return 0;
}

_Bool generate(int maxFeatures) {
	enum Direction dir = {randInRange(0, 4)};
	if (!makeRoom(MAP_WIDTH / 2, MAP_HEIGHT / 2, dir, 1)) {
		return 0;
	}

	for (int i = 1; i < maxFeatures; ++i) {
		if (!createFeatureOne()) {
			return 0;
		}
	}

	return 1;
}

char * makeMap() {
	struct Rect rect = {0,0,0,0};

	do {
		exits[0] = rect;
		for (int i = 0; i < sizeof(tiles); i++) {
			tiles[i] = VOID_CHAR;
		}
	} while (!generate(50));

	return tiles;
}

void renderMap(const char* map, const Player player) {
	clear();
	move(0, 0);

	for (int i = 0; i < MAP_WIDTH*MAP_HEIGHT; i++) {
		if (map[i] == WALL_CHAR) {
			attron(COLOR_PAIR(WALL_PAIR));
			addch(WALL_CHAR);
			attroff(COLOR_PAIR(WALL_PAIR));
		}
		else if (map[i] == FLOOR_CHAR) {
			attron(COLOR_PAIR(FLOOR_PAIR));
			addch(FLOOR_CHAR);
			attroff(COLOR_PAIR(FLOOR_PAIR));
		}
		else if (map[i] == PLAYER_CHAR) {
			attron(COLOR_PAIR(PLAYER_PAIR));
			addch(PLAYER_CHAR);
			attroff(COLOR_PAIR(PLAYER_PAIR));
		}
		else if (map[i] == VOID_CHAR) {
			attron(COLOR_PAIR(VOID_PAIR));
			addch(VOID_CHAR);
			attroff(COLOR_PAIR(VOID_PAIR));
		}
	}
	printw("X: %d\tY: %d\n", player.x, player.y);
	move(player.y, player.x);
	refresh();
}
