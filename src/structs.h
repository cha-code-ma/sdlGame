#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "game.h"
#include <stdbool.h>
#define ABOSOLUTE_WINDOW_HEIGTH 800
#define ABSOLUTE_WINDOW_WIDTH 450


typedef struct game_t game_t;
typedef struct game_state game_state;
typedef struct game_settings game_settings;
typedef struct game_sounds game_sounds;
typedef struct game_textures game_textures;
typedef struct game_special_effects game_special_effects;
typedef struct game_values game_values;
typedef struct texture_info texture_info;
typedef struct animation_data animation_data;


typedef struct sub_object sub_object;
typedef struct level level;
typedef struct menu menu;
typedef struct values_list values_list;
typedef struct object object;
typedef struct vec2 vec2;


typedef struct size_info size_info;
typedef struct vec2_float_list vec2_float_list;
typedef struct hitbox hitbox;
typedef struct button button;
typedef struct object_pool object_pool;
typedef struct sub_object_pool sub_object_pool;
typedef struct text_info_t text_info_t;
typedef struct ui_t ui_t;
typedef struct button_pool button_pool;
typedef struct string string;
typedef struct text_ui text_ui;
typedef struct group_t group_t;
typedef struct group_action group_action;
typedef struct button_action_info button_action_info;
typedef struct game_progress game_progress;
typedef struct game_save_values game_save_values;
typedef struct game_const_values game_const_values;
typedef struct game_textures game_textures;
typedef struct game_fonts game_fonts;
typedef struct fixed_tempelate_list fixed_tempelate_list;
typedef struct game_IO game_IO;
typedef struct text_ui_pool text_ui_pool;

typedef enum time_type time_type;
typedef enum action_type action_type;
typedef enum behaviour_type behaviour_type;
typedef enum size_type size_type;
typedef enum object_type object_type;
typedef enum sub_object_type sub_object_type;
typedef enum pool_types pool_types;

struct button {
	button_action_info *action_info;
	string *name;
	text_info_t text_info;
	vec2 position;
	vec2 size;
	SDL_Color color;
	SDL_Color second_color; //for when the button is being clicked/hovered.
	sub_object_pool *details;
	bool visible;
	bool active;
	bool clicked;
	float clicked_time_left;
};

struct button_action_info {
	group_action **group_actions;
	int action_count;
	int action_capacity;
};



enum action_type {
	ACTION_TYPE_RAND_FUNC,
	ACTION_TYPE_HIDE,
	ACTION_TYPE_SHOW,
	ACTION_TYPE_NEG_VISIBILITY,

};

struct text_info_t {
	string *text;
	bool text_centered_bool;
	vec2 text_offset;

	vec2 text_size;
	bool text_pos_scaled_bool;
	bool text_size_scaled_bool;
};

struct text_ui {
	string *text;
	vec2 pos;
	vec2 size;
	bool transparant_background;
	SDL_Color background_color;
};



SDL_Color red = { 255, 0, 0, 255 };
SDL_Color blue = { 0, 0, 255, 255 };

struct game_t {
	game_const_values const_values;
	game_state state;
	game_settings settings;
	game_sounds sounds;
	game_textures textures;
	game_special_effects special_effects;
	game_values values;
	SDL_Renderer *renderer;
	SDL_Window *window;
	game_progress progress;
	game_save_values save_values;
	game_fonts fonts;
	game_IO IO;
};

struct game_IO {
	vec2 mouse_pos;
	vec2 prev_mouse_pos;
	time_type cur_valid;
	int current_key;
	time_type prev_valid;
	int previous_key;
	float key_time;
};

struct game_fonts {
	TTF_Font *basic_font;
};

struct game_const_values {
	char *languages[30];
	int amount_languages;
};


struct game_save_values {
	//settings
	bool music;
	bool sound_effects;
	int music_volume;
	int sound_effects_volume;
	char language[30];
	// game_values
	int current_level;
	int coins;
	int diamonds;
	int level;
	int xp;
};

struct game_progress {

};

struct game_values {
	int coins;
	int diamonds;
	int level;
	int xp;

};

struct game_state {
	level *active_level;
	level** all_levels;
	menu menu;
	float dt;
	Uint64 time;
};

enum time_type {
	TIME_TYPE_VALID,
	TIME_TYPE_INVALID,
	TIME_TYPE_LATE
};

enum object_type {
	OBJECT_TYPE_TAPPER,
    OBJECT_TYPE_SOMETHING_ELSE
};

enum sub_object_type {
	SUB_OBJECT_TYPE_PRIMARY_TEXTURE,
	SUB_OBJECT_TYPE_SECONDARY_TEXTURE
};



struct ui_t {
	object_pool *ui_objects;
	button_pool *buttons;
	text_ui_pool *strings;
};

struct group_t {
	string *name;
	object_pool *objects;
	ui_t *ui;


};

struct group_action {
	group_t *group_id;
	action_type action;
	bool is_active;
	void (*custom_action)(group_t *group); //optioneel, eigen functie.
};

struct level {
	object_pool *objects;
	object_pool *sprites;
	ui_t *UI;
	group_t *groups;
	float time_duration;
	int points;
};

struct text_ui_pool {
    string **strings;
    int* free_list;
    int count;
    int capacity;
    int free_count;

};


struct button_pool {
    button **buttons;
    int* free_list;
    int count;
    int capacity;
    int free_count;

};

enum pool_types {
	POOL_TYPES_BUTTON,
	POOL_TYPES_OBJECT,
	POOL_TYPES_SUB_OBJECT,
	POOL_TYPES_TEXT_UI
};


struct menu {
	object_pool *all_menus;

};

struct game_settings {
	bool music;
	bool sound_effects;
	int music_volume;
	int sound_effects_volume;
	char language[30];
};

struct game_sounds {

};


struct game_textures {
	SDL_Texture *circle_yellow;
};

struct game_special_effects {

};



struct animation_data {
	int current_animation_index;
	float *frame_time_list;
	float *rotation_list;
	int amount_frames_animation;
	bool animation;
	int *order_animation;
};

struct vec2_float_list {
	float *x;
	float *y;
};

struct fixed_tempelate_list {
	vec2_float_list fixed_list;
	Uint64 *time_list;
	int length;
	int index;
	Uint64 time_left;
};

struct values_list {
	fixed_tempelate_list *pos;
	fixed_tempelate_list *size;

};

struct sub_object_pool {
    sub_object** objects;
    int* free_list;
    int count;
    int capacity;
    int free_count;
};

typedef struct {
    object** objects;
    int* free_list;
    int count;
    int capacity;
    int free_count;
} object_pool;


struct vec2 {
	float x;
	float y;
};

struct object {
	object_type type;
	string *name;
	behaviour_type behaviour;
	sub_object_pool *sub_objects;
	float total_visible_time_remaining;
	hitbox transform;
	values_list *fixed_transform_lists;
	bool time_started;
	bool clicked;
	bool is_clickable;
};

struct hitbox {
	vec2 size;
	vec2 future_size;
	vec2 position;
	vec2 future_position;
	bool click_active;
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


struct string {
	char *text;
	int length; //length text
	int capacity; //total char amount
	SDL_Color color;
	TTF_Font *font;
};

struct sub_object {
	sub_object_type type;
	vec2 offset;
	bool centered_pos;
	size_info size_info;
	all_states state;
	bool visible;
	SDL_Color color;
	animation_data *animation;
	SDL_Texture *texture;
	texture_info *info_texture;
	int points;
	float texture_rotation;
	float visible_time_remaining;
	bool time_started;
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


#endif STRUCT_H;