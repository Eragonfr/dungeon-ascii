#include <SDL2/SDL.h> 


int main() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialize the SDL2 library\nSDL2 Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);

	if(!window) {
		printf("Failed to create window\nSDL2 Error: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Surface *window_surface = SDL_GetWindowSurface(window);

	if(!window_surface) {
		printf("Failed to get the surface from the window\nSDL2 Error: %s\n", SDL_GetError());
		return 1;
	}

	_Bool keep_window_open = 1;
	while(keep_window_open) {
		SDL_Event e;
		while(SDL_PollEvent(&e) > 0) {
			switch(e.type) {
				case SDL_QUIT:
					keep_window_open = 0;
					break;
			}

			SDL_UpdateWindowSurface(window);
		}
	}

	return 0;
}
