#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "map.h"

int rooms_latest = 0;
int exits_latest = 0;
char tiles[MAP_WIDTH*MAP_HEIGHT];
struct Rect exits[MAP_WIDTH*MAP_HEIGHT];
struct Rect rooms[50];

int randInRange(int min, int max);
char getTile(int x, int y);
char* setTile(int x, int y, char tile);
_Bool generate(int maxFeatures);
_Bool randomBool();
_Bool createFeature();
_Bool placeRect(const struct Rect rect, const enum Tile tile);
_Bool makeCorridor(int x, int y, enum Direction dir);
_Bool createFeature(int x, int y, enum Direction dir);
_Bool makeRoom(int x, int y, enum Direction dir, _Bool firstRoom);
RgbChar * rgbMapFromAscii(RgbChar map[MAP_HEIGHT*MAP_WIDTH]);

int randInRange(int min, int max) {
	int result, temp;
	if (min > max) {
		temp = max;
		min = max;
		max = temp;
	}
	result = ((rand() % (max - min + 1)) + min);
	return result;
}

_Bool randomBool() {
	return rand() % 2;
}

char getTile(int x, int y) {
	if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) {
		return Unused;
	}

	return tiles[x + y * MAP_WIDTH];
}

void print() {
	for (int y = 0; y < MAP_HEIGHT; ++y) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			printf("%c", getTile(x, y));
		}
		printf("\n");
	}
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

	if (placeRect(room, Floor)) {
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

_Bool placeRect(const struct Rect rect, const enum Tile tile) {
	if (rect.x < 1 || rect.y < 1 || rect.x + rect.width > MAP_WIDTH - 1 || rect.y + rect.height > MAP_HEIGHT - 1) {
		return 0;
	}

	for (int y = rect.y; y < rect.y + rect.height; ++y) {
		for (int x = rect.x; x < rect.x + rect.width; ++x) {
			if (getTile(x, y) != Unused) {
				return 0;
			}
		}
	}

	for (int y = rect.y - 1; y < rect.y + rect.height + 1; ++y) {
		for (int x = rect.x - 1; x < rect.x + rect.width + 1; ++x) {
			if (x == rect.x - 1 || y == rect.y - 1 || x == rect.x + rect.width || y == rect.y + rect.height) {
				setTile(x, y, Wall);
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

	if (placeRect(corridor, Corridor)) {
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
	static const int roomChance = 50;

	int dx = 0;
	int dy = 0;

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

	if (getTile(x + dx, y + dy) != Floor && getTile(x + dx, y + dy) != Corridor) {
		return 0;
	}

	if (randInRange(0, 100) < roomChance) {
		if (makeRoom(x, y, dir, 0))
		{
			setTile(x, y, ClosedDoor);

			return 1;
		}
	}
	else {
		if (makeCorridor(x, y, dir)) {
			if (getTile(x + dx, y + dy) == Floor) {
				setTile(x, y, ClosedDoor);
			}
			else {
				setTile(x, y, Corridor);
			}

			return 1;
		}
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

	for (int i = 0; i < (sizeof(tiles)); ++i) {
		if (tiles[i] == Unused) {
			tiles[i] = '.';
		}
		else if (tiles[i] == Floor || tiles[i] == Corridor) {
			tiles[i] = ' ';
		}
	}
	return 1;
}

RgbChar *  rgbMapFromAscii(RgbChar map[MAP_HEIGHT*MAP_WIDTH]) {
	for (int i = 0; i < MAP_HEIGHT*MAP_WIDTH; i++) {
		if (tiles[i] == ' ' || tiles[i] ==  '+' || tiles[i] ==  '-') {
			RgbChar temp = {169, 169, 169, 35};
			map[i] = temp;
		}
		else if (tiles[i] == '.') {
			RgbChar temp = {0, 0, 0, 35};
			map[i] = temp;
		}
		else {
			RgbChar temp = {255, 0, 0, 35};
			map[i] = temp;
		}
	}
	return map;
}

RgbChar * makeMap(RgbChar map[MAP_HEIGHT*MAP_WIDTH]) {
	srand((unsigned)time(NULL));
	struct Rect rect = {0,0,0,0};
	do {
		exits[0] = rect;
		for (int i = 0; i < sizeof(tiles); i++) {
			tiles[i] = ' ';
		}
	} while (!generate(50));
	//print(map);

	for (int i = 0; i < MAP_HEIGHT*MAP_WIDTH; i++) {
		if (tiles[i] == ' ' || tiles[i] ==  '+' || tiles[i] ==  '-') {
			RgbChar temp = {FLOOR_COLOR, 35};
			map[i] = temp;
		}
		else if (tiles[i] == '.') {
			RgbChar temp = {VOID_COLOR, 35};
			map[i] = temp;
		}
		else {
			RgbChar temp = {WALL_COLOR, 35};
			map[i] = temp;
		}
	}
	return map;
}
