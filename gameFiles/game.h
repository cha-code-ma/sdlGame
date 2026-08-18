#ifndef GAME_H
#define GAME_H
#include "structs.h"

bool save_data(game_t *game_p);

bool load_settings(game_t *game_p);

game_t *game_init(SDL_Renderer *renderer, SDL_Window *window);

void game_set_time(game_t *game, Uint64 cur_time, Uint64 prev_time);
void game_set_input(game_t *game, int button, float x, float y, bool input);

#endif