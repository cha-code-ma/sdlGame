#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

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

    } elif (game->state.current_key == SDL_BUTTON) {
        
    }
}