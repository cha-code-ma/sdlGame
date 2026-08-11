#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "structs.h"
#include <stdbool.h>
#include "sub_object.h"
#include "object_pools.h"
#include <SDL3_ttf/SDL_ttf.h>

vec2 calc_center(object *obj) {
	vec2 ret;
	ret.x = obj->transform.position.x + 0.5 * obj->transform.size.x;
	ret.y = obj->transform.position.y + 0.5 * obj->transform.size.y;
	return ret;
}
vec2 calc_future_center(object* obj) {
	vec2 ret;
	ret.x = obj->transform.future_position.x + 0.5 * obj->transform.future_size.x;
	ret.y = obj->transform.future_position.y + 0.5 * obj->transform.future_size.y;
	return ret;
}

SDL_FRect calc_rect(object* obj, sub_object *sub_obj) {
		float x;
		float y;
		float h;
		float w;
	if (sub_obj->size_info.size_type == SIZE_TYPE_SCALE) {
		h = sub_obj->size_info.future_size.y * obj->transform.future_size.y;
		w = sub_obj->size_info.future_size.x * obj->transform.future_size.x;
	} else if (sub_obj->size_info.size_type == SIZE_TYPE_ABS_SIZE) {
		h = sub_obj->size_info.future_size.y;
		w = sub_obj->size_info.future_size.x;
	}
	if (sub_obj->centered_pos) {
		x = calc_future_center(obj).x + sub_obj->offset.x;
		y = calc_future_center(obj).y + sub_obj->offset.y;
	} else {
		x = obj->transform.future_position.x + sub_obj->offset.x;
		y = obj->transform.future_position.y + sub_obj->offset.y;
	}
		SDL_FRect rect = {
			.h = h,
			.w = w,
			.x = x,
			.y = y,
		};
	return rect;
}

void show_sub_object(object* obj,sub_object *sub_obj, SDL_Renderer *renderer) {
	SDL_FRect rect = calc_rect(obj, sub_obj);
    if (sub_obj->obj_shape == SQUARE) {
        SDL_SetRenderDrawColor(renderer, sub_obj->color.r, sub_obj->color.g, sub_obj->color.b, sub_obj->color.a);

		SDL_RenderFillRect(renderer, &rect);
		return;
    }
    else if (sub_obj->obj_shape == TEXTURE) {
		if (!sub_obj->texture) {
			return NULL;
		}
		SDL_Texture *texture = sub_obj->info_texture->texture;
		SDL_RenderTexture(renderer, sub_obj->info_texture->texture, NULL, &rect);
    }

}

void show_object(object *obj, SDL_Renderer *renderer) {
	for (int i = 0; i < obj->sub_objects.capacity; i++) {
		if (!values_in_list_int(obj->sub_objects.free_list, i, obj->sub_objects.free_count)) {
			if (obj->sub_objects.objects[i]->visible) {
				show_sub_object(obj, obj->sub_objects.objects[i], renderer);
			}
		}
	}
}

void show_obj_pool(object_pool *obj_p, SDL_Renderer *renderer) {
	for (int i = 0; i < obj_p->capacity; i++) {
		if (!values_in_list_int(obj_p->free_list, i, obj_p->free_count)) {
			show_object(obj_p->objects[i], renderer);
		}
	}
}

void show_button(button *but, SDL_Renderer *renderer) {
	SDL_FRect rect =
	{.h = but->size.y,
	 .w = but->size.x,
	 .x = but->position.x,
	 .y = but->position.y,

	};
	SDL_SetRenderDrawColor(renderer, but->color.r, but->color.g, but->color.b, but->color.a);
	SDL_RenderRect(renderer, &rect);

	text_info_t text_inf = but->text_info;
	SDL_FRect text_rect = calc_rect_general(text_inf.text_offset, text_inf.text_size,
	true, text_inf.text_centered_bool, text_inf.text_pos_scaled_bool, text_inf.text_pos_scaled_bool, but->position,
	but->size);
	SDL_Surface *txt_surface = TTF_RenderText_Solid(text_inf.text->font, text_inf.text->text, text_inf.text->length, text_inf.text->color);
	SDL_Texture *txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);
	SDL_DestroySurface(txt_surface);
	SDL_RenderTexture(renderer, txt_texture, NULL, &text_rect);
	SDL_DestroyTexture(txt_texture);
}


