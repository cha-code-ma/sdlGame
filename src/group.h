#ifndef GROUP_H
#define GROUP_H


#include "structs.h"
#include "object_pools.h"


void free_group(group_t *group, bool with_objects, bool with_ui);

group_t *group_init(object_pool *obj_pool, ui_t *ui, char *text, int text_length, int text_capacity);

void free_group_action(group_action *group_act, bool with_group);
/*
    header needed for actions: "actions.h"
    Possible group actions:

*/
group_action *group_action_init(group_t *group, action_type action, bool is_active, void (*custom_action)(group_t *group));

void group_action_hide(group_t *group, bool with_objects, bool with_UI);



void group_action_show(group_t *group, bool with_objects, bool with_UI);

void group_action_invert_visibility(group_t *group, bool with_objects, bool with_UI);






#endif