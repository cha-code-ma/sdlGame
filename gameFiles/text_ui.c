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

text_ui *text_ui_init(vec2 pos, vec2 size, SDL_Color background_color,
                        char *source_text, int text_length, int text_capacity, SDL_Color text_color, TTF_Font *font) {
    text_ui *ui_text = malloc(sizeof(text_ui));
    if (!ui_text) {
        free_text_ui(ui_text);
        return NULL;
    }
    ui_text->pos = pos;
    ui_text->size = size;
    ui_text->background_color = background_color;
    ui_text->text = malloc(sizeof(string));
    if (!ui_text->text) {
        free_text_ui(ui_text);
        return NULL;
    }
    ui_text->text->text = malloc(sizeof(char) * text_capacity);
    if (!ui_text->text->text) {
        free_text_ui(ui_text);
    }
    strcpy(ui_text->text->text, source_text);
    ui_text->text->capacity = text_capacity;
    ui_text->text->length = text_length;
    ui_text->text->color = text_color;
    ui_text->text->font = font;

}

void free_text_ui(text_ui *ui_text) {
    if (!ui_text) {
        return;
    }
    if (ui_text->text) {
        if (ui_text->text->text) {
            free(ui_text->text->text);
        }

        free(ui_text);
    }
    free(ui_text);
}