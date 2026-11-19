
#include "sub_object.h"

#include "object.h"
#include "button.h"
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

bool values_in_list_int(int * list, int value, int length) {
    for (int i =0; i < length; i++) {
        if (list[i] == value) {
            SDL_Log("value in list found!");
            return true;
        }
    }
    return false;
}


int *remove_value_list_int(int *list, int value, int *list_length, int *pool_count) {
    for (int i = 0; i < *list_length; i ++) {
        if (list[i] == value) {
            if (*list_length == 1) {
                free(list);
                list = NULL;
                return NULL;
            }
            int *temp = malloc(sizeof(int) * ((*list_length)-1));
            for (int j = 0; j < *list_length-1; j++) {
                if (i != j) {
                    temp[j] = list[j];
                } else continue;
            }
            (*list_length)--;
            (*pool_count)++;
            return temp;


            return NULL;
        }
    }
}


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

void *pool_init(int capacity, pool_types type) {
    switch (type) {
        case POOL_TYPES_BUTTON:
            button_pool *b_pool = calloc(1, sizeof(button_pool));
            if (!b_pool) return NULL;
            b_pool->buttons = calloc(capacity, sizeof(button*));
            if(!b_pool->buttons) return NULL;
            b_pool->capacity = capacity;
            b_pool->free_count = capacity;
            b_pool->free_list = malloc(sizeof(int) * capacity);
            for (int i = 1; i < b_pool->capacity + 1; i++) {
                b_pool->free_list[i-1] = i;
            }
            return b_pool;

        case POOL_TYPES_OBJECT:
            object_pool *o_pool = calloc(1, sizeof(object_pool));
            if (!o_pool) return NULL;
            o_pool->objects = calloc(capacity, sizeof(object*));
            if (!o_pool->objects) return NULL;
            o_pool->capacity = capacity;
            o_pool->free_count = capacity;
            o_pool->free_list = malloc(sizeof(int) * capacity);
            for (int i = 1; i < o_pool->capacity + 1; i++) {
                o_pool->free_list[i-1] = i;
            }
            return o_pool;


        case POOL_TYPES_SUB_OBJECT:
            sub_object_pool *s_pool = calloc(1, sizeof(sub_object_pool));
            if (!s_pool) return NULL;
            s_pool->objects = calloc(capacity, sizeof(sub_object*));
            if (!s_pool->objects) return NULL;
            s_pool->capacity = capacity;
            s_pool->free_count = capacity;
            s_pool->free_list = malloc(sizeof(int) * capacity);
            for (int i = 1; i < s_pool->capacity + 1; i++) {
                s_pool->free_list[i-1] = i;
            }
            return s_pool;

        case POOL_TYPES_TEXT_UI:
            text_ui_pool *t_pool = calloc(1, sizeof(text_ui_pool));
            if (!t_pool) return NULL;
            t_pool->strings = calloc(capacity, sizeof(text_ui*));
            if (!t_pool->strings) return NULL;
            t_pool->capacity = capacity;
            t_pool->free_count = capacity;
            t_pool->free_list = malloc(sizeof(int) * capacity);
            for (int i = 1; i < t_pool->capacity + 1; i++) {
                t_pool->free_list[i-1] = i;
            }
            return t_pool;

        case POOL_TYPES_ACTION:
            action_pool *a_pool = calloc(1, sizeof(action_pool));
            if (!a_pool) return NULL;
            a_pool->actions = calloc(capacity, sizeof(text_ui*));
            if (!a_pool->actions) return NULL;
            a_pool->capacity = capacity;
            a_pool->free_count = capacity;
            a_pool->free_list = malloc(sizeof(int) * capacity);
            for (int i = 1; i < a_pool->capacity + 1; i++) {
                a_pool->free_list[i-1] = i;
            }
            return a_pool;
    }
}


