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

button *button_init(button_type type, vec2 pos, vec2 size, SDL_Color color,char *name, int name_length, int name_capacity, char * text, bool centered_text, bool scaled_position,
    vec2 text_offset, bool scaled_size, vec2 text_size, SDL_Color text_color, int text_length, int text_capacity) {
    button *but = malloc(sizeof(button));
    but->color = color;
    but->position = pos;
    but->size = size;
    but->details = NULL;
        but->type = type;
    if (name) {
        but->name = malloc(sizeof(string));
        if (!but->name->text) {
            return NULL;
        }
        but->name->text = malloc(sizeof(char) * name_capacity);
        if (!but->name->text) {
            free_string(but->text_info.text);
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
        but->text_info.text_centered_bool = centered_text;
        but->text_info.text_color = text_color;
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