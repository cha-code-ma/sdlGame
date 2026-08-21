/*
	Header for object.c
	All changes for a struct object
	can be made using these functions
*/



#ifndef SUB_OBJECT_H
#define SUB_OBJECT_H
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "structs.h"


/*
	initializes sub_object, and puts it in object if given
*/
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

);

/*
	frees sub_object from memory.
*/
void free_sub_object(sub_object* sub_obj);


#endif