bool pool_get_free_index(void *pool, pool_types type, int *value) {
    switch (type) {
        case POOL_TYPES_BUTTON:
            button_pool *b_pool = (button_pool *)pool;
            for (int i = 0; i < b_pool->capacity; i++) {
                if (values_in_list_int(b_pool->free_list, i, b_pool->free_count)) {
                    b_pool->free_list = remove_value_list_int(b_pool->free_list, i, &b_pool->free_count, &b_pool->count);
                    *value = i;
                    return true;
                }
            }

        case POOL_TYPES_OBJECT:
            object_pool *o_pool = (object_pool *)pool;
            for (int i = 0; i < o_pool->capacity; i++) {
                if (values_in_list_int(o_pool->free_list, i, o_pool->free_count)) {
                    o_pool->free_list = remove_value_list_int(o_pool->free_list, i, &o_pool->free_count, &o_pool->count);
                    *value = i;
                    return true;
                }
            }

        case POOL_TYPES_SUB_OBJECT:
            sub_object_pool *s_pool = (sub_object_pool *)pool;
            for (int i = 0; i < s_pool->capacity; i++) {
                if (values_in_list_int(s_pool->free_list, i, s_pool->free_count)) {
                    s_pool->free_list = remove_value_list_int(s_pool->free_list, i, &s_pool->free_count, &s_pool->count);
                    *value = i;
                    return true;
                }
            }

        case POOL_TYPES_TEXT_UI:
            text_ui_pool *t_pool = (text_ui_pool *)pool;
            for (int i = 0; i < t_pool->capacity; i++) {
                if (values_in_list_int(t_pool->free_list, i, t_pool->free_count)) {
                    t_pool->free_list = remove_value_list_int(t_pool->free_list, i, &t_pool->free_count, &t_pool->count);
                    *value = i;
                    return true;
                }
            }
        case POOL_TYPES_ACTION:
            action_pool *a_pool = (action_pool *)pool;
            for (int i = 0; i < a_pool->capacity; i++) {
                if (values_in_list_int(a_pool->free_list, i, a_pool->free_count)) {
                    a_pool->free_list = remove_value_list_int(a_pool->free_list, i, &a_pool->free_count, &t_pool->count);
                    *value = i;
                    return true;
                }
            }
    }
    return false;
}

bool pool_add(void *pool, void *insert_object, pool_types type) {
    int free_index;
    bool possible;
    switch (type) {
        case POOL_TYPES_BUTTON:
            button_pool *b_pool = (button_pool *)pool;
            button *but = (button *)insert_object;
            if (b_pool->capacity == 0) return false;

            possible = pool_get_free_index(b_pool, POOL_TYPES_BUTTON, &free_index);
            if (!possible) return false;
            b_pool->buttons[free_index] = but;
            return true;


        case POOL_TYPES_OBJECT:
            object_pool *o_pool = (object_pool *)pool;
            object *obj = (object *)insert_object;
            if (o_pool->capacity == 0) return false;

            possible = pool_get_free_index(o_pool, POOL_TYPES_OBJECT, &free_index);
            if (!possible) return false;
            o_pool->objects[free_index] = obj;
            return true;

        case POOL_TYPES_SUB_OBJECT:
            sub_object_pool *s_pool = (sub_object_pool *)pool;
            sub_object *sub_obj = (sub_object *)insert_object;
            if (s_pool->capacity == 0) return false;
            free_index= 0;
            possible = pool_get_free_index(s_pool, POOL_TYPES_SUB_OBJECT, &free_index);
            if (!possible) return false;

            if (free_index >= s_pool->capacity) {

                return false;
            }
            s_pool->objects[free_index] = sub_obj;

            return true;

        case POOL_TYPES_TEXT_UI:
            text_ui_pool *t_pool = (text_ui_pool *)pool;
            text_ui *ui_text = (text_ui *)insert_object;
            if (t_pool->capacity == 0) return false;
            free_index= 0;
            possible = pool_get_free_index(t_pool, POOL_TYPES_TEXT_UI, &free_index);
            if (!possible) return false;
            t_pool->strings[free_index] = ui_text;
            return true;
        case POOL_TYPES_ACTION:
            action_pool *a_pool = (action_pool *)pool;
            group_action *action = (group_action *)insert_object;
            if (a_pool->capacity == 0) return false;
            free_index= 0;
            possible = pool_get_free_index(a_pool, POOL_TYPES_ACTION, &free_index);
            if (!possible) return false;
            a_pool->actions[free_index] = action;
            return true;
    }

}




/*
    unsorted list, speed O(n)
*/


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

