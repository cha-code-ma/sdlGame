/*

*/
#include "structs.h"
#include "sub_object.h"
#include <stdarg.h>
#include "object_pools.h"

void free_string(string *str) {
    if (str) {
    if (str->text) {
        free(str->text);
    }
    free(str);
    }

}
void free_object(object *obj) { //not done
    free_string(obj->name);
    free_sub_object_pool(obj->sub_objects, false);
    free(obj);
}

float *create_list_float(int count, ...) {
    float *array = malloc(sizeof(float) * count);
    if (!array) {
        SDL_Log("func create_list_Uint: malloc fails");
        return NULL;
    }
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        array[i] = (float)va_arg(args, double);
    }
    va_end(args);
    return array;
}

Uint64 *create_list_float_to_Uint64(int count, ...) {
    Uint64 *array = malloc(sizeof(Uint64) * count);
    if (!array) {
        SDL_Log("func create_list_float: malloc fails");
        return NULL;
    }
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        array[i] = (Uint64)((float)va_arg(args, double) * 1000.0f);
    }
    va_end(args);
    return array;
}





void **object_create_lists(float *x_list, float *y_list, Uint64 *t_list, int length) {
    void **arr = malloc(sizeof(void *) * 3);
    if (!arr) return NULL;
    SDL_Log("malloc double pointer succes");
    arr[0] = x_list;
    arr[1] = y_list;
    arr[2] = t_list;
    return arr;
}

object *object_init(object_type type, behaviour_type behaviour, vec2 position,
    vec2 size, float visible_time, bool time_started,
    char *text, int length,
    int text_capacity,
    sub_object_pool* sub_objects,
    int sub_objects_count,
	bool fixed_size_bool,
    int fixed_size_length,
    void **size_values_list,
	bool fixed_positions_bool,
    int fixed_pos_length,
	void **pos_values_list
) {
    object * obj = calloc(1, sizeof(object));
    if (!obj) {
        free_object(obj);
        return NULL;
    }
    obj->behaviour = behaviour;
    obj->type = type;
    obj->sub_objects = sub_objects;
    obj->transform.position = position;
    obj->transform.future_position = position;
    obj->transform.size = size;
    obj->transform.future_size = size;
    obj->transform.future_size = size;
    obj->total_visible_time_remaining = visible_time;
    obj->time_started = time_started;
    if (fixed_size_bool || fixed_positions_bool) {
        obj->fixed_transform_lists = calloc(1, sizeof(values_list));
        if (!obj->fixed_transform_lists) {
            free_object(obj);
            return NULL;
        }
    }
    if (fixed_size_bool) {
        SDL_Log("fixed_size set start");
        if (fixed_size_length <= 0) {
            SDL_Log("object_int: invalid input, fixed_size_length");
            return NULL;
        }
        obj->fixed_transform_lists->size = malloc(sizeof(fixed_tempelate_list));
        if (!obj->fixed_transform_lists->size) {
            free_object(obj);
            return NULL;
        }

        obj->fixed_transform_lists->size->fixed_list.x = malloc(sizeof(float) * fixed_size_length);
        obj->fixed_transform_lists->size->fixed_list.y = malloc(sizeof(float) * fixed_size_length);
        obj->fixed_transform_lists->size->time_list = malloc(sizeof(Uint64) * fixed_size_length);
        if (!obj->fixed_transform_lists->size->fixed_list.x  || !obj->fixed_transform_lists->size->fixed_list.y|| !obj->fixed_transform_lists->size->time_list) {
            free_object(obj);
            return NULL;
        }

        memcpy(obj->fixed_transform_lists->size->fixed_list.x , (float *)size_values_list[0], sizeof(float) * fixed_size_length);
        memcpy(obj->fixed_transform_lists->size->fixed_list.y, (float *)size_values_list[1], sizeof(float) * fixed_size_length);
        memcpy(obj->fixed_transform_lists->size->time_list, (Uint64 *)size_values_list[2], sizeof(Uint64) * fixed_size_length);

        obj->fixed_transform_lists->size->index = 0;

        obj->fixed_transform_lists->size->time_left = obj->fixed_transform_lists->size->time_list[0];
        SDL_Log("time_left set");
        obj->fixed_transform_lists->size->length = fixed_size_length;
        SDL_Log("size length set");
        obj->transform.size = (vec2){obj->fixed_transform_lists->size->fixed_list.x[0],
        obj->fixed_transform_lists->size->fixed_list.y[0]};
        SDL_Log("fixed_size set finished");
    }
    if (fixed_positions_bool) {
        if (fixed_pos_length <= 0) {
            SDL_Log("object_int: invalid input, fixed_pos_length");
            return NULL;
        }
        obj->fixed_transform_lists->pos = malloc(sizeof(fixed_tempelate_list));
        if (!obj->fixed_transform_lists->pos) {
            free_object(obj);
            return NULL;
        }

        obj->fixed_transform_lists->pos->fixed_list.x = malloc(sizeof(float) * fixed_pos_length);
        obj->fixed_transform_lists->pos->fixed_list.y = malloc(sizeof(float) * fixed_pos_length);
        obj->fixed_transform_lists->pos->time_list = malloc(sizeof(Uint64) * fixed_pos_length);
        if (!obj->fixed_transform_lists->pos->fixed_list.x  || !obj->fixed_transform_lists->pos->fixed_list.y|| !obj->fixed_transform_lists->pos->time_list) {
            free_object(obj);
            return NULL;
        }
        memcpy(obj->fixed_transform_lists->pos->fixed_list.x , (float *)pos_values_list[0], sizeof(float) * fixed_pos_length);
        memcpy(obj->fixed_transform_lists->pos->fixed_list.y, (float *)pos_values_list[1], sizeof(float) * fixed_pos_length);
        memcpy(obj->fixed_transform_lists->pos->time_list, (Uint64 *)pos_values_list[2], sizeof(Uint64) * fixed_pos_length);
        obj->fixed_transform_lists->pos->index = 0;
        obj->fixed_transform_lists->pos->time_left = obj->fixed_transform_lists->pos->time_list[0];
        obj->fixed_transform_lists->pos->length = fixed_pos_length;
        obj->transform.position = (vec2){obj->fixed_transform_lists->pos->fixed_list.x[0],
        obj->fixed_transform_lists->pos->fixed_list.y[0]};

    }
    SDL_Log("object_init finsihed");

    if (text) {
        obj->name->text = malloc(sizeof(char) * text_capacity);
        strcpy(obj->name->text, text);
        obj->name->length = length;
        obj->name->capacity = text_capacity;
    } else {
        obj->name = NULL;
    }

    return obj;
}





void object_click_action(object *obj) {
    
}

bool object_add_sub_object(object *obj, sub_object *sub_obj) {
    SDL_Log("boject_add_sub_object function started");
    bool debug = pool_add(obj->sub_objects, sub_obj, POOL_TYPES_SUB_OBJECT);
    SDL_Log("debug: ");
    return debug;
}