#ifndef LOGIC_H
#define LOGIC_H
#include "structs.h"
/*
    calculates render rectangle for all possible formats.
*/
SDL_FRect calc_rect_general(
    vec2 pos,
    vec2 size,
    bool parent,
    bool centered,
    bool size_scaled,
    bool position_scaled,
    vec2 parent_pos,
    vec2 parent_size);

#endif