/*

*/
#include "structs.h"
#include "sub_object.h"

#include "object_pools.h"
object *object_init(object_type type, vec2 position, vec2 size, float visible_time, bool time_started, char *text, int length, int text_capacity, sub_object_pool* sub_objects) {
    object * obj = malloc(sizeof(object));
    if (!obj) {
        free_object(obj);
        return NULL;
    }
    memset(obj, 0, sizeof(object));
    obj->type = type;
    obj->sub_objects = sub_objects;
    obj->transform.position = position;
    obj->transform.future_position = position;
    obj->transform.size = size;
    obj->transform.future_position = size;
    obj->total_visible_time_remaining = visible_time;
    obj->time_started = time_started;
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

void free_object(object *obj) {
    free_string(obj->name);
    free_sub_object_pool(&obj->sub_objects, false);
    free(obj);
}