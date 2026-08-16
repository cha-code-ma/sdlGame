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
    bool debug = load_settings(&game_p->settings);
    if (!debug) return NULL;
    debug = load_sounds(&game_p->sounds);
    if (!debug) return NULL;
    debug = load_special_effects(&game_p->special_effects);
    debug = load_game_state(game_p);
    return game_p;
}

bool load_game_state(game *game_p) {
    game_state *state = &game_p->state;
    bool debug;
    debug = load_all_levels(state);
    if (!debug) return false;
    state->last_registered_logic_time = 0;
    load_menu(&state->menu);
    state->time = 0;
}

bool load_all_levels(game_state *state) {
    int level_count = 1;
    state->all_levels = calloc(1, sizeof(level*));
    if (!state->all_levels) return false;
}

void free_game(game *game_p) {
    if (!game_p) {
        return;
    }
    free(game_p);
}
//settings

bool settings_exist(const char *path) {
    SDL_IOStream *file = SDL_IOFromFile(path, 'rb');
    if (file) {
        SDL_CloseIO(file);
        return true;
    }
    return false;
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

bool load_settings(game *game_p) {
    char *path = get_settings_path();
    if  (!path) return false;

    if (settings_exist(path)) {
        SDL_IOStream *file = SDL_IOFromFile(path, "rb");
        size_t read = SDL_ReadIO(file, &game_p->settings, sizeof(game_settings));
        SDL_RWclose(file);
        if (read != 1) return false;
        game_settings settings = game_p->settings;

        if (in_language_list(settings.language) ||
        valid_volume(settings.sound_effects_volume) ||
        valid_volume(settings.music_volume))
        return true;
    }

    bool debug = set_default_settings(path, game_p);
    if (!debug) return false;


    return true;

}

bool set_default_settings(const char *path, game *game_p) {
    if (!game_p) {
        return false;
    }
    strcpy(game_p->settings.language, "english");
    game_p->settings.music = true;
    game_p->settings.music_volume = 100;
    game_p->settings.sound_effects = true;
    game_p->settings.sound_effects_volume = 100;
    return true;
}

bool valid_volume(int volume) {
    if (volume > 100 || volume < 0) {
        return false;
    }
    return true;
}
