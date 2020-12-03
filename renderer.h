#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "rgbchar.h"

int colorEquals(RgbChar a, RgbChar b);
void setColor(char* buffer, int r, int g, int b);
void setColorComponent(char* buffer, int color, int off);

void renderMap(struct RgbChar* map, int count);
