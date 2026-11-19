#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "object_pools.h"
#include "group.h"

void update_level_actions(game_t *game) {
    level *lvl = game->state.active_level;
    action_pool **all_actions;
    int length;
    bool debug = pool_get_objects(lvl->actions, all_actions, POOL_TYPES_ACTION, &length);
    if (!debug) return;

    for (int i = 0; i < length; i++) {
        update_action_trigger(game, all_actions[i]);
    }
}

void update_action_trigger(game_t *game, group_action *action) {
    switch (action->trigger) {
        case TRIGGER_ALWAYS_ACTIVE:
            update_group(action);
            break;
        case TRIGGER_KEY_ACTIVATE_PER_FRAME:
            if ((SDL_Scancode *)action->trigger_information == game->IO.current_key) {
                update_group(action);
            }
            break;

        case TRIGGER_KEY_ACTIVATE_ONCE:
            update_group(action);
            action->trigger = TRIGGER_NOT_ACTIVE;
            break;


        case TRIGGER_KEY_ACTIVATE_WITH_COOLDOWN:
                //For trigger_information2: [0] is current time,
                //[1] is total cooldown time,
                //[2] is int boolean wether already triggered or not in curtime
            if ((SDL_Scancode *)action->trigger_information == game->IO.current_key &&
                ((int *)action->trigger_information2)[0] - game->state.dt < 0 &&
                ((int *)action->trigger_information2)[2] == 1) {
                update_group(action);
                ((int *)action->trigger_information2)[0] = ((int *)action->trigger_information2)[1];
                ((int *)action->trigger_information2)[2] = 0;
            } else {
                if (((int *)action->trigger_information2)[0] - game->state.dt < 0) {
                    ((int *)action->trigger_information2)[0] = ((int *)action->trigger_information2)[1];
                    ((int *)action->trigger_information2)[2] = 1;
                }
                ((int *)action->trigger_information2)[0] -= game->state.dt;
            }
            break;

        case TRIGGER_ACTIVATE_PER_TIME_UNIT:
            //[0] is current time, [1] is total time_unit
            if (((int *)action->trigger_information2)[0] - game->state.dt < 0) {
                update_group(action);
                ((int *)action->trigger_information2)[0] = ((int *)action->trigger_information2)[1];
            } else {
                ((int *)action->trigger_information2)[0] -= game->state.dt;
            }
            break;

        case TRIGGER_REPEAT_ACTIVE_TIMEFRAME:
            if (((int *)action->trigger_information2)[0] - game->state.dt > 0) {
                update_group(action);
                ((int *)action->trigger_information2)[0] -= game->state.dt;
            } else {
                action->trigger = TRIGGER_NOT_ACTIVE;
            }

            break;

    }
}

void update_group(group_action * action) {

}