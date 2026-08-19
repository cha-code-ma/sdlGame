/*

*/
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <stdbool.h>
#include "SDL3/SDL.h"
#define SDL_MAIN_HANDLED
#define SCREEN_WIDTH 800
#define SCREEN_HEIGTH 450
int main(void) {
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
	SDL_SetHint(SDL_HINT_TOUCH_MOUSE_EVENTS, "0");
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







	SDL_Window* window = SDL_CreateWindow("Move Game", 800, 600, SDL_WINDOW_RESIZABLE);
	if (!window) {
		SDL_Quit();
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		SDL_Log("Renderer init error %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	game_t *game = game_init(renderer, window);
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
				case SDL_EVENT_QUIT:
					running = false;
					break;
				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						game_set_input(game, event.button.button, event.button.x, event.button.y, true);
					}
					if (event.button.button == SDL_BUTTON_RIGHT) {

					}
					break;
				case SDL_EVENT_FINGER_DOWN:
					float x = event.tfinger.x * SCREEN_WIDTH;
					float y = event.tfinger.y * SCREEN_HEIGTH;
					game_set_input(game, event.button.button, x, y, true);
				break;
				default:
					game_set_input(game, 0, 0, 0, false);
				break;
			}

		}
		if (!running) {
			break;
		}


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	SDL_Quit();
	return 0;
}
