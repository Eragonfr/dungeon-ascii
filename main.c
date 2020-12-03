#include <stdio.h>
#include <windows.h>

#include "renderer.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 20

int main()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD  dwMode = 0;

    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    RgbChar map[] = {
        {   0,   0, 255, 219 },
        { 255, 255, 255, 219 },
        { 255,   0,   0, 219 }
    };

    renderMap(map, sizeof(map) / sizeof(map[0]));

    return 0;
}