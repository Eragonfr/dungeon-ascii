#ifdef _WIN32

#include <conio.h>

char readInput() {
	return _getch();
}
#endif

#ifdef __unix__

#include <curses.h>

char readInput() {
	initscr();
	char ch = getch();
	endwin();

	return ch;
}

#endif

char readInput();
