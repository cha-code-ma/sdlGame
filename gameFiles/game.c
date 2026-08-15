#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <SDL3/SDL.h>
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

char *get_settings_path(void) {
    char *path = SDL_GetPrefPath("chakirCode", "settings");
    if (!path) {
        SDL_Log("cant get preffered path");
        return NULL;
    }
    static char full_path[512];
    SDL_snprintf(full_path, sizeof(full_path), "%s%s", path, "settings.bin");
    //volledige pad
    SDL_free(path);

    return full_path;
}

bool save_settings(game *game_p) {
    char *path = get_settings_path();
    if (!path) return false;

    SDL_IOStream *file = SDL_IOFromFile(path, "wb");
    if (!file) return false;

    SDL_WriteIO(file, &game_p->settings, sizeof(game_settings));
    SDL_CloseIO(file);
    return true;
}

bool load_settings(const char *path, game *game_p) {
    char *path = get_settings_path();
    if  (!path) return false;

    SDL_IOStream *file = SDL_RWFromFile(path, "rb");
    if (!path) return false;

    size_t read = SDL_ReadIO(file, &game_p->settings, sizeof(game_settings));

    SDL_RWclose(file);

    if (read != 1) return false;

    return true;

}
