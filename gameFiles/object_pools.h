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
#endif