/*
    type decids input and output:
    -POOL_TYPES_BUTTON -> button **
    -POOL_TYPES_OBJECT -> object **
    -POOL_TYPES_SUB_OBJECT -> sub_object **
    -POOL_TYPES_TEXT_UI -> text_ui **

    dont malloc return_objects
*/
bool pool_get_objects(void *pool, void ***return_objects , pool_types type, int *length) {
    int index;

    switch (type) {
        case POOL_TYPES_BUTTON:
            button_pool *b_pool = (button_pool *)pool;
            button **buttons = malloc(sizeof(button*) * b_pool->count);
            if (!buttons) return false;

            index = 0;
            for (int i = 0; i < b_pool->capacity; i++) {
                if (b_pool->buttons[i]) {
                    buttons[index] = b_pool->buttons[i];
                    index++;
                }
            }
            *return_objects = (void **)buttons;
            *length = index;
            return true;

        case POOL_TYPES_OBJECT:
            object_pool *o_pool = (object_pool *)pool;
            object **objects = malloc(sizeof(object*) * o_pool->count);
            if (!objects) return false;

            index = 0;
            for (int i = 0; i < o_pool->capacity; i++) {
                if (o_pool->objects[i]) {
                    objects[index] = o_pool->objects[i];
                    index++;
                }
            }
            *return_objects = (void **)objects;
            *length = index;
            return true;
        case POOL_TYPES_SUB_OBJECT:
            sub_object_pool *s_pool = (sub_object_pool *)pool;
            sub_object **sub_obj = malloc(sizeof(sub_object*) * s_pool->count);
            if (!sub_obj) return false;

            index = 0;
            for (int i = 0; i < s_pool->capacity; i++) {
                if (s_pool->objects[i]) {
                    sub_obj[index] = s_pool->objects[i];
                    index++;
                }
            }
            *return_objects = (void **)sub_obj;
            *length = index;
            return true;

        case POOL_TYPES_TEXT_UI:
            text_ui_pool *t_pool = (text_ui_pool *)pool;
            text_ui **ui_text = malloc(sizeof(text_ui*) * t_pool->count);
            if (!ui_text) return false;

            index = 0;
            for (int i = 0; i < t_pool->capacity; i++) {
                if (t_pool->strings[i]) {
                    ui_text[index] = t_pool->strings[i];
                    index++;
                }
            }
            *return_objects = (void **)ui_text;
            *length = index;
            return true;
    }
}


//object

void free_object_pool(object_pool *pool, bool is_pointer) {
    if (!pool) {
        return;
    }
    if (!pool->objects) {
        free(pool);
        return;
    }
    object **objects;
    int count = 0;
    bool debug = pool_get_objects(pool, (void ***)&objects, POOL_TYPES_OBJECT, &count);
    if (!debug) return;
    for (int i = 0; i < count; i++) {
        if (values_in_list_int(pool->free_list, i, pool->free_count)) {
            free_object(objects[i]);
        }
    }
    if (is_pointer) {
        free(pool);
    }

}




