/*

*/

#ifndef BUTTON_H
#define BUTTON_H
#include "structs.h"
#include "sub_object.h"

#include "object.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

button *button_init(vec2 pos, vec2 size, SDL_Color color,char *text, bool centered_text,
    bool scaled_position,
    vec2 text_offset, bool scaled_size, vec2 text_size, SDL_Color text_color);

void free_button(button *but);


bool button_clicked(button* but, float mouse_x, float mouse_y);

bool button_hovered(button *but);

void activate_button(button* but);
void update_level_buttons(game_t *game_ptr);
void update_menu_buttons(game_t *game_ptr);
#endif