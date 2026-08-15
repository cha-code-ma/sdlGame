#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

game *game_init(SDL_Renderer *renderer, SDL_Window *window) {
    game *game_p = calloc(1, sizeof(game));
    if (!game_p) {
        return NULL;
    }
    game_p->renderer = renderer;
    game_p->window = window;
    set_settings(&game_p->settings);

    return game_p;
}

void free_game(game *game_p) {
    if (!game_p) {
        return;
    }
    free(game_p);
}

void set_settings(game_settings *settings) {
    char *path = SDL_GetPrefPath()
}