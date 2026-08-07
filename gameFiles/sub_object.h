/*
	Header for object.c
	All changes for a struct object
	can be made using these functions
*/



#ifndef OBJECT_H
#define OBJECT_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "structs.h"


/*
	initializes sub_object, and puts it in object if given
*/
sub_object* sub_obj_init(
	SDL_Renderer *renderer,
	object_list* list_object,
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
);

/*
	frees sub_object from memory.
*/
void free_sub_object(sub_object* sub_obj);


#endif
