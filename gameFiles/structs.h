#ifndef STRUCT_H
#define STRUCT_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <stdbool.h>

struct game {
	game_state state;
	game_settings settings;
	game_sounds sounds;
	game_textures textures;
	game_special_effects special_effects;
	game_values values;

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

struct animation_order {
	int animation_index;
	float time;
};

struct animation_data {
	int current_frame;
	float frame_time;
	int amount_frames_animation;
	bool animation;
	float *rotations;
	animation_order order_animation;
	SDL_Texture **animation_textures;
};

struct size_list {
	float *x_list;
	float *y_list;
	float *t_list; //time intervals for each position.
};

struct fixed_movement {
	size_list list_size;
	position_list *list_position;
};
struct node {
	sub_object* character;
	struct node* next;
};

struct object_list {
	node* start_node;
	size_t count;
};

struct position_list {
	float *x_list;
	float *y_list;
	float *t_list; //time intervals for each position.
};


struct vec2 {
	float x;
	float y;
};

struct object {
	sub_object **sub_objects;
	float total_visible_time_remaining;
};

struct sub_object {
	object_type obj_shape;
	all_states state;
	vec2 size; //hitbox
	vec2 future_size; //hitbox
	vec2 texture_position;
	vec2 texture_size;
	vec2 position;
	vec2 future_position;
	vec2 move_diretion; //after calculations.
	fixed_movement *obj_fixed_movement;
	bool visible;
	float speed;
	SDL_Color color;
	animation_data *animation;
	mask obj_mask;
	layer obj_layer;
	SDL_Texture *texture;
	int points;
	float texture_rotation;
	float visible_time_remaining;
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
	sub_object* character;
	struct node* next;
};



#endif STRUCT_H;