/*

*/
#include "structs.h"
#include "sub_object.h"
#include "object_list.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

button *button_init(vec2 pos, vec2 size, SDL_Color color,char *text, bool centered_text, bool scaled_position,
    vec2 text_offset, bool scaled_size, vec2 text_size, SDL_Color text_color) {
    button *but = malloc(sizeof(button));
    but->color = color;
    but->position = pos;
    but->size = size;
    but->details = NULL;
    but->text_info.text = text;
    but->text_info.text_centered_bool = centered_text;
    but->text_info.text_color = text_color;
    but->text_info.text_offset = text_offset;
    but->text_info.text_size = text_size;
    but->text_info.text_pos_scaled_bool = scaled_position;
    but->text_info.text_size_scaled_bool = scaled_size;
}

void free_button(button *but) {
    free_sub_object_pool(but->details);
    free(but);
}