/*

*/

#ifndef BUTTON_H
#define BUTTON_H
#include "structs.h"
#include "sub_object.h"
#include "object_list.h"
#include "object.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

button *button_init(vec2 pos, vec2 size, SDL_Color color,char *text, bool centered_text,
    bool scaled_position,
    vec2 text_offset, bool scaled_size, vec2 text_size, SDL_Color text_color);

void free_button(button *but);

#endif