SDL_FRect calc_rect_general(
    vec2 pos,
    vec2 size,
    bool parent,
    bool centered,
    bool size_scaled,
    bool position_scaled,
    vec2 parent_pos,
    vec2 parent_size) {
        SDL_FRect rect;
        if (parent) {
            if (size_scaled) {
                rect.h = parent_size.y * size.y;
                rect.w = parent_size.x * size.x;
            } else {
                rect.h = size.y;
                rect.w = size.x;
            }
            if (centered) {
                if (position_scaled) {
                    rect.x = parent_pos.x + 0.5*parent_size.x + pos.x * parent_size.x;
                    rect.y = parent_pos.y + 0.5*parent_size.y + pos.y * parent_size.y;
                } else {
                    rect.x = parent_pos.x + 0.5*parent_size.x + pos.x;
                    rect.x = parent_pos.y + 0.5*parent_size.y + pos.y;
                }
            } else {
                if (position_scaled) {
                    rect.x = parent_pos.x + 0.5*parent_size.x + pos.x * parent_size.x;
                    rect.y = parent_pos.y + 0.5*parent_size.y + pos.y * parent_size.y;
                } else {
                    rect.x = parent_pos.x + 0.5*parent_size.x + pos.x;
                    rect.x = parent_pos.y + 0.5*parent_size.y + pos.y;
                }
            }
        } else{
            rect.h = size.y;
            rect.w = size.x;
            rect.x = pos.x;
            rect.y = pos.y;
        }
        return rect;
    }

bool game_textures_init(game_textures *game_tex, SDL_Renderer *renderer) {
	if (!game_tex) {
		game_tex = malloc(sizeof(game_textures));
		if (!game_tex) {
			return false;
		}
	}
	SDL_Surface *surface = SDL_LoadSurface("media/character_poppetje.png");
	if (!surface) {
		free_game_textures(game_tex);
		return false;
	}
	game_tex->circle_yellow = SDL_CreateTextureFromSurface(renderer, surface);
	if (!game_tex->circle_yellow) {
		free_game_textures(game_tex);
		return false;
	}

	return true;
}

void free_game_textures(game_textures *game_tex) {
	if (game_tex->circle_yellow) {
		SDL_DestroyTexture(game_tex->circle_yellow);
	}




	free(game_tex);
}

//text:

void show_text_ui(text_ui *ui_text, SDL_Renderer *renderer) {
	if (!ui_text) {
		return;
	}

	if (!ui_text->transparant_background) {
		SDL_FRect background_rect = {
			.h = ui_text->size.y,
			.w = ui_text->size.x,
			.x = ui_text->pos.x,
			.y = ui_text->pos.y,
		};

	SDL_SetRenderDrawColor(renderer, ui_text->background_color.r, ui_text->background_color.g, ui_text->background_color.b, ui_text->background_color.a);
	SDL_RenderRect(renderer, &background_rect);
	}

	SDL_FRect text_rect = {
			.h = ui_text->size.y,
			.w = ui_text->size.x,
			.x = ui_text->pos.x,
			.y = ui_text->pos.y,
		};

	SDL_Surface *txt_surface = TTF_RenderText_Solid(ui_text->text->font, ui_text->text->text, ui_text->text->length, ui_text->text->color);
	SDL_Texture *txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);
	SDL_DestroySurface(txt_surface);
	SDL_RenderTexture(renderer, txt_texture, NULL, &text_rect);
	SDL_DestroyTexture(txt_texture);
}