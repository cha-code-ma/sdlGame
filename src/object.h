/*

*/


#ifndef OBJECT_H
#define OBJECT_H
#include "structs.h"



object *object_init(object_type type, behaviour_type behaviour, vec2 position,
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
);

void free_object(object *obj);

void free_string(string *str);


void object_click_action(object *obj);
bool object_add_sub_object(object *obj, sub_object *sub_obj);
#endif