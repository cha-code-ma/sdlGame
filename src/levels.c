#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "object_pools.h"
#include "object.h"
#include "sub_object.h"
#include "logic.h"
level *init_level_1(void) {
    level *lvl = calloc(1, sizeof(level));
    if (!lvl) return NULL;
    bool debug;
    object_pool *o_pool = pool_init( 3, POOL_TYPES_OBJECT);
    if (!o_pool) return NULL;
    object *obj1 = object_init(SQUARE, BEHAVIOUR_TYPE_NONE, (vec2){400, 200}, (vec2){100, 100}, 5, false, NULL, 0, 0, (sub_object_pool *)pool_init(2, POOL_TYPES_SUB_OBJECT), 1, 0, 0, false, NULL, NULL, NULL, false, NULL, NULL, NULL);
    if (!obj1) return NULL;
    sub_object *sub_obj1 = sub_obj_init(SUB_OBJECT_TYPE_PRIMARY_TEXTURE,
        (vec2){0, 0}, false, false, (vec2){1, 1}, red, true, true, NULL, 5, 10, 0, NULL, false, 0, NULL, NULL, NULL);
    if (!sub_obj1) return NULL;
    debug = object_add_sub_object(obj1, sub_obj1);
    if (!debug) return NULL;
    //add sub_objects...

    debug = pool_add(o_pool, obj1, POOL_TYPES_OBJECT);
        if (!debug) return NULL;
    lvl->objects =  o_pool;
    return lvl;
}

