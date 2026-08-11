# ifndef TEXT_UI_H
#define TEXT_UI_H
#include "structs.h"

text_ui *text_ui_init(vec2 pos, vec2 size, SDL_Color background_color,
                        char *source_text, int text_length, int text_capacity, SDL_Color text_color);

void free_text_ui(text_ui *ui_text);



#endif