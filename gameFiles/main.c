/*

*/
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <stdbool.h>
#include "SDL3/SDL.h"
#define SDL_MAIN_HANDLED

int main(void) {
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");

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
		//reset_all_dx_dy(list_c);
		Uint64 current_time = SDL_GetTicks();
		game_set_time(game, current_time, last_time);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT:
					running = false;
					break;
				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						button_
						butt  event.button.x
					}
					if (event.button.button = SDL_BUTTON_RIGHT) {

					}
					break;
				default:

					break;
			}

		}
		if (!running) {
			break;
		}
		set_all_false(square);
		const Uint8* keystates = SDL_GetKeyboardState(NULL);

		if (keystates[SDL_SCANCODE_W]) { object_set_bool_up(square, true); }
		if (keystates[SDL_SCANCODE_A]) { object_set_bool_left(square, true); }
		if (keystates[SDL_SCANCODE_S]) { object_set_bool_down(square, true); }
		if (keystates[SDL_SCANCODE_D]) { object_set_bool_right(square, true); }

		update_future_movement(square, object_get_bool_left(square), object_get_bool_right(square), object_get_bool_up(square), object_get_bool_down(square), dt);




		move_charachter(all_objects_list, square, dt);


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		draw_all_characters(renderer, list_c);
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	SDL_Quit();
	return 0;
}
