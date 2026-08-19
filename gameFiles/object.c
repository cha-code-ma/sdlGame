/*

*/
#include "structs.h"
#include "sub_object.h"

#include "object_pools.h"
object *object_init(object_type type, vec2 position,
    vec2 size, float visible_time, bool time_started,
    char *text, int length,
    int text_capacity,
    sub_object_pool* sub_objects,
    int sub_objects_count,
    int fixed_size_length,
    int fixed_pos_length,
	bool fixed_size_bool,
	float *fixed_size_list_x,
	float *fixed_size_list_y,
	float *time_list_size,
	bool fixed_positions_bool,
	float *fixed_position_list_x,
	float *fixed_position_list_y,
	float *time_list_position
) {
    object * obj = calloc(1, sizeof(object));
    if (!obj) {
        free_object(obj);
        return NULL;
    }

    obj->type = type;
    obj->sub_objects = sub_objects;
    obj->transform.position = position;
    obj->transform.future_position = position;
    obj->transform.size = size;
    obj->transform.future_position = size;
    obj->total_visible_time_remaining = visible_time;
    obj->time_started = time_started;

    if (fixed_size_bool) {
        obj->fixed_transform_lists->size = malloc(sizeof(fixed_tempelate_list));
        if (!obj->fixed_transform_lists->size) {
            free_object(obj);
            return NULL;
        }

        obj->fixed_transform_lists->size->fixed_list.x = malloc(sizeof(float) * fixed_size_length);
        obj->fixed_transform_lists->size->fixed_list.y = malloc(sizeof(float) * fixed_size_length);
        obj->fixed_transform_lists->size->time_list = malloc(sizeof(float) * fixed_size_length);
        if (!obj->fixed_transform_lists->size->fixed_list.x || !obj->fixed_transform_lists->size->fixed_list.y  || !obj->fixed_transform_lists->size->time_list) {
            free_object(obj);
            return NULL;
        }
        memcpy(obj->fixed_transform_lists->size->fixed_list.x , fixed_size_list_x, sizeof(float) * fixed_size_length);
        memcpy(obj->fixed_transform_lists->size->fixed_list.y, fixed_size_list_y, sizeof(float) * fixed_size_length);
        memcpy(obj->fixed_transform_lists->size->time_list, time_list_size, sizeof(float) * fixed_size_length);
    }
    if (fixed_positions_bool) {

        obj->fixed_transform_lists->pos = malloc(sizeof(fixed_tempelate_list));
        if (!obj->fixed_transform_lists->pos) {
            free_object(obj);
            return NULL;
        }

        obj->fixed_transform_lists->pos->fixed_list.x = malloc(sizeof(float) * fixed_pos_length);
        obj->fixed_transform_lists->pos->fixed_list.y = malloc(sizeof(float) * fixed_pos_length);
        obj->fixed_transform_lists->pos->time_list = malloc(sizeof(float) * fixed_pos_length);
        if (!obj->fixed_transform_lists->pos->fixed_list.x  || !obj->fixed_transform_lists->pos->fixed_list.y|| !obj->fixed_transform_lists->pos->time_list) {
            free_object(obj);
            return NULL;
        }
        memcpy(obj->fixed_transform_lists->pos->fixed_list.x , fixed_position_list_x, sizeof(float) * fixed_pos_length);
        memcpy(obj->fixed_transform_lists->pos->fixed_list.y, fixed_position_list_y, sizeof(float) * fixed_pos_length);
        memcpy(obj->fixed_transform_lists->pos->time_list, time_list_position, sizeof(float) * fixed_pos_length);
    }


    if (text) {
        char * mal_text = malloc(sizeof(char) * text_capacity);
        strcpy(mal_text, text);
        obj->name->text = mal_text;
        obj->name->length = length;
        obj->name->capacity = text_capacity;
    } else {
        obj->name = NULL;
    }

    return obj;
}

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
    free_sub_object_pool(&obj->sub_objects, false);
    free(obj);
}

void object_click_action(object *obj) {
    
}