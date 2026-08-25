#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include <SDL2/SDL.h>
#include "levels.h"
#include "logic.h"
char *get_path(const char *file) {
    char *path = SDL_GetPrefPath("chakirCode", "tapGame");
    if (!path) {
        SDL_Log("cant get preffered path");
        return NULL;
    }
    static char full_path[512];
    SDL_snprintf(full_path, sizeof(full_path), "%s%s", path, file);
    //volledige pad
    SDL_free(path);

    return full_path;
}
//bool load_fonts(game_t *game_p) {
 //   game_p->fonts.basic_font = TTF_OpenFont("path_to_tff file", 24);
//}


bool load_textures(game_t *game_p, SDL_Renderer *renderer) {
    SDL_Surface *surface = IMG_Load("media/character_poppetje.png");
	if (!surface) return false;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) return false;
    game_p->textures.circle_yellow = texture;
}

bool load_special_effects(game_t *game_p) {
    //....
}

bool load_sounds(game_t *game_p) {
    game_sounds *sounds = &game_p->sounds;
    //.....
}


bool load_all_levels(game_state *state) {
    int level_count = 1;
    state->all_levels = calloc(level_count + 1, sizeof(level*));
    SDL_Log("load_all_levels calloc has done");
    if (!state->all_levels) return false;
    SDL_Log("calloc succesfull");
    state->all_levels[0] = init_level_1();
    SDL_Log("end of load_all_levels_function");
    return true;
}

bool load_menu(game_state *state) {
    menu *menu_p = &state->menu;
    //........
    return true;
}

bool load_game_state(game_t *game_p) {
    SDL_Log("load game state function start");
    game_state *state = &game_p->state;
    bool debug;
    debug = load_all_levels(state);
    if (!debug) return false;
    state->time = 0;
    SDL_Log("time = 0");
    debug = load_menu(state);
    SDL_Log("menu loaded");
    if (!debug) return NULL;
    return true;
}




void free_game(game_t *game_p) {
    if (!game_p) {
        return;
    }
    free(game_p);
}



bool save_game_values(game_t *game_p) {
    char *path = get_path("save_values.ibm");
    if (!path) return false;

    SDL_RWops *file = SDL_RWFromFile(path, "wb");
    if (!file) return false;

    SDL_RWwrite(file, &game_p->save_values, sizeof(game_save_values), 1);
    SDL_RWclose(file);
    return true;
}



bool load_game_values(game_t *game_p) {
    game_p->values.coins = game_p->save_values.coins;
    game_p->values.diamonds = game_p->save_values.diamonds;
    game_p->values.level = game_p->save_values.level;
    game_p->values.xp = game_p->save_values.xp;
    return true;
}


bool valid_volume(int volume) {
    if (volume > 100 || volume < 0) {
        return false;
    }
    return true;
}


bool file_exist(const char *full_path) {
    SDL_RWops *file = SDL_RWFromFile(full_path, "rb");
    if (file) {
        SDL_RWclose(file);
        return true;
    }
    return false;
}

