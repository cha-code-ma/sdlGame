#ifndef OBJECT_POOLS_H
#define OBJECT_POOLS_H


button_pool *button_pool_init(int capacity);
void free_button_pool(button_pool *pool);


//object
object_pool *sub_object_pool_init(int capacity);

void free_object_pool(object_pool *pool);

//sub_object


void free_sub_object_pool(sub_object_pool *pool, bool is_pointer);

bool sub_object_pool_add(sub_object_pool* pool, sub_object* sub_obj);

object **object_pool_get_objects(object_pool *pool, int *count);

bool values_in_list_int(int * list, int value, int length);

button **button_pool_get_objects(button_pool *pool, int *count);
sub_object **sub_object_pool_get_objects(sub_object_pool *pool, int *count);
#endif


