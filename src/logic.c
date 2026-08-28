#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "structs.h"
#include <stdbool.h>
#include "sub_object.h"
#include "object_pools.h"
#include "SDL2/SDL_ttf.h"

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

SDL_Rect calc_rect(object* obj, sub_object *sub_obj) {
		SDL_Log("In function calc_rect");
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
		SDL_Rect rect = {
			.h = (int)h,
			.w = (int)w,
			.x = (int)x,
			.y = (int)y,
		};
	return rect;
}

void show_sub_object(object* obj,sub_object *sub_obj, SDL_Renderer *renderer) {
	SDL_Log("show_sub_object function");
	SDL_Rect *rect = malloc(sizeof(SDL_Rect));
	if (!rect) return;
	*rect = calc_rect(obj, sub_obj);
	SDL_Log("sub_obj rect: h: %d, w: %d, x: %d, y: %d", rect->h, rect->w, rect->x, rect->y);
	//SDL_Log("position is calculated");
    if (!sub_obj->texture) {
		//SDL_Log("show rectangle");
        SDL_SetRenderDrawColor(renderer, sub_obj->color.r, sub_obj->color.g, sub_obj->color.b, sub_obj->color.a);
		if (!rect) {
			SDL_Log("rect is NULL!");
			return;
		}
		if (rect->w <= 0 || rect->h <= 0) {
			SDL_Log("rect has invalid size: %dx%d", rect->w, rect->h);
			return;
		}
		int debug = SDL_RenderFillRect(renderer, rect);
		if (!debug) {
			SDL_Log("cant show sub_obj: %s", SDL_GetError());
			return;
		}

    }
    else  {
		if (!sub_obj->texture) return;
		SDL_Texture *texture = sub_obj->info_texture->texture;
		SDL_RenderCopy(renderer, sub_obj->info_texture->texture, NULL, rect);
    }

}

void show_object(object *obj, SDL_Renderer *renderer) {
	//SDL_Log("show_object function");
	for (int i = 0; i < obj->sub_objects->capacity; i++) {
		if (obj->sub_objects->objects[i]) {
			//SDL_Log("sub_object found");
			if (obj->sub_objects->objects[i]->visible) {
				//SDL_Log("sub object visible");
				show_sub_object(obj, obj->sub_objects->objects[i], renderer);
			}
		}
	}
}

void show_obj_pool(object_pool *obj_p, SDL_Renderer *renderer) {
	//SDL_Log("show_object_pool function started");
	for (int i = 0; i < obj_p->capacity; i++) {
		if (obj_p->objects[i]) {
			//SDL_Log("valid object found");
			show_object(obj_p->objects[i], renderer);
		}
	}
}

void free_game_textures(game_t *game_p) {
	if (game_p->textures.circle_yellow) {
		SDL_DestroyTexture(game_p->textures.circle_yellow);
	}

}


SDL_Rect calc_rect_general(
    vec2 pos,
    vec2 size,
    bool parent,
    bool centered,
    bool size_scaled,
    bool position_scaled,
    vec2 parent_pos,
    vec2 parent_size) {
	SDL_Rect rect;
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
void show_button(button *but, SDL_Renderer *renderer) {
	SDL_Rect rect =
	{.h = but->size.y,
	 .w = but->size.x,
	 .x = but->position.x,
	 .y = but->position.y,

	};
	SDL_SetRenderDrawColor(renderer, but->color.r, but->color.g, but->color.b, but->color.a);
	SDL_RenderFillRect(renderer, &rect);

	text_info_t text_inf = but->text_info;
	SDL_Rect text_rect = calc_rect_general(text_inf.text_offset, text_inf.text_size,
	true, text_inf.text_centered_bool, text_inf.text_pos_scaled_bool, text_inf.text_pos_scaled_bool, but->position,
	but->size);
	SDL_Surface *txt_surface = TTF_RenderText_Solid(text_inf.text->font, text_inf.text->text, text_inf.text->color);
	SDL_Texture *txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);
	SDL_FreeSurface(txt_surface);
	SDL_RenderCopy(renderer, txt_texture, NULL, &text_rect);
	SDL_DestroyTexture(txt_texture);
}
bool game_textures_init(game_t *game_p, SDL_Renderer *renderer) {
	if (!game_p) return false;

	game_p->textures.circle_yellow = IMG_LoadTexture(renderer, "media/character_poppetje.png");
	if (!game_p->textures.circle_yellow) {
		free_game_textures(game_p);
		return false;
	}

	return true;
}



//text:

void show_text_ui(text_ui *ui_text, SDL_Renderer *renderer) {
	if (!ui_text) {
		return;
	}

	if (!ui_text->transparant_background) {
		SDL_Rect background_rect = {
			.h = (int)ui_text->size.y,
			.w = (int)ui_text->size.x,
			.x = (int)ui_text->pos.x,
			.y = (int)ui_text->pos.y,
		};

	SDL_SetRenderDrawColor(renderer, ui_text->background_color.r, ui_text->background_color.g, ui_text->background_color.b, ui_text->background_color.a);
	SDL_RenderFillRect(renderer, &background_rect);
	}

	SDL_Rect text_rect = {
			.h =(int)ui_text->size.y,
			.w = (int)ui_text->size.x,
			.x = (int)ui_text->pos.x,
			.y = (int)ui_text->pos.y,
		};

	SDL_Surface *txt_surface = TTF_RenderText_Solid(ui_text->text->font, ui_text->text->text, ui_text->text->color);
	SDL_Texture *txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);
	SDL_RenderCopy(renderer, txt_texture, NULL, &text_rect);
	SDL_DestroyTexture(txt_texture);
}