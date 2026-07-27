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

int object_excist(object* obj);

// object_type
object_type object_get_shape(object* obj);
int object_set_shape(object* obj, object_type shape);

// all_states
all_states object_get_state(object* obj);
int object_set_state(object* obj, all_states state);

// size (hitbox)
float object_get_x_size(object* obj);
float object_get_y_size(object* obj);
int object_set_x_size(object* obj, float x_size);
int object_set_y_size(object* obj, float y_size);

// future_size
float object_get_future_x_size(object* obj);
float object_get_future_y_size(object* obj);
int object_set_future_x_size(object* obj, float x_size);
int object_set_future_y_size(object* obj, float y_size);

// position
float object_get_x_pos(object* obj);
float object_get_y_pos(object* obj);
int object_set_x_pos(object* obj, float x_pos);
int object_set_y_pos(object* obj, float y_pos);

// future_position
float object_get_future_x_pos(object* obj);
float object_get_future_y_pos(object* obj);

// d-position
float object_get_dx_pos(object* obj);
float object_get_dy_pos(object* obj);


// d-size
float object_get_dx_size(object* obj);
float object_get_dy_size(object* obj);
float object_set_dx_size(object* obj, float dx);
float object_set_dy_size(object* obj, float dy);

// move_diretion
float object_get_move_direction_x(object* obj);
float object_get_move_direction_y(object* obj);
int object_set_move_direction_x(object* obj, float x);
int object_set_move_direction_y(object* obj, float y);

// obj_fixed_movement (pointer)
fixed_movement* object_get_fixed_movement(object* obj);
int object_set_fixed_movement(object* obj, fixed_movement* fm);

// visible
bool object_get_visible(object* obj);
int object_set_visible(object* obj, bool visible);

// speed
float object_get_speed(object* obj);
int object_set_speed(object* obj, float speed);

// color
SDL_Color object_get_color(object* obj);
int object_set_color(object* obj, SDL_Color color);

// animation (pointer)
animation_data* object_get_animation_ptr(object* obj);
int object_set_animation_ptr(object* obj, animation_data* anim);

// obj_mask
unsigned int object_get_mask(object* obj);
int object_set_mask(object* obj, unsigned int mask);

// obj_layer
unsigned int object_get_layer(object* obj);
int object_set_layer(object* obj, unsigned int layer);

// texture
SDL_Texture* object_get_texture(object* obj);
int object_set_texture(object* obj, SDL_Texture* texture);

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



/*
	sets movement boolean of the shape pointer all to false.
*/
 void set_all_false(object* s_p);

 void free_all_things(object_list* list);

 void reset_dx_dy(object* c);

 void reset_all_dx_dy(object_list* list);




#endif
