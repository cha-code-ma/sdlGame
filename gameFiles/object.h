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

typedef struct object object;
typedef struct node node;
typedef struct animation_data animation_data;
typedef struct object_list object_list;
typedef struct fixed_movement fixed_movement;
typedef struct size_data size_data;
typedef struct position_list position_list;
typedef struct size_list size_list;

typedef struct position_data position_data;
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
	LEFT,
	RIGHT,
	UP,
	DOWN
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

float object_get_x_pos(object* obj);

float object_get_y_pos(object* obj);

float object_get_x_size(object* obj);

float object_get_y_size(object* obj);

float object_get_future_dx(object* obj);

float object_get_future_dy(object* obj);

float object_get_future_x_pos(object* obj);

float object_get_future_y_pos(object* obj);

float object_get_speed(object* obj);

SDL_Color object_get_color(object* obj);

int object_get_animation_frame(object* obj);

unsigned int object_get_mask(object* obj);

unsigned int object_get_layer(object* obj);

bool object_get_visible(object* obj);

bool object_get_collision(object* obj);

bool object_get_animation(object* obj);

float object_get_frame_time(object* obj);

int object_get_amount_frames_animation(object* obj);

bool object_get_bool_left(object* obj);

bool object_get_bool_right(object* obj);

bool object_get_bool_up(object* obj);

bool object_get_bool_down(object* obj);

int object_set_bool_left(object* obj, bool left);

int object_set_bool_right(object* obj, bool right);

int object_set_bool_up(object* obj, bool up);

int object_set_bool_down(object* obj, bool up);

int object_set_type(object* obj, object_type type);

object_type object_get_type(object* obj);

/*
	sets x_position. Returns 1 if it went well, returns 0 if not.  struct object
*/
int object_set_x_pos(object* obj, float x_pos);

/*
	sets y position. Returns 1 if it went well, returns 0 if not.  struct object
*/
int object_set_y_pos(object* obj, float y_pos);

/*
	sets x size. Returns 1 if it went well, returns 0 if not.  struct object
*/
int object_set_x_size(object* obj, float x_size);

/*
	sets y size. Returns 1 if it went well, returns 0 if not.  struct object
*/
int object_set_y_size(object* obj, float y_size);

/*
	sets future dx. Returns 1 if it went well, returns 0 if not. struct object
*/
int object_set_future_dx(object* obj, float future_dx);

/*
	sets future dy. Returns 1 if it went well, returns 0 if not. struct object
*/
int object_set_future_dy(object* obj, float future_dy);

/*
	sets speed. Returns 1 is if went well, returns 0 if not. struct object
*/
int object_set_speed(object* obj, float speed);

/*
	sets color. Returns 1 is it went well, returns 0 if not. struct object
*/
int object_set_color(object* obj, SDL_Color color);

/*
	sets animation frame. Returns 1 if it went well, returns 0 if not. struct object
*/
int object_set_animation_frame(object* obj, int frame);

/*
	sets mask. Returns 1 if it went well, returns 0 if not. struct object
	you need to use bitoperations
*/
int object_set_mask(object* obj, unsigned int mask);

/*
	sets layer. Returns 1 if it went well, returns 0 if not. struct object
	You need to use bitoperations
*/
int object_set_layer(object* obj, unsigned int layer);

/*
	sets visible boolean. Returns 1 if it went well, returns 0 if not. struct object
*/
int object_set_visible(object* obj, bool visible);

/*
	Sets collision boolean. Returns 1 if it went well, returns 0 if not. struct object
*/
int object_set_collision(object* obj, bool collision);

/*
	Sets animation boolean. Returns 1 if it went well, returns 0 if not. struct object
*/
int object_set_animation(object* obj, bool animation);

/*
	sets the last time the next frame has taken to apear, to get a consistent animation.
	Returns 1 if it went well, returns 0 if not. struct object.
*/
int object_set_frame_time(object* obj, float frame_time);

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
