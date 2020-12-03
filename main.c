#include <stdio.h>

#include "renderer.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 20

int main()
{
    RgbChar map[] = {
        {   0,   0, 255, 219 },
        { 255, 255, 255, 219 },
        { 255,   0,   0, 219 }
    };

    renderMap(map, sizeof(map) / sizeof(map[0]));

    return 0;
}