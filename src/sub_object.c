/*
	object.c functions of object.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include "sub_object.h"

#include  "structs.h"




sub_object* sub_obj_init(
	sub_object_type type,
	vec2 offset,
	bool centered_pos,
	bool abs_pixel_size,
	vec2 size,
	SDL_Color color,
	bool visible,
	bool collision,
	SDL_Texture *texture,
	int points,
	float stay_time,
	float texture_rotation,
	float *time_visible,
	bool animation,
	int animation_length,
	float *animation_rot_list,
	int * order_animation,
	float *animation_time_list

) {
	sub_object* sub_obj = calloc(1, sizeof(sub_object));
	if (!sub_obj) return NULL;



	if (animation) {
	sub_obj->animation = malloc(sizeof(animation_data));
	if (!sub_obj->animation) {
		free_sub_object(sub_obj);
		return NULL;
	}
	sub_obj->animation->amount_frames_animation = animation_length;
	sub_obj->animation->animation = true;
	sub_obj->animation->frame_time_list = malloc(sizeof(float) * animation_length);
	sub_obj->animation->rotation_list = malloc(sizeof(float) * animation_length);
	sub_obj->animation->order_animation = malloc(sizeof(int) * animation_length);
	if (!sub_obj->animation->frame_time_list || !sub_obj->animation->rotation_list || !sub_obj->animation->order_animation) {
			free_sub_object(sub_obj);
			return NULL;
		}

	memcpy(sub_obj->animation->frame_time_list, animation_time_list, sizeof(float) * animation_length);
	memcpy(sub_obj->animation->rotation_list, animation_rot_list, sizeof(float) * animation_length);
	memcpy(sub_obj->animation->order_animation, order_animation, sizeof(int) * animation_length);
	}

	sub_obj->texture = texture;

	sub_obj->type = type;
	sub_obj->offset = offset;
	sub_obj->size_info.size = size;

	sub_obj->size_info.future_size = size;
	sub_obj->state = IDLE;
	sub_obj->color = color;
	sub_obj->visible = visible;
	sub_obj->points = points;
	return sub_obj;
}


void free_sub_object(sub_object* sub_obj) { //not done
    if (!sub_obj) {
        return;
    }





	if (sub_obj->animation->rotation_list) {
		free(sub_obj->animation->rotation_list);

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