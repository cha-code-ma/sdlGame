/*
	Header for object.c
	All changes for a struct object
	can be made using these functions
*/
#include <SDL3/SDL.h>


#ifndef OBJECT_H
#define OBJECT_H



#define PLAYER (1 << 0)
#define WALL (1 << 1)
typedef struct game game;

typedef struct game_state game_state;
typedef struct game_settings game_settings;
typedef struct game_sounds game_sounds;
typedef struct game_textures game_textures;
typedef struct game_special_effects game_special_effects;
typedef struct	level level;
typedef struct	menu menu;
typedef struct game_values game_values;
typedef struct sub_object sub_object;
typedef struct node node;
typedef struct animation_data animation_data;
typedef struct object_list object_list;
typedef struct fixed_movement fixed_movement;
typedef struct vec2 vec2;
typedef struct position_list position_list;
typedef struct size_list size_list;

typedef struct vec2 vec2;
extern SDL_Color red;
extern SDL_Color blue;


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
	int amount_frames_animation
);

int obj_exist(sub_object* obj);


void update_charachter(sub_object* c, bool up, bool down, bool left, bool right, float dt,
	float speed, bool collision_x, bool collision_y);

/*
	moves the character on the renderer, gives 1 if the given key moves the character

	Output:
	0 when the input isnt about moving or keycode is equal to NULL.
*/
int move_charachter(object_list* list, sub_object* c, float dt);
/*
	puts character on the renderer, using the struct shape pointer.
*/
 void draw_character(SDL_Renderer* renderer, sub_object* c);
/*
	draws all shapes pointers in struct object_list on the renderer. SPECIFICALLY CHARACTER LIST
*/
 void draw_all_characters(SDL_Renderer* renderer, object_list* l_c);



#endif
