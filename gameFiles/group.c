#include <stdio.h>
#include <stdlib.h>
#include <structs.h>
#include "object_pools.h"


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