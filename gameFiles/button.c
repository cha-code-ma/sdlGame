/*

*/
#include "structs.h"
#include "sub_object.h"

#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "object_pools.h"
#include "logic.h"
#include <SDL3_ttf/SDL_ttf.h>


button *button_init(button_type type, vec2 pos, vec2 size, SDL_Color color,SDL_Color second_color, char *name, int name_length, int name_capacity, char * text, bool centered_text, bool scaled_position,
    vec2 text_offset, bool scaled_size, vec2 text_size, SDL_Color text_color,TTF_Font *font, int text_length, int text_capacity, group_action **group_actions, int group_act_amount, int group_act_capacity) {
    button *but = malloc(sizeof(button));
    but->color = color;
    but->second_color = second_color;
    but->position = pos;
    but->size = size;
    but->details = NULL;



    but->action_info = calloc(1, sizeof(button_action_info));
    if (!but->action_info) {
        free_button(but);
        return NULL;

    }
    but->action_info->action_count = group_act_amount;
    but->action_info->action_capacity = group_act_capacity;
    but->action_info->group_actions = calloc(group_act_capacity, sizeof(button_action_info*));
    if (!but->action_info->group_actions) {
        free_button(but);
        return NULL;
    }
    for (int i = 0; i < group_act_amount; i++) {
        but->action_info->group_actions[i] = group_actions[i];
    }

    if (name) {
        but->name = malloc(sizeof(string));
        if (!but->name->text) {
            free_button(but);
            return NULL;
        }
        but->name->text = malloc(sizeof(char) * name_capacity);
        if (!but->name->text) {
            free_string(but->text_info.text);
            free_button(but);
            return NULL;
        }
        strcpy(but->name->text, name);
        but->name->length = name_length;
        but->name->capacity = name_capacity;
    }
    if (text) {
        but->text_info.text = malloc(sizeof(string));
        if (!but->text_info.text) {
            free_button(but);
            return NULL;
        }
        but->text_info.text->text = malloc(sizeof(char) * text_capacity);
        if (!but->text_info.text->text) {
            free_button(but);
            return NULL;
        }
        but->text_info.text->font = font;
        but->text_info.text->color = text_color;

        but->text_info.text_centered_bool = centered_text;
        but->text_info.text_offset = text_offset;
        but->text_info.text_size = text_size;
        but->text_info.text_pos_scaled_bool = scaled_position;
        but->text_info.text_size_scaled_bool = scaled_size;

    }
}

void free_button(button *but) {
    free_sub_object_pool(but->details, true);
    free_string(but->name);
    free_string(but->text_info.text); 
    free(but);
}


bool check_button_clicked(button* but, float mouse_x, float mouse_y) {
    if (but->position.x <= mouse_x && but->position.x + but->size.x >= mouse_x &&
        but->position.y < mouse_y && but->position.y + but->size.y >= mouse_y) {
            activate_button(but);
        }
}

bool button_hovered(button *but);

void activate_button(button* but) {
    group_action *cur_action = but->action_info->group_actions;
    if (cur_action->custom_action) {
        cur_action->custom_action(cur_action->group_id);
        return;
    }
    switch (cur_action->action) {
    case ACTION_TYPE_HIDE:

        break;

    }
}

void check_buttons(game *game_ptr, float mouse_x, float mouse_y) {
    if (!game_ptr->state.active_level->UI->buttons) {
        return;
    }
    button_pool *buttons =game_ptr->state.active_level->UI->buttons;
    for (int i = 0; i < buttons->capacity; i++) {
        if (buttons->buttons[i]) {
            if (buttons->buttons[i]->active && buttons->buttons[i]->visible) {
                check_button_clicked(buttons->buttons[i], mouse_x, mouse_y);
            }
        }

    }
}