#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "object_pools.h"
#include "button.h"

void update_level_buttons(game_t *game) {
    if (!game->state.active_level->UI->buttons) {
        return;
    }
    button_pool *buttons =game->state.active_level->UI->buttons;
    for (int i = 0; i < buttons->capacity; i++) {
        if (buttons->buttons[i]) {
            if (buttons->buttons[i]->active && buttons->buttons[i]->visible) {
                //check_button_clicked(buttons->buttons[i], game->IO.mouse_pos.x, game->IO.mouse_pos.y);
            }
        }

    }
}

bool object_clicked(object *obj, game_t *game, bool future) {
    if (!obj || !game || !obj->is_clickable || game->IO.cur_valid != TIME_TYPE_VALID) return false;
    if (!obj->clicked) {
        if (future) {
            if (obj->transform.future_position.x <= game->IO.mouse_pos.x && obj->transform.future_position.x + obj->transform.future_size.x >= game->IO.mouse_pos.x &&
            obj->transform.future_position.y < game->IO.mouse_pos.y && obj->transform.future_position.y + obj->transform.future_size.y >= game->IO.mouse_pos.y) {
                return true;
            }
        } else {
            if (obj->transform.position.x <= game->IO.mouse_pos.x && obj->transform.position.x + obj->transform.size.x >= game->IO.mouse_pos.x &&
            obj->transform.position.y < game->IO.mouse_pos.y && obj->transform.position.y + obj->transform.size.y >= game->IO.mouse_pos.y) {
                return true;
            }
        }
    }
    return false;
}
void update_text_ui(text_ui *text, game_t *game) {

}
void update_text_pool(text_ui_pool *pool, game_t *game) {
    int count;
    text_ui **ui_text;
    bool debug = pool_get_objects(pool, (void ***)&ui_text, POOL_TYPES_TEXT_UI, &count);
    if (!debug) return;
    for (int i = 0; i < count; i++) {
        update_text_ui(ui_text[i], game);
    }
}

void update_object(object *obj, game_t *game) {
    //SDL_Log("update_object function");
    Uint64 cur_time = game->state.time;
    Uint64 prev_time = game->state.time;
    Uint64 dt = game->state.dt;
    if (obj->fixed_transform_lists) {
        Uint64 extra_time;
        if (obj->fixed_transform_lists->pos) {
            fixed_tempelate_list *pos = obj->fixed_transform_lists->pos;
            if (pos->time_left <= dt) {
                extra_time = dt - pos->time_left;
                pos->index = (pos->index + 1) % pos->length;
                pos->time_left = pos->time_list[pos->index] - extra_time;
                obj->transform.future_position.x = pos->fixed_list.x[pos->index];
                obj->transform.future_position.y = pos->fixed_list.y[pos->index];
            } else {
                pos->time_left -= dt;

                extra_time = 0;
            }
        }
        if (obj->fixed_transform_lists->size) {
            fixed_tempelate_list *size = obj->fixed_transform_lists->size;
            if (size->time_left <= dt) {
                extra_time = dt - size->time_left;
                size->index = (size->index + 1) % size->length;
                size->time_left = size->time_list[size->index]- extra_time;
                obj->transform.future_size.x = size->fixed_list.x[size->index];
                obj->transform.future_size.y = size->fixed_list.y[size->index];
            } else {
                size->time_left -= dt;
                SDL_Log("time_left size: %lu", size->time_left);
                SDL_Log("index: %d", size->index);
                extra_time = 0;
            }
        }

    }
    if (game->IO.current_key == SDL_BUTTON_LEFT) {
        SDL_Log("input detected: object may be clicked");
        if (object_clicked(obj, game, true)) {
            SDL_Log("object is clicked");
            object_click_action(obj);
        }
    }
}
void update_object_pool(object_pool *pool, game_t *game) {
    int count;
    object **objects;
    bool debug = pool_get_objects(pool, (void ***)&objects, POOL_TYPES_OBJECT, &count);
    if (!debug) return;
    for (int i = 0; i < count; i++) {
        update_object(objects[i], game);
    }
}

void update_level_UI_objects(game_t *game) {
    update_text_pool(game->state.active_level->UI->strings, game);
    update_object_pool(game->state.active_level->UI->ui_objects, game);
}

void update_level_UI(game_t *game) {
    if (game->state.active_level->UI->buttons) {
        update_level_buttons(game);
    }
    if (game->state.active_level->UI->strings) {
        //update_level_text(game);
    }

    if (game->state.active_level->UI->ui_objects) {
       // update_level_UI_objects(game);
    }

}
void update_menu_buttons(game_t *game_ptr) { //not done
    if (!game_ptr->state.active_level->UI->buttons) {
        return;
    }
    button_pool *buttons =game_ptr->state.active_level->UI->buttons;
    for (int i = 0; i < buttons->capacity; i++) {
        if (buttons->buttons[i]) {
            if (buttons->buttons[i]->active && buttons->buttons[i]->visible) {
               // check_button_clicked(buttons->buttons[i], game_ptr->IO.mouse_pos.x, game_ptr->IO.mouse_pos.y);
            }
        }

    }
} 





void update_level_objects(game_t *game) {
    //SDL_Log("update_level_objects function");
    update_object_pool(game->state.active_level->objects, game);
}





void update_level(game_t *game) {
    //SDL_Log("update level function");

    if (game->state.active_level->objects) {
        update_level_objects(game);
    }
    //if (game->state.active_level->UI) {
     //   update_level_UI(game);
    //}


}



void update_active_level(game_t *game) {
    if (game && game->state.active_level) {
        update_level(game);
    }
}