bool load_saved_values(game_t *game_p) {
    char *path = get_path("save_values.ibm");
    if  (!path) return false;
    SDL_RWops *file;
    if (file_exist(path)) {
        SDL_RWops *file = SDL_RWFromFile(path, "rb");
        size_t read = SDL_RWread(file, &game_p->save_values, sizeof(game_save_values), 1);
        SDL_RWclose(file);
        if (read != 1) return false;
        bool debug;
        //debug = load_settings(game_p);
        //if (!debug) return false;
        debug = load_game_values(game_p);
        if (!debug) return false;
    }

    //bool debug = set_default_save_values(file, game_p);
    //if (!debug) return false;

    return true;

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

bool save_data(game_t *game_p) {
    char *path = get_settings_path();
    if (!path) return false;

    SDL_RWops *file = SDL_RWFromFile(path, "wb");
    if (!file) return false;

    SDL_RWwrite(file, &game_p->settings, sizeof(game_settings), 1);
    SDL_RWclose(file);
    return true;
}
/*bool in_language_list(char language[30], game_t *game_p) {
    char *list[30] = game_p->const_values.languages;
    for (int i = 0; i <game_p->const_values.amount_languages; i++) {
        if (strcmp(list[i], language)) return true;
    }
    return false;
}*/

bool set_default_settings(game_t *game_p) {
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

bool load_settings(game_t *game_p) {
    strcpy(game_p->settings.language, game_p->save_values.language);
    game_p->settings.music = game_p->save_values.music;
    game_p->settings.music_volume = game_p->save_values.music_volume;
    game_p->settings.sound_effects = game_p->save_values.sound_effects;
    game_p->settings.sound_effects_volume = game_p->save_values.sound_effects_volume;
   // if (!in_language_list(game_p->settings.language, game_p) ||
   // !valid_volume(game_p->settings.music_volume) ||
  //  !valid_volume(game_p->settings.sound_effects_volume)) {
  //      set_default_settings(game_p);
 //   }
    return true;
}




void game_set_time(game_t *game, Uint64 cur_time, Uint64 prev_time) {
    if (!game) return;
    game->state.time = cur_time;
    game->state.dt = (float)(cur_time - prev_time);
}

void game_set_input(game_t *game, int button, float x, float y, bool input) {
    if (!game) return;
    if (input) {
        game->IO.previous_key = game->IO.current_key;
        game->IO.current_key = button;
        game->IO.prev_valid = game->IO.cur_valid;
        game->IO.cur_valid = TIME_TYPE_VALID;
        game->IO.key_time = 0.5;
        game->IO.prev_mouse_pos.x = game->IO.mouse_pos.x;
        game->IO.prev_mouse_pos.y = game->IO.prev_mouse_pos.y;
        game->IO.mouse_pos.x = x;
        game->IO.prev_mouse_pos.y = y;
    } else {

        if (!(game->IO.prev_valid == TIME_TYPE_INVALID) && game->IO.key_time - game->state.dt < 0) {
            game->IO.cur_valid = TIME_TYPE_LATE;
            game->IO.prev_valid = TIME_TYPE_LATE;
            game->IO.key_time = 0.5;
        } else {
            game->IO.key_time -= game->state.dt;
        }
    }
}

game_t *game_init(SDL_Renderer *renderer, SDL_Window *window, int *active_level) {
    SDL_Log("game_init: start");
    
    game_t *game_p = calloc(1, sizeof(game_t));
    if (!game_p) {
        SDL_Log("game_init: calloc failed");
        return NULL;
    }
    SDL_Log("game_init: calloc OK");
    
    game_p->renderer = renderer;
    game_p->window = window;
    SDL_Log("game_init: renderer and window set");
    bool debug = true;
    // Load saved values
    //bool debug = load_saved_values(game_p);
    if (!debug) {
        SDL_Log("game_init: load_saved_values failed");
        free(game_p);
        return NULL;
    }
    SDL_Log("game_init: load_saved_values OK");
    
    // Load sounds (skip for now)
    // debug = load_sounds(game_p);
    // if (!debug) {
    //     SDL_Log("game_init: load_sounds failed");
    //     free(game_p);
    //     return NULL;
    // }
    
    // Load special effects (skip for now)
    // debug = load_special_effects(game_p);
    // if (!debug) {
    //     SDL_Log("game_init: load_special_effects failed");
    //     free(game_p);
    //     return NULL;
    // }
    
    // Load game state
    debug = load_game_state(game_p);
    if (!debug) {
        SDL_Log("game_init: load_game_state failed: %s", SDL_GetError());
        free(game_p);
        return NULL;
    }
    SDL_Log("game_init: load_game_state OK");
    
    // Load textures
    //debug = load_textures(game_p, renderer);
    if (!debug) {
        SDL_Log("game_init: load_textures failed");
        free(game_p);
        return NULL;
    }
    SDL_Log("game_init: load_textures OK");
    
    // Load fonts
    //debug = load_fonts(game_p);
    if (!debug) {
        SDL_Log("game_init: load_fonts failed");
        free(game_p);
        return NULL;
    }
    SDL_Log("game_init: load_fonts OK");
    
    //Set active level
    if (active_level && *active_level > 0) {
        game_p->state.active_level = game_p->state.all_levels[*active_level-1];
       SDL_Log("game_init: active level set to %d", *active_level);
    }
    
    SDL_Log("game_init: SUCCESS!");
    return game_p;
}

//save_values

void show_active_level(game_t *game) {
    if (!game || !game->state.active_level) return;
    show_obj_pool(game->state.active_level->objects, game->renderer);
}