#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>


#define ABOSOLUTE_WINDOW_HEIGTH 800
#define ABSOLUTE_WINDOW_WIDTH 450


typedef struct game game;
typedef struct game_state game_state;
typedef struct game_settings game_settings;
typedef struct game_sounds game_sounds;
typedef struct game_textures game_textures;
typedef struct game_special_effects game_special_effects;
typedef struct game_values game_values;
typedef struct texture_info texture_info;
typedef struct animation_data animation_data;
typedef struct object_list object_list;
typedef struct sprite_list sprite_list;
typedef struct sub_object sub_object;
typedef struct level level;
typedef struct menu menu;
typedef struct node node;
typedef struct values_list values_list;
typedef struct fixed_movement fixed_movement;
typedef struct object object;
typedef struct vec2 vec2;
typedef struct hitbox hitbox;
typedef enum size_type size_type;
typedef struct size_info size_info;
typedef struct vec2_float_list vec2_float_list;
typedef enum behaviour_type behaviour_type;
SDL_Color red = { 255, 0, 0, 255 };
SDL_Color blue = { 0, 0, 255, 255 };

struct game {
	game_state state;
	game_settings settings;
	game_sounds sounds;
	game_textures textures;
	game_special_effects special_effects;
	game_values values;
	SDL_Renderer *renderer;
	SDL_Window *window;
};


struct game_values {
	int coins;
	int diamonds;
	int level;
	int xp;

};
struct game_state {
	level* all_levels;
	menu menu;
	float time;
	float last_registered_logic_time;
	int current_level;

};

struct level {
	object_list *objects;
	sprite_list *sprites;
	sub_object *player;
	float time_duration;
	int points;
};

struct menu {
	object_list *all_menus;

};

struct game_settings {
	bool music;
	bool sound_effects;
	float music_volume;
	float sound_effects_volume;
};

struct game_sounds {

};
struct game_textures {
	SDL_Texture *coin;
};

struct game_special_effects {

};



struct animation_data {
	values_list lists;
	int current_frame;
	float frame_time;
	int amount_frames_animation;
	bool animation;
	int *order_animation;
};

struct vec2_float_list {
	float *x;
	float *y;
};

struct values_list {
	vec2_float_list pos; //can be position or offset
	vec2_float_list size;
	float *t_list; //time intervals for each position.
	float *r_list; //rotation
};

struct fixed_movement {
	values_list list_size;
	position_list *list_position;
};
struct node {
	sub_object* sub_obj;
	struct node* next;
};

struct object_list {
	node* start_node;
	size_t count;
};


struct vec2 {
	float x;
	float y;
};

struct object {
	sub_object **sub_objects;
	float total_visible_time_remaining;
	hitbox transform;
	values_list *fixed_transform_lists;
};

struct hitbox {
	vec2 size;
	vec2 future_size;
	vec2 position;
	vec2 future_position;
};


enum size_type {
	SIZE_TYPE_SCALE,
	SIZE_TYPE_ABS_SIZE
};

enum behaviour_type {
	BEHAVIOUR_TYPE_NONE,
	BEHAVIOUR_TYPE_ANIMATION,
	BEHAVIOUR_TYPE_FIXED_TRANSFORM
};


struct texture_info {
	SDL_Texture *texture;
	float original_heigth;
	float original_width;
	vec2 offset;
	bool bool_scale;
	vec2 size;
	vec2 future_size;
};

struct size_info {
	size_type size_type;
	vec2 size;
	vec2 future_size;
};

struct sub_object {
	behaviour_type behaviour_type;
	vec2 offset;
	bool centered_pos;
	size_info size_info;
	object_type obj_shape;
	all_states state;
	bool visible;
	SDL_Color color;
	animation_data *animation;
	mask obj_mask;
	layer obj_layer;
	SDL_Texture *texture;
	texture_info *info_texture;
	int points;
	float texture_rotation;
	float visible_time_remaining;
	values_list *fixed_transform_lists;
};

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


struct sprite_list {
	node * start_node;
	size_t count;
};

struct object_list {
	node* start_node;
	size_t count;

};

struct node {
	sub_object* sub_obj;
	struct node* next;
};



#endif STRUCT_H;