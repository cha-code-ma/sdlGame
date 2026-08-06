#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "structs.h"
#include <stdbool.h>
#include "object.h"
#include "object_list.h"

struct sub_object {
	vec2 offset;
	bool centered_pos;
	size_type size_type;
	object_type obj_shape;
	all_states state;
	fixed_movement *obj_fixed_movement;
	bool visible;
	SDL_Color color;
	animation_data *animation;
	mask obj_mask;
	layer obj_layer;
	SDL_Texture *texture;
	texture_info *info_texture;
	int points;
	float texture_rotation;
	float visible_time_remaining;
};

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
	for (int i = 0; i < len(obj->sub_objects); i++) {
		if (obj->sub_objects[i]->visible) {
		show_sub_object(obj, obj->sub_objects[i], renderer);
		}
	}
}

void show_object_list(object_list *list, SDL_Renderer * renderer) {
	node *cur_node = list->start_node;
	for (int i = 1; i < len(list->count); i++) {
		show_object(cur_node->sub_obj, renderer);
		cur_node = cur_node->next;
	}
}