/*
	object.c functions of object.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
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
	SDL_Texture *obj_texture,
	SDL_Texture **obj_animation_textures,
	int points,
	float stay_time

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
	s_p->texture = obj_texture;
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


void update_charachter(sub_object* obj, float dt) {
	float factor = 1;
	float speed = obj->speed;
	int amount_inputs = 0;

	direction obj_direction = object_get_move_direction_x(obj), object_get_move_direction_y(obj);


	if (amount_inputs == 2) {
		factor = 1.0f / sqrtf(2);
	}

	direction current_direction = obj->animation;
	//animation
	if (object_get_animation(c)) {
		float new_frame_time = object_get_frame_time(c) + dt;
		object_set_frame_time(c, object_get_frame_time(c) + dt);
		if (object_get_frame_time(c) > 0.1f) {
			object_set_animation_frame(c, (object_get_animation_frame(c) + 1) % object_get_amount_frames_animation(c));
			object_set_frame_time(c, 0.0f);
		}
	}
}




/*
	puts character on the renderer, using the struct shape pointer.
*/
void draw_character(SDL_Renderer* renderer, sub_object* c) {
	SDL_SetRenderDrawColor(renderer, c->color.r, c->color.g, c->color.b, c->color.a);
	if (object_get_type(c) == SQUARE) {
		SDL_FRect rect = {
			object_get_x_pos(c),
			object_get_y_pos(c),
			object_get_x_size(c),
			object_get_y_size(c)
		};
		SDL_RenderFillRect(renderer, &rect);
		return;
	}
	if (object_get_type(c) == CIRCLE) {


	}
}

/*
	draws all shapes pointers in struct object_list on the renderer. SPECIFICALLY CHARACTER LIST
*/
 void draw_all_characters(SDL_Renderer* renderer, object_list* l_c) {

	if (!renderer || !l_c || !object_list_get_start_node(l_c)) {
		return;
	}
	node* current_node = object_list_get_start_node(l_c);
	while (current_node) {
		draw_character(renderer, node_get_object(current_node));
		current_node = node_get_next(current_node);
	}
}

