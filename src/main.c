/*

*/
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <stdbool.h>
#include "SDL2/SDL.h"
#include "game.h"
#include "update.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGTH 450
int main(int argc, char *argv[]) {

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
	SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		const char* err = SDL_GetError();
		printf("SDL_Init failed: %s\n", err);

		SDL_ShowSimpleMessageBox(
			SDL_MESSAGEBOX_ERROR,
			"SDL Init failed",
			err,
			NULL
		);
		return 1;
	}
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
	SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");






	SDL_Window* window = SDL_CreateWindow("Move Game",0, 0, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_RESIZABLE);
	if (!window) {
		SDL_Quit();
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, (Uint32)0);
	if (!renderer) {
		SDL_Log("Renderer init error %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
    printf("IMG_Init failed: %s\n", SDL_GetError());
    return 1;
	}
	int active_level = 1;
	game_t *game = game_init(renderer, window, &active_level);
	if (!game) {
		SDL_Log("game init error %s", SDL_GetError());
		SDL_Quit();
	}
	//MAIN LOOP

	bool running = true;
	SDL_Event event;


	Uint64 last_time = SDL_GetTicks();
	while (running) {
		Uint64 current_time = SDL_GetTicks();
		game_set_time(game, current_time, last_time);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						game_set_input(game, event.button.button, event.button.x, event.button.y, true);
					}
					if (event.button.button == SDL_BUTTON_RIGHT) {

					}
					break;
				case SDL_FINGERDOWN:
					float x = event.tfinger.x * SCREEN_WIDTH;
					float y = event.tfinger.y * SCREEN_HEIGTH;
					game_set_input(game, event.button.button, x, y, true);
				break;
				default:
					game_set_input(game, 0, 0, 0, false);
				break;
			}
			update_level(game);

		}
		if (!running) {
			break;
		}
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	SDL_Quit();
	return 0;
}
