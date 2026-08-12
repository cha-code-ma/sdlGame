
#include "sub_object.h"

#include "object.h"
#include "button.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
//button
button_pool *button_pool_init(int capacity) {
    button_pool* pool = malloc(sizeof(button_pool));
    pool->capacity = capacity;
    pool->count = 0;
    pool->free_count = 0;
    pool->free_list = malloc(sizeof(int) * capacity);
    pool->buttons = NULL;
    pool->free_count = capacity;
}

void free_button_pool(button_pool *pool, bool is_pointer) {
    if (!pool) {
        return;
    }
    if (!pool->buttons) {
        free(pool);
        return;
    }
    for (int i = 0; i < pool->count; i++) {
        if (values_in_list_int(pool->free_list, i, pool->free_count)) {
            free_button(pool->buttons[i]);
        }
    }
    if (is_pointer) {
        free(pool);
    }

}

button **button_pool_get_objects(button_pool *pool, int *count) {
    button **buttons = malloc(sizeof(button*) * pool->count);
    if (!buttons) {
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < pool->capacity; i++) {
        if (pool->buttons[i]) {
            buttons[index] = pool->buttons[i];
            index++;
        }
    }
    *count = index;
    return buttons;
}

//object
object_pool *sub_object_pool_init(int capacity) {
    object_pool* pool = malloc(sizeof(object_pool));
    pool->capacity = capacity;
    pool->count = 0;
    pool->free_count = 0;
    pool->free_list = malloc(sizeof(int) * capacity);
    pool->objects = NULL;
    pool->free_count = capacity;
}

void free_object_pool(object_pool *pool, bool is_pointer) {
    if (!pool) {
        return;
    }
    if (!pool->objects) {
        free(pool);
        return;
    }
    for (int i = 0; i < pool->count; i++) {
        if (values_in_list_int(pool->free_list, i, pool->free_count)) {
            free_sub_object(pool->objects[i]);
        }
    }
    if (is_pointer) {
        free(pool);
    }

}

object *object_pool_remove_rand(object_pool* pool) {
    if (!pool || pool->count == 0 ) {
        return NULL;
    }
    object *sub_obj = NULL;
    for (int i = 0; i < pool->capacity; i++) {
        if (!values_in_list_int(i, pool->free_list, pool->capacity)) {
            sub_obj = pool->objects[i];
            pool->objects[i] = NULL;
            pool->count--;
            pool->free_list[pool->free_count] = i;
            pool->free_count++;
            break;
        }
    }
    return sub_obj;
}


object *object_pool_remove_name(object_pool* pool,  string name) {
    if (!pool || pool->count == 0 ) {
        return NULL;
    }
    object *sub_obj = NULL;
    for (int i = 0; i < pool->capacity; i++) {
        if (strcmp(pool->objects[i]->name->text, name.text)) {
            sub_obj = pool->objects[i];
            pool->objects[i] = NULL;
            pool->count--;
            pool->free_list[pool->free_count] = i;
            pool->free_count++;
            break;
        }
    }
    return sub_obj;
}

object **object_pool_get_objects(object_pool *pool, int *count) {
    object **objects = malloc(sizeof(object*) * pool->count);
    if (!objects) {
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < pool->capacity; i++) {
        if (pool->objects[i]) {
            objects[index] = pool->objects[i];
            index++;
        }
    }
    *count = index;
    return objects;
}

//sub_object
object *sub_object_pool_remove_type(object_pool* pool,  object_type type) {
    if (!pool || pool->count == 0 ) {
        return NULL;
    }
    object *obj = NULL;
    for (int i = 0; i < pool->capacity; i++) {
        if (pool->objects[i]->type == type) {
            obj = pool->objects[i];
            pool->objects[i] = NULL;
            pool->count--;
            pool->free_list[pool->free_count] = i;
            pool->free_count++;
            break;
        }
    }
    return obj;
}

sub_object_pool *sub_object_pool_init(int capacity) {
    sub_object_pool* pool = malloc(sizeof(sub_object));
    pool->capacity = capacity;
    pool->count = 0;
    pool->free_count = 0;
    pool->free_list = malloc(sizeof(int) * capacity);
    pool->objects = NULL;
    pool->free_count = capacity;
}

void free_sub_object_pool(sub_object_pool *pool, bool is_pointer) {
    if (!pool) {
        return;
    }
    if (!pool->objects) {
        free(pool);
        return;
    }
    for (int i = 0; i < pool->count; i++) {
        if (values_in_list_int(pool->free_list, i, pool->free_count)) {
            free_object(pool->objects[i]);
        }
    }
    if (is_pointer) {
        free(pool);
    }
}

bool sub_object_pool_add(sub_object_pool* pool, sub_object* sub_obj) {
    if (!pool || !sub_obj || pool->free_count == 0 ) {
        return false;
    }
    int place = pop_free_list_sub_obj(pool);
    pool->objects[place] = sub_obj;

    return true;
}

sub_object *sub_object_pool_remove_rand(sub_object_pool* pool) {
    if (!pool || pool->count == 0 ) {
        return NULL;
    }
    sub_object *sub_obj = NULL;
    for (int i = 0; i < pool->capacity; i++) {
        if (!values_in_list_int(i, pool->free_list, pool->capacity)) {
            sub_obj = pool->objects[i];
            pool->objects[i] = NULL;
            pool->count--;
            pool->free_list[pool->free_count] = i;
            pool->free_count++;
            break;
        }
    }
    return sub_obj;
}

sub_object *sub_object_pool_remove_type(sub_object_pool* pool,  sub_object_type type) {
    if (!pool || pool->count == 0 ) {
        return NULL;
    }
    sub_object *sub_obj = NULL;
    for (int i = 0; i < pool->capacity; i++) {
        if (pool->objects[i]->type == type) {
            sub_obj = pool->objects[i];
            pool->objects[i] = NULL;
            pool->count--;
            pool->free_list[pool->free_count] = i;
            pool->free_count++;
            break;
        }
    }
    return sub_obj;
}


int pop_free_list_sub_obj(sub_object_pool* pool) {
    int first = pool->free_list[0];
    pool->free_count++;

    for (int i = 1; i < pool->free_count; i++) {
        pool->free_list[i-1] = pool->free_list[i];
    }
    pool->count--;
    return first;
}

sub_object **sub_object_pool_get_objects(sub_object_pool *pool, int *count) {
    sub_object **sub_objects = malloc(sizeof(sub_object*) * pool->count);
    if (!sub_objects) {
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < pool->capacity; i++) {
        if (pool->objects[i]) {
            sub_objects[index] = pool->objects[i];
            index++;
        }
    }
    *count = index;
    return sub_objects;
}

/*
    unsorted list, speed O(n)
*/
bool values_in_list_int(int * list, int value, int length) {
    for (int i =0; i < length; i++) {
        if (list[i] == value) {
            return true;
        }
    }
    return false;
}

