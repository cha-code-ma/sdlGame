/*

*/
#include "structs.h"
#include "sub_object.h"
#include "object_list.h"

object *object_init(vec2 position, vec2 size, float visible_time, bool time_started) {
    object * obj = malloc(sizeof(object));
    if (!obj) {
        free_object(obj);
        return NULL;
    }
    memset(obj, 0, sizeof(object));
    obj->transform.position = position;
    obj->transform.future_position = position;
    obj->transform.size = size;
    obj->transform.future_position = size;
    obj->sub_objects.count = 0;
    obj->sub_objects.sub_objects = NULL;
    obj->total_visible_time_remaining = visible_time;
    obj->time_started = time_started;

    return obj;
}

void free_object(object *obj) {
    int amount_sub_objects = obj->sub_objects.count;
    sub_object * cur_sub_obj;
    for (int i = 0; i < amount_sub_objects; i++) {
        cur_sub_obj = obj->sub_objects.sub_objects[i];
        free_sub_object(cur_sub_obj);
    }
    free(obj);
}