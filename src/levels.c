#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "object_pools.h"
#include "object.h"
#include "sub_object.h"
#include "logic.h"
SDL_Color red = {255, 0, 0, 255};
SDL_Color blue = {0, 0, 255, 255};
level *init_level_1(void) {
    level *lvl = calloc(1, sizeof(level));
    if (!lvl) return NULL;
    SDL_Log("level calloc succesfull");
    bool debug;
    object_pool *o_pool = pool_init(3, POOL_TYPES_OBJECT);
    SDL_Log("pool init succesfull");
    if (!o_pool) return NULL;
    object *obj1 = object_init(SQUARE, BEHAVIOUR_TYPE_FIXED_TRANSFORM, (vec2){500, 500}, (vec2){30, 30},
     5, false, NULL, 0, 0, (sub_object_pool *)pool_init(2, POOL_TYPES_SUB_OBJECT), 1,
     true, 3,
     object_create_lists(create_list_float(3, 5.0f, 50.0f, 30.0f),
     create_list_float(3, 50.0f, 30.0f, 10.0f),
    create_list_float_to_Uint64(3, 3.0f, 5.0f, 4.0f), 3),
    true, 4,
     object_create_lists(create_list_float(4, 10.0f, 50.0f, 100.0f, 200.0f),
     create_list_float(4, 10.0f, 50.0f, 100.0f, 200.0f),
     create_list_float_to_Uint64(4, 3.0f, 5.0f, 4.0f, 2.0f), 4));


    if (!obj1) return NULL;
    SDL_Log("object init succesfull");
    sub_object *sub_obj1 = sub_obj_init(SUB_OBJECT_TYPE_PRIMARY_TEXTURE,
        (vec2){0, 0}, false, false, (vec2){1, 1}, red, true, true, NULL, 5, 10, 0, NULL, false, 0, NULL, NULL, NULL);
    if (!sub_obj1) return NULL;
    SDL_Log("subobject innit succesfull");
    debug = object_add_sub_object(obj1, sub_obj1);
    if (!debug) return NULL;
    //add sub_objects...
    SDL_Log("add sub_objects to object");

    debug = pool_add(o_pool, obj1, POOL_TYPES_OBJECT);
        if (!debug) return NULL;
        SDL_Log("add object to object_pool");
    lvl->objects =  o_pool;
    SDL_Log("add objectpool to level object pool");
    return lvl;
}