bool pool_remove_rand(void *pool, void *return_object, pool_types type) {
   int length;
    switch (type) {
        case POOL_TYPES_BUTTON:
            button_pool *b_pool = (button_pool *)pool;
            button *but = (button *)return_object;
            if (b_pool->capacity == 0 || b_pool->capacity == b_pool->free_count) return false;
            length = b_pool->free_count;
            for (int i = 0; i < b_pool->capacity; i++) {

                if (!values_in_list_int(b_pool->free_list, i, length)) {
                    but = b_pool->buttons[i];
                    int *temp = realloc(b_pool->free_list, sizeof(int) * (length + 1));
                    if (!temp) return false;
                    b_pool->free_list = temp;
                    b_pool->free_list[length] = i;
                    b_pool->count--;
                    b_pool->free_count++;
                    return true;

                }
            }

            return false;

        case POOL_TYPES_OBJECT:
            object_pool *o_pool = (object_pool *)pool;
            object *obj = (object *)return_object;
            if (o_pool->capacity == 0 || o_pool->capacity == o_pool->free_count) return false;
            length = o_pool->free_count;
            for (int i = 0; i < o_pool->capacity; i++) {

                if (!values_in_list_int(o_pool->free_list, i, length)) {
                    obj = o_pool->objects[i];
                    int *temp = realloc(o_pool->free_list, sizeof(int) * (length + 1));
                    if (!temp) return false;

                    o_pool->free_list = temp;
                    o_pool->free_list[length] = i;
                    o_pool->count--;
                    o_pool->free_count++;
                    return true;

                }
            }

            return false;

        case POOL_TYPES_SUB_OBJECT:
            sub_object_pool *s_pool = (sub_object_pool *)pool;
            sub_object *sub_obj = (sub_object *)return_object;
            if (s_pool->capacity == 0 || s_pool->capacity == s_pool->free_count) return false;
            length = s_pool->free_count;
            for (int i = 0; i < s_pool->capacity; i++) {

                if (!values_in_list_int(s_pool->free_list, i, length)) {
                    sub_obj = s_pool->objects[i];
                    int *temp =realloc(s_pool->free_list, sizeof(int) * (length + 1));
                    if (!temp) return false;
                    s_pool->free_list[length] = i;
                    s_pool->free_list = temp;
                    s_pool->count--;
                    s_pool->free_count++;
                    return true;

                }
            }

            return false;

        case POOL_TYPES_TEXT_UI:
            text_ui_pool *t_pool = (text_ui_pool *)pool;
            text_ui *ui_text = (text_ui *)return_object;
            if (t_pool->capacity == 0 || t_pool->capacity == t_pool->free_count) return false;
            length = t_pool->free_count;
            for (int i = 0; i < t_pool->capacity; i++) {

                if (!values_in_list_int(t_pool->free_list, i, length)) {
                    ui_text = t_pool->strings[i];
                    int *temp = realloc(t_pool->free_list, sizeof(int) * (length + 1));
                    if (!temp) return false;
                    t_pool->free_list = temp;
                    t_pool->free_list[length] = i;
                    t_pool->count--;
                    t_pool->free_count++;
                    return true;

                }
            }

            return false;
    }
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



//sub_object
object *object_pool_remove_type(object_pool* pool,  object_type type) {
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
    if (!pool) return NULL;
    pool->objects = malloc (sizeof(object*) * capacity);
    if (!pool->objects) return NULL;
    pool->capacity = capacity;
    pool->count = 0;
    pool->free_count = 0;
    pool->free_list = malloc(sizeof(int) * capacity);

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
    int count;
    sub_object **sub_obj;
    bool debug = pool_get_objects(pool, (void ***)&sub_obj, POOL_TYPES_SUB_OBJECT, &count );
    if (!debug) return;
    for (int i = 0; i < count; i++) {

        if (values_in_list_int(pool->free_list, i, pool->free_count)) {
            free_sub_object(sub_obj[i]);
        }
    }
    if (is_pointer) {
        free(pool);
    }
}


sub_object *sub_object_pool_remove_rand(sub_object_pool* pool) {
    if (!pool || pool->count == 0 ) {
        return NULL;
    }
    sub_object *sub_obj = NULL;
    for (int i = 0; i < pool->capacity; i++) {
        if (!values_in_list_int(pool->free_list,i , pool->capacity)) {
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





//ui_t

ui_t *ui_t_init(object_pool *obj_pool, button_pool *but_pool) {
    ui_t *ui = malloc(sizeof(ui_t));
    if (!ui) {
        return NULL;
    }
    ui->buttons = but_pool;
    ui->ui_objects = obj_pool;
    return ui;
}

void free_ui_t(ui_t *ui, bool with_objects, bool with_buttons) {
    if (!ui) {
        return;
    }
    if (with_objects) {
        free_object_pool(ui->ui_objects, true);
    }
    if (with_buttons) {
        free_button_pool(ui->buttons, true);
    }
    free(ui);
}


//text_UI

text_ui_pool *text_ui_pool_init(int capacity) {
    text_ui_pool* pool = malloc(sizeof(text_ui_pool));
    pool->capacity = capacity;
    pool->count = 0;
    pool->free_count = 0;
    pool->free_list = malloc(sizeof(int) * capacity);
    pool->strings = NULL;
    pool->free_count = capacity;
}

void free_text_ui_pool(text_ui_pool *pool, bool is_pointer) {
    if (!pool) {
        return;
    }
    if (!pool->strings) {
        free(pool);
        return;
    }
    //not done
    if (is_pointer) {
        free(pool);
    }

}


