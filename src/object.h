/*

*/


#ifndef OBJECT_H
#define OBJECT_H
#include "structs.h"
void **object_create_lists(float *x_list, float *y_list, Uint64 *t_list, int length);
Uint64 *create_list_float_to_Uint64(int count, ...);
float *create_list_float(int count, ...);
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
);

void free_object(object *obj);

void free_string(string *str);


void object_click_action(object *obj);
bool object_add_sub_object(object *obj, sub_object *sub_obj);
#endif