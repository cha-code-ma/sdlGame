/*
	object.c functions of object.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include "sub_object.h"
#include "object_list.h"
#include  "structs.h"




sub_object* sub_obj_init(
	SDL_Renderer *renderer,
	object_type my_shape,
	behaviour_type behaviour,
	vec2 offset,
	bool centered_pos,
	bool abs_pixel_size,
	vec2 size,
	SDL_Color color,
	layer obj_layer,
	mask obj_mask,
	bool visible,
	bool collision,
	int fixed_transform_length,
	bool fixed_size_bool,
	float *fixed_size_list_x,
	float *fixed_size_list_y,
	float *time_list_size,
	bool fixed_positions_bool,
	float *fixed_position_list_x,
	float *fixed_position_list_y,
	float *time_list_position,
	float *fixed_rotation_list,
	char *img_text,
	int points,
	float stay_time,
	float texture_rotation,
	float time_visible,
	int animation_length,
	float *animation_x_offset_list,
	float *animation_y_offset_list,
	float *animation_x_size_list,
	float *animation_y_size_list,
	float *animation_time_list,
	float *animation_rot_list,
	int * order_animation
) {
	sub_object* sub_obj = malloc(sizeof(sub_object));
	if (!sub_obj) {
		return NULL;
	}
	memset(sub_obj, 0, sizeof(sub_object));



	if (behaviour == BEHAVIOUR_TYPE_FIXED_TRANSFORM) {
		sub_obj->fixed_transform_lists = malloc(sizeof(values_list));
		if (!sub_obj->fixed_transform_lists) {
			free_sub_object(sub_obj);
			return NULL;
		}
		if (fixed_size_bool) {

			sub_obj->fixed_transform_lists->size.x = malloc(sizeof(float) * fixed_transform_length);
			sub_obj->fixed_transform_lists->size.y = malloc(sizeof(float) * fixed_transform_length);
			if (!sub_obj->fixed_transform_lists->size.x || !sub_obj->fixed_transform_lists->size.y) {
				free_sub_object(sub_obj);
				return NULL;
			}
			memcpy(sub_obj->fixed_transform_lists->size.x, fixed_size_list_x, sizeof(float) * fixed_transform_length);
			memcpy(sub_obj->fixed_transform_lists->size.y, fixed_size_list_y, sizeof(float) * fixed_transform_length);
		}
		if (fixed_positions_bool) {
			sub_obj->fixed_transform_lists->pos.x = malloc(sizeof(float) * fixed_transform_length);
			sub_obj->fixed_transform_lists->pos.y = malloc(sizeof(float) * fixed_transform_length);
			if (!sub_obj->fixed_transform_lists->pos.x || !sub_obj->fixed_transform_lists->pos.y) {
				free_sub_object(sub_obj);
				return NULL;
			}
			memcpy(sub_obj->fixed_transform_lists->pos.x, fixed_position_list_x, sizeof(float) * fixed_transform_length);
			memcpy(sub_obj->fixed_transform_lists->pos.y, fixed_position_list_y, sizeof(float) * fixed_transform_length);
		}
	} else {
		sub_obj->fixed_transform_lists = NULL;
	}

	if (behaviour == BEHAVIOUR_TYPE_ANIMATION) {
		sub_obj->animation = malloc(sizeof(animation_data));
		if (!sub_obj->animation) {
			free_sub_object(sub_obj);
			return NULL;
		}
		sub_obj->animation->amount_frames_animation = animation_length;
		sub_obj->animation->animation = true;
		sub_obj->animation->current_frame = 0;
		sub_obj->animation->lists.pos.x = malloc(sizeof(float) * animation_length);
		sub_obj->animation->lists.pos.y = malloc(sizeof(float) * animation_length);
		sub_obj->animation->lists.size.x = malloc(sizeof(float) * animation_length);
		sub_obj->animation->lists.size.y = malloc(sizeof(float) * animation_length);
		sub_obj->animation->lists.r_list = malloc(sizeof(float) * animation_length);
		sub_obj->animation->lists.t_list = malloc(sizeof(float) * animation_length);
		sub_obj->animation->order_animation = malloc(sizeof(int) * animation_length);
		if (!sub_obj->animation->lists.pos.x || !sub_obj->animation->lists.pos.y || !sub_obj->animation->lists.size.x
		|| !sub_obj->animation->lists.size.y|| !sub_obj->animation->lists.r_list || !sub_obj->animation->lists.t_list) {
				free_sub_object(sub_obj);
				return NULL;
			}
		memcpy(sub_obj->animation->lists.pos.x, animation_x_offset_list, sizeof(float) * animation_length);
		memcpy(sub_obj->animation->lists.pos.y, animation_y_offset_list, sizeof(float) * animation_length);
		memcpy(sub_obj->animation->lists.size.x, animation_x_size_list, sizeof(float) * animation_length);
		memcpy(sub_obj->animation->lists.size.y, animation_y_size_list, sizeof(float) * animation_length);
		memcpy(sub_obj->animation->lists.r_list, animation_rot_list, sizeof(float) * animation_length);
		memcpy(sub_obj->animation->lists.t_list, animation_time_list, sizeof(float) * animation_length);
		memcpy(sub_obj->animation->order_animation, order_animation, sizeof(int) * animation_length);

	} else{
		sub_obj->animation = NULL;
	}

	if (img_text) {
		SDL_Texture *texture = IMG_LoadTexture(renderer, img_text);
		sub_obj->info_texture = malloc(sizeof(texture_info));
		if (!sub_obj->info_texture) {
			free_sub_object(sub_obj);
			return NULL;
		}

		sub_obj->info_texture->texture = texture;
		sub_obj->info_texture->original_heigth = texture->h;
		sub_obj->info_texture->original_width = texture->w;
	} else {
		sub_obj->info_texture = NULL;
	}
	sub_obj->behaviour_type = behaviour;
	sub_obj->obj_shape = my_shape;
	sub_obj->offset = offset;
	sub_obj->size_info.size = size;

	sub_obj->size_info.future_size = size;
	sub_obj->state = IDLE;
	sub_obj->color = color;
	sub_obj->visible = visible;
	sub_obj->obj_mask = obj_mask;
	sub_obj->obj_layer = obj_layer;
	sub_obj->points = points;
	return sub_obj;
}


void free_sub_object(sub_object* sub_obj) {
    if (!sub_obj) {
        return;
    }

    if (sub_obj->fixed_transform_lists) {

        if (sub_obj->fixed_transform_lists->size.x) {
            free(sub_obj->fixed_transform_lists->size.x);
            sub_obj->fixed_transform_lists->size.x = NULL;
        }
        if (sub_obj->fixed_transform_lists->size.y) {
            free(sub_obj->fixed_transform_lists->size.y);
            sub_obj->fixed_transform_lists->size.y = NULL;
        }

        if (sub_obj->fixed_transform_lists->pos.x) {
            free(sub_obj->fixed_transform_lists->pos.x);
            sub_obj->fixed_transform_lists->pos.x = NULL;
        }
        if (sub_obj->fixed_transform_lists->pos.y) {
            free(sub_obj->fixed_transform_lists->pos.y);
            sub_obj->fixed_transform_lists->pos.y = NULL;
        }


        if (sub_obj->fixed_transform_lists->r_list) {
            free(sub_obj->fixed_transform_lists->r_list);
            sub_obj->fixed_transform_lists->r_list = NULL;
        }

        free(sub_obj->fixed_transform_lists);
        sub_obj->fixed_transform_lists = NULL;
    }

    if (sub_obj->animation) {

        if (sub_obj->animation->lists.pos.x) {
            free(sub_obj->animation->lists.pos.x);
            sub_obj->animation->lists.pos.x = NULL;
        }
        if (sub_obj->animation->lists.pos.y) {
            free(sub_obj->animation->lists.pos.y);
            sub_obj->animation->lists.pos.y = NULL;
        }

        if (sub_obj->animation->lists.size.x) {
            free(sub_obj->animation->lists.size.x);
            sub_obj->animation->lists.size.x = NULL;
        }
        if (sub_obj->animation->lists.size.y) {
            free(sub_obj->animation->lists.size.y);
            sub_obj->animation->lists.size.y = NULL;
        }


        if (sub_obj->animation->lists.r_list) {
            free(sub_obj->animation->lists.r_list);
            sub_obj->animation->lists.r_list = NULL;
        }

        if (sub_obj->animation->lists.t_list) {
            free(sub_obj->animation->lists.t_list);
            sub_obj->animation->lists.t_list = NULL;
        }

        if (sub_obj->animation->order_animation) {
            free(sub_obj->animation->order_animation);
            sub_obj->animation->order_animation = NULL;
        }

        free(sub_obj->animation);
        sub_obj->animation = NULL;
    }

    if (sub_obj->info_texture) {
        if (sub_obj->info_texture->texture) {
            SDL_DestroyTexture(sub_obj->info_texture->texture);
            sub_obj->info_texture->texture = NULL;
        }

        free(sub_obj->info_texture);
        sub_obj->info_texture = NULL;
    }

    free(sub_obj);
}