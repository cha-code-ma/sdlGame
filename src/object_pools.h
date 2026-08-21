#ifndef OBJECT_POOLS_H
#define OBJECT_POOLS_H






//object




//sub_object




void *pool_init(int capacity, pool_types type);
bool pool_add(void *pool, void *insert_object, pool_types type);
bool pool_remove_rand(void *pool, void *return_object, pool_types type);
bool pool_get_objects(void *pool, void **return_objects , pool_types type, int *length);
bool values_in_list_int(int * list, int value, int length);

void free_button_pool(button_pool *pool);
void free_object_pool(object_pool *pool);
void free_ui_t(ui_t *ui, bool with_objects, bool with_buttons);
void free_sub_object_pool(sub_object_pool *pool, bool is_pointer);
#endif


