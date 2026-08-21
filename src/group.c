#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "object_pools.h"

group_t *group_init(object *obj_pool, ui_t *ui, char *text, int text_length, int text_capacity) {
    group_t *group = malloc(sizeof(group_t));
    if (!group) {
        return NULL;
    }
    group->name = calloc(1, sizeof(string));
    if (!group->name) {
        free_group(group, false, false);
        return NULL;
    }
    if (text) {
        group->name->text = malloc(sizeof(char) * text_capacity);
        if (!group->name->text) {
            free_group(group, false, false);
            return NULL;
        }
        strcpy(group->name->text, text);
        group->name->font = NULL;
        group->name->length = text_length;
        group->name->capacity = text_capacity;
    }
    group->objects = obj_pool;
    group->ui = ui;
    return group;
}

void free_group(group_t *group, bool with_objects, bool with_ui) {
    if (!group) {
        return;
    }
    if (group->name) {
        if (group->name->text) {
            free(group->name->text);
        }
        free(group->name);
    }
    if (with_objects) {
        free_object_pool(group->objects);
    }
    if (with_ui) {
        free_ui_t(group->ui, true, true);
    }
    free(group);
}


group_action *group_action_init(group_t *group, action_type action, bool is_active, void (*custom_action)(group_t *group)) {
    group_action *group_act = calloc(1, sizeof(group_action));
    if (!group_act) {
        free_group_action(group_act, false);
        return NULL;
    }
    group_act->action = action;
    group_act->custom_action = custom_action;
    group_act->group_id = group;
    group_act->is_active = is_active;
    return group_act;
}

void free_group_action(group_action *group_act, bool with_group) {
    if (!group_act) {
        return;
    }
    if (with_group) {
        free_group(group_act->group_id, false, false);
    }
    free(group_act);
}

void group_action_hide(group_t *group, bool with_objects, bool with_UI) {
    if (!group || !group->objects) {
        return;
    }
    int count;
    if (with_objects) {
        object **objects = object_pool_get_objects(group->objects, &count);
        if (!objects) {
            return;
        }
        for (int i = 0; i < count; i++) {
            int sub_count;
            sub_object **sub_objects = sub_object_pool_get_objects(objects[i]->sub_objects, &sub_count);
            for (int j = 0; j < sub_count; j++) {
                sub_objects[j]->visible = false;
            }
        }
    }
    if (with_UI) {
        int ui_count;
        object **ui_objects = object_pool_get_objects(group->ui->ui_objects, &ui_count);
        if (!ui_objects) {
            return;
        }
        for (int i = 0; i < ui_count; i++) {
            int sub_count;
            sub_object **sub_objects = sub_object_pool_get_objects(ui_objects[i]->sub_objects, &sub_count);
            for (int j = 0; j < sub_count; j++) {
                sub_objects[j]->visible = false;
            }
        }
        button **buttons = button_pool_get_objects(group->ui->buttons, &ui_count);
        if (!buttons) {
            return;
        }
        for (int i = 0; i < ui_count; i ++) {
            buttons[i]->visible = false;
        }
    }
}

void group_action_show(group_t *group, bool with_objects, bool with_UI) {
    if (!group || !group->objects) {
        return;
    }
    int count;
    if (with_objects) {
        object **objects = object_pool_get_objects(group->objects, &count);
        if (!objects) {
            return;
        }
        for (int i = 0; i < count; i++) {
            int sub_count;
            sub_object **sub_objects = sub_object_pool_get_objects(objects[i]->sub_objects, &sub_count);
            for (int j = 0; j < sub_count; j++) {
                sub_objects[j]->visible = true;
            }
        }
    }
    if (with_UI) {
        int ui_count;
        object **ui_objects = object_pool_get_objects(group->ui->ui_objects, &ui_count);
        if (!ui_objects) {
            return;
        }
        for (int i = 0; i < ui_count; i++) {
            int sub_count;
            sub_object **sub_objects = sub_object_pool_get_objects(ui_objects[i]->sub_objects, &sub_count);
            for (int j = 0; j < sub_count; j++) {
                sub_objects[j]->visible = true;
            }
        }
        button **buttons = button_pool_get_objects(group->ui->buttons, &ui_count);
        if (!buttons) {
            return;
        }
        for (int i = 0; i < ui_count; i ++) {
            buttons[i]->visible = true;
        }
    }
}

void group_action_invert_visibility(group_t *group, bool with_objects, bool with_UI) {
    if (!group || !group->objects) {
        return;
    }
    int count;
    if (with_objects) {
        object **objects = object_pool_get_objects(group->objects, &count);
        if (!objects) {
            return;
        }
        for (int i = 0; i < count; i++) {
            int sub_count;
            sub_object **sub_objects = sub_object_pool_get_objects(objects[i]->sub_objects, &sub_count);
            for (int j = 0; j < sub_count; j++) {
                sub_objects[j]->visible = !sub_objects[j]->visible;
            }
        }
    }
    if (with_UI) {
        int ui_count;
        object **ui_objects = object_pool_get_objects(group->ui->ui_objects, &ui_count);
        if (!ui_objects) {
            return;
        }
        for (int i = 0; i < ui_count; i++) {
            int sub_count;
            sub_object **sub_objects = sub_object_pool_get_objects(ui_objects[i]->sub_objects, &sub_count);
            for (int j = 0; j < sub_count; j++) {
                sub_objects[j]->visible = !sub_objects[j]->visible ;
            }
        }
        button **buttons = button_pool_get_objects(group->ui->buttons, &ui_count);
        if (!buttons) {
            return;
        }
        for (int i = 0; i < ui_count; i ++) {
            buttons[i]->visible = !buttons[i]->visible;
        }
    }
}