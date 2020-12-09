#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rgbchar.h"

int colorEquals(RgbChar a, RgbChar b);

int writeColor(char* buffer, unsigned char r, unsigned char g, unsigned char b);
int writeColorComponent(char* buffer, unsigned char color, unsigned int off);

void renderMap(const RgbChar* map, unsigned int count);
