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
typedef struct object object;
typedef struct node node;
typedef struct animation_data animation_data;
typedef struct object_list object_list;
typedef struct fixed_movement fixed_movement;
typedef struct size_data size_data;
typedef struct position_list position_list;
typedef struct size_list size_list;

typedef struct vec2 vec2;
extern SDL_Color red;
extern SDL_Color blue;

typedef enum {
	SQUARE,
	TRIANGLE,
	TEXTURE,
	CIRCLE
} object_type;

typedef enum {
	IDLE,
	WALKING,
	JUMPING,
	FALLING,
	SLOW_DOWN
} all_states;

typedef enum {
	NONE = 0,
	LEFT = 1 << 0, // 0001
	RIGHT = 1 << 1, //0010
	UP = 1 << 2, //0100
	DOWN = 1 << 3 //1000
} direction;

typedef enum {
	COLLISION_NONE  = 0,
    COLLISION_TOP    = 1 << 0,
    COLLISION_BOTTOM = 1 << 1,
    COLLISION_LEFT   = 1 << 2,
    COLLISION_RIGHT  = 1 << 3
} collisionFlags;

typedef enum {
    LAYER_PLAYER  = 1 << 0,
    LAYER_ENEMY   = 1 << 1,
    LAYER_WALL    = 1 << 2,
    LAYER_BULLET  = 1 << 3,
} layer;

typedef enum {
    MASK_NONE    = 0,
    MASK_PLAYER  = LAYER_PLAYER,
    MASK_ENEMY   = LAYER_ENEMY,
    MASK_WALL    = LAYER_WALL,
    MASK_BULLET  = LAYER_BULLET,
} mask;
/*
	Initializes a struct shape pointer, inputs are obvious.

	Output:
	returns shape pointer is everything went well, otherwise NULL
*/
object* obj_init(
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

int obj_exist(object* obj);


void update_charachter(object* c, bool up, bool down, bool left, bool right, float dt,
	float speed, bool collision_x, bool collision_y);

/*
	moves the character on the renderer, gives 1 if the given key moves the character

	Output:
	0 when the input isnt about moving or keycode is equal to NULL.
*/
int move_charachter(object_list* list, object* c, float dt);
/*
	puts character on the renderer, using the struct shape pointer.
*/
 void draw_character(SDL_Renderer* renderer, object* c);
/*
	draws all shapes pointers in struct object_list on the renderer. SPECIFICALLY CHARACTER LIST
*/
 void draw_all_characters(SDL_Renderer* renderer, object_list* l_c);



#endif
