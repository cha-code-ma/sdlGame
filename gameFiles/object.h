/*

*/


#ifndef OBJECT_H
#define OBJECT_H
#include "structs.h"



object *object_init(vec2 position, vec2 size, float visible_time, bool time_started);


void free_object(object *obj);

void free_string(string *str);
#endif