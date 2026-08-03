#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "structs.h"
#include <stdbool.h>
#include "object.h"
#include "object_list.h"


void show_sub_object(sub_object *obj, SDL_Renderer *renderer) {
    if (obj->obj_shape == SQUARE) {
        SDL_SetRenderDrawColor(renderer, obj->color.r, obj->color.g, obj->color.b, obj->color.a);
		SDL_FRect rect = {
			obj->future_position.x,
			obj->future_position.y,
			obj->future_size.x,
			obj->future_size.y
		};
		SDL_RenderFillRect(renderer, &rect);
		return;
    }
    else if (obj->obj_shape == TEXTURE) {
		if (!obj->texture) {
			return NULL;
		}
		SDL_Texture *texture = obj->info_texture->texture;
		SDL_FRect rect =
    }

}