#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "object_pools.h"
#include "button.h"

void update_level(game_t *game) {
    update_level_objects(game);
    update_level_UI(game);

}

void update_level_UI(game_t *game) {
    update_level_buttons(game);
    update_level_text(game);
    update_level_UI_objects(game);
}

void update_level_UI_objects(game_t *game) {
    update_object_pool(game->state.active_level->UI->ui_objects, game);
}

void update_level_objects(game_t *game) {
    update_object_pool(game->state.active_level->objects, game);
}

void update_object_pool(object_pool *pool, game_t *game) {
    int count;
    object **objects = object_pool_get_objects(pool, &count);
    if (!objects) return;
    for (int i = 0; i < count; i++) {
        update_object(objects[i], game);
    }
}



void update_object(object *obj, game_t *game) {
    Uint64 cur_time = game->state.time;
    Uint64 prev_time = game->state.time;
    Uint64 dt = (cur_time - prev_time) / 1000; //change this, var in game struct?
    if (obj->fixed_transform_lists) {
        float extra_time;
        if (obj->fixed_transform_lists->pos) {
            fixed_tempelate_list *pos = obj->fixed_transform_lists->pos;
            if (pos->time_left - dt < 0) {
                extra_time = pos->time_left - dt;
                pos->index = (pos->index + 1) % pos->length;
                pos->time_left = pos->time_list[pos->index];
                obj->transform.future_position.x = pos->fixed_list.x[pos->index];
                obj->transform.future_position.y = pos->fixed_list.y[pos->index];
            } else {
                pos->time_left -= dt;
                extra_time = 0;
            }
        }
        if (obj->fixed_transform_lists->size) {
            fixed_tempelate_list *size = obj->fixed_transform_lists->size;
            if (size->time_left - dt < 0) {
                extra_time = size->time_left - dt;
                size->index = (size->index + 1) % size->length;
                size->time_left = size->time_list[size->index];
                obj->transform.future_size.x = size->fixed_list.x[size->index];
                obj->transform.future_size.y = size->fixed_list.y[size->index];
            } else {
                size->time_left -= dt;
                extra_time = 0;
            }
        }

    }
    if (game->IO.current_key == SDL_BUTTON_LEFT) {
        if (object_clicked(obj, game, true)) {
            object_click_action(obj);
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