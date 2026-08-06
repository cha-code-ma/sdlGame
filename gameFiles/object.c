/*
	object.c functions of object.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include "object.h"
#include "object_list.h"
#include  "structs.h"
SDL_Color red = { 255, 0, 0, 255 };
SDL_Color blue = { 0, 0, 255, 255 };


/*
	Initializes a struct shape pointer, inputs are obvious.

	Output:
	returns shape pointer is everything went well, otherwise NULL
*/
sub_object* obj_init(
	SDL_Renderer *renderer,
	object_type my_shape,
	float x_pos,
	float y_pos,
	float x_size,
	float y_size,
	float speed,
	bool animation,
	SDL_Color color,
	object_list* list_object,
	layer  obj_layer,
	mask obj_mask,
	bool visible,
	bool player,
	bool collision,
	int amount_frames_animation,
	bool fixed_movement_bool,
	float *size_list_x,
	float *size_list_y,
	float *time_list_size,
	bool fixed_positions_bool,
	float *position_list_x,
	float *position_list_y,
	float *time_list_position,
	char *img_text,
	SDL_Texture **obj_animation_textures,
	int points,
	float stay_time,
	float texture_scale

) {
	sub_object* s_p = malloc(sizeof(sub_object));
	if (!s_p) {
		return NULL;
	}
	int check = 1;
	node* n_p = node_init(s_p);


	if (!n_p) {
		free(s_p);
		return NULL;
	}
	check = node_insert(list_object, n_p);
	if (!check) {
		free(s_p);
		return NULL;
	}
		list_object->count++;

	if (fixed_movement_bool) {
		s_p->obj_fixed_movement = malloc(sizeof(fixed_movement));
		if (!s_p->obj_fixed_movement) {
			free_sub_object(s_p);
			return NULL;
		}
		s_p->obj_fixed_movement->list_size.x_list = size_list_x;
		s_p->obj_fixed_movement->list_size.y_list = size_list_y;
		s_p->obj_fixed_movement->list_size.t_list = time_list_size;
		if (fixed_positions_bool) {
			s_p->obj_fixed_movement->list_position = malloc(sizeof(position_list));
			if (!s_p->obj_fixed_movement->list_position) {
				free_sub_object(s_p);
				return NULL;
			}

			s_p->obj_fixed_movement->list_position->x_list = position_list_x;
			s_p->obj_fixed_movement->list_position->y_list = position_list_y;
			s_p->obj_fixed_movement->list_position->t_list = time_list_position;
		}
	} else {
		s_p->obj_fixed_movement = NULL;
	}

	if (animation) {
		s_p->animation = malloc(sizeof(animation_data));
		if (!s_p->animation) {
			free_sub_object(s_p);
			return NULL;
		}
		s_p->animation->amount_frames_animation = amount_frames_animation;
		s_p->animation->animation = animation;
		s_p->animation->animation_textures = obj_animation_textures;
		s_p->animation->current_frame = 0;
		s_p->animation->frame_time = amount_frames_animation;
	} else{
		s_p->animation = NULL;
	}

	if (img_text) {
		SDL_Texture *texture = IMG_LoadTexture(renderer, img_text);
		s_p->info_texture = malloc(sizeof(texture_info));
		s_p->info_texture->texture = texture;
		s_p->info_texture->original_heigth = texture->h;
		s_p->info_texture->original_width = texture->w;
	} else {
		s_p->info_texture = NULL;
	}

	s_p->obj_shape = my_shape;
	s_p->position.x = x_pos;
	s_p->position.y = y_pos;
	s_p->future_position.x = x_pos;
	s_p->future_position.y = y_pos;
	s_p->size.x = x_size;
	s_p->size.y = y_size;
	s_p->future_size.x = x_size;
	s_p->future_size.y = y_size;
	s_p->state = IDLE;
	s_p->color = color;
	s_p->visible = true;
	s_p->obj_mask = obj_mask;
	s_p->obj_layer = obj_layer;
	s_p->speed = speed;
	s_p->obj_fixed_movement->list_size.x_list = size_list_x;
	s_p->obj_fixed_movement->list_size.y_list = size_list_y;
	s_p->obj_fixed_movement->list_size.t_list = time_list_size;
	s_p->obj_fixed_movement->list_position->x_list = position_list_x;
	s_p->obj_fixed_movement->list_position->y_list = position_list_y;
	s_p->obj_fixed_movement->list_position->t_list = time_list_position;
	s_p->animation->amount_frames_animation = amount_frames_animation;
	s_p->animation->animation = animation;
	s_p->animation->animation_textures = obj_animation_textures;

	s_p->points = points;
	return s_p;
}

void free_sub_object(sub_object* obj) {
	if (obj->obj_fixed_movement) {
		if (obj->obj_fixed_movement->list_position) {
			free(obj->obj_fixed_movement->list_position);
		}
		free(obj->obj_fixed_movement);
	}
	if (obj->obj_fixed_movement) {
		if (obj->obj_fixed_movement->list_position) {
			if (obj->obj_fixed_movement->list_position->x_list) {
				free(obj->obj_fixed_movement->list_position->x_list);
			}
			if(obj->obj_fixed_movement->list_position->y_list) {
				free(obj->obj_fixed_movement->list_position->y_list);
			}
			if (obj->obj_fixed_movement->list_position->t_list) {
				free(obj->obj_fixed_movement->list_position->t_list);
			}
			free(obj->obj_fixed_movement->list_position);
		}
		if (obj->obj_fixed_movement->list_size.x_list) {
			free(obj->obj_fixed_movement->list_size.x_list);
		}
		if (obj->obj_fixed_movement->list_size.y_list) {
			free(obj->obj_fixed_movement->list_size.x_list);
		}
		if (obj->obj_fixed_movement->list_size.t_list) {
			free(obj->obj_fixed_movement->list_size.x_list);
		}

	}
	if (obj->texture) {
		free(obj->texture);
	}
	if (obj->animation) {
		if (obj->animation->animation_textures) {
			for (int i = 0; i < len(obj->animation->animation_textures); i++) {
			free(i);
			}
			free(obj->animation->animation_textures);
		}
		free(obj->animation);
	}
	free(obj);
}
