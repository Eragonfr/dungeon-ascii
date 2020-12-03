#include <stdio.h>

#include "renderer.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 20

#ifdef _WIN32

#include <conio.h>

char readInput()
{
    return _getch();
}
#endif

#ifdef __unix__

#include "curses.h"

char readInput()
{
    initscr();
    char ch = getch();
    endwin();

    return ch;
}

#endif

char readInput();

int main()
{
    RgbChar map[] = {
        {   0,   0, 255, 219 },
        { 255, 255, 255, 219 },
        { 255,   0,   0, 219 }
    };

    printf("%c", readInput());

    renderMap(map, sizeof(map) / sizeof(map[0]));

    return 0;
}
