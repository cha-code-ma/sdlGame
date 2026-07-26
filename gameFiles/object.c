/*
	object.c functions of object.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include "object.h"
#include "object_list.h"
#include "physics.h"
SDL_Color red = { 255, 0, 0, 255 };
SDL_Color blue = { 0, 0, 255, 255 };


struct animation_data {
	int current_frame;
	float frame_time;
	int amount_frames_animation;
	bool animation;
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
	object* character;
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

struct size_data {
	float x;
	float y;
};

struct position_data {
	float x;
	float y;
};

struct object {
	object_type obj_shape;
	all_states state;
	size_data size; //hitbox
	size_data future_size; //hitbox
	position_data position;
	position_data future_position;
	position_data move_diretion;
	fixed_movement *obj_fixed_movement;
	bool visible;
	float speed;
	SDL_Color color;
	animation_data *animation;
	mask obj_mask;
	layer obj_layer;
	SDL_Texture *texture;
};

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
	SDL_Texture **obj_animation_textures

) {
	object* s_p = malloc(sizeof(object));
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
			free(s_p);
			return NULL;
		}
		s_p->obj_fixed_movement->list_size.x_list = size_list_x;
		s_p->obj_fixed_movement->list_size.y_list = size_list_y;
		s_p->obj_fixed_movement->list_size.t_list = time_list_size;
		if (fixed_positions_bool) {
			s_p->obj_fixed_movement->list_position = malloc(sizeof(position_list));
			if (!s_p->obj_fixed_movement->list_position) {
				free(s_p);
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
			free(s_p);
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
	return s_p;
}

void free_object(object* obj) {
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

int object_excist(object* obj) {
	if (obj) {
		return 1;
	}
	return 0;
}

object_type object_get_shape(object* obj) {
    return obj->obj_shape;
}
int object_set_shape(object* obj, object_type shape) {
    if (!obj) return 0;
    obj->obj_shape = shape;
    return 1;
}

all_states object_get_state(object* obj) {
    return obj->state;
}
int object_set_state(object* obj, all_states state) {
    if (!obj) return 0;
    obj->state = state;
    return 1;
}

float object_get_x_size(object* obj) {
    return obj->size.x;
}
float object_get_y_size(object* obj) {
    return obj->size.y;
}
int object_set_x_size(object* obj, float x_size) {
    if (!obj) return 0;
    obj->size.x = x_size;
    return 1;
}
int object_set_y_size(object* obj, float y_size) {
    if (!obj) return 0;
    obj->size.y = y_size;
    return 1;
}

float object_get_future_x_size(object* obj) {
    return obj->future_size.x;
}
float object_get_future_y_size(object* obj) {
    return obj->future_size.y;
}
int object_set_future_x_size(object* obj, float x_size) {
    if (!obj) return 0;
    obj->future_size.x = x_size;
    return 1;
}
int object_set_future_y_size(object* obj, float y_size) {
    if (!obj) return 0;
    obj->future_size.y = y_size;
    return 1;
}

float object_get_x_pos(object* obj) {
    return obj->position.x;
}
float object_get_y_pos(object* obj) {
    return obj->position.y;
}
int object_set_x_pos(object* obj, float x_pos) {
    if (!obj) return 0;
    obj->position.x = x_pos;
    return 1;
}
int object_set_y_pos(object* obj, float y_pos) {
    if (!obj) return 0;
    obj->position.y = y_pos;
    return 1;
}

float object_get_future_x_pos(object* obj) {
    return obj->future_position.x;
}
float object_get_future_y_pos(object* obj) {
    return obj->future_position.y;
}
int object_set_future_x_pos(object* obj, float x_pos) {
    if (!obj) return 0;
    obj->future_position.x = x_pos;
    return 1;
}
int object_set_future_y_pos(object* obj, float y_pos) {
    if (!obj) return 0;
    obj->future_position.y = y_pos;
    return 1;
}

float object_get_move_direction_x(object* obj) {
    return obj->move_diretion.x;
}
float object_get_move_direction_y(object* obj) {
    return obj->move_diretion.y;
}

float object_get_dx_pos(object* obj) {
	return obj->future_position.x - obj->position.x;
}
float object_get_dy_pos(object* obj) {
	return obj->future_position.y - obj->position.y;
}

float object_get_dx_size(object* obj) {
	return obj->future_size.x - obj->future_size.x;
}
float object_get_dy_size(object* obj) {
	return obj->future_size.y - obj->future_size.y;
}

int object_set_move_direction_x(object* obj, float x) {
    if (!obj) return 0;
    obj->move_diretion.x = x;
    return 1;
}
int object_set_move_direction_y(object* obj, float y) {
    if (!obj) return 0;
    obj->move_diretion.y = y;
    return 1;
}

fixed_movement* object_get_fixed_movement(object* obj) {
    return obj->obj_fixed_movement;
}
int object_set_fixed_movement(object* obj, fixed_movement* fm) {
    if (!obj) return 0;
    obj->obj_fixed_movement = fm;
    return 1;
}

bool object_get_visible(object* obj) {
    return obj->visible;
}
int object_set_visible(object* obj, bool visible) {
    if (!obj) return 0;
    obj->visible = visible;
    return 1;
}

float object_get_speed(object* obj) {
    return obj->speed;
}
int object_set_speed(object* obj, float speed) {
    if (!obj) return 0;
    obj->speed = speed;
    return 1;
}

SDL_Color object_get_color(object* obj) {
    return obj->color;
}
int object_set_color(object* obj, SDL_Color color) {
    if (!obj) return 0;
    obj->color = color;
    return 1;
}

animation_data* object_get_animation_ptr(object* obj) {
    return obj->animation;
}
int object_set_animation_ptr(object* obj, animation_data* anim) {
    if (!obj) return 0;
    obj->animation = anim;
    return 1;
}

unsigned int object_get_mask(object* obj) {
    return obj->obj_mask;
}
int object_set_mask(object* obj, unsigned int mask) {
    if (!obj) return 0;
    obj->obj_mask = mask;
    return 1;
}

unsigned int object_get_layer(object* obj) {
    return obj->obj_layer;
}
int object_set_layer(object* obj, unsigned int layer) {
    if (!obj) return 0;
    obj->obj_layer = layer;
    return 1;
}

SDL_Texture* object_get_texture(object* obj) {
    return obj->texture;
}
int object_set_texture(object* obj, SDL_Texture* texture) {
    if (!obj) return 0;
    obj->texture = texture;
    return 1;
}

void update_charachter(object* c, bool up, bool down, bool left, bool right, float dt,
	float speed, bool collision_x, bool collision_y) {
	float factor = 1;
	int amount_inputs = 0;
	if (left) {
		amount_inputs++;
	}
	if (right) {
		amount_inputs++;
	}
	if (up) {
		amount_inputs++;
	}
	if (down) {
		amount_inputs++;
	}
	if (amount_inputs == 2) {
		factor = 1.0f / sqrtf(2);
	}

	if (left && !collision_x) {
		object_set_x_pos(c, object_get_x_pos(c) - speed * dt * factor);
	}
	if (right && !collision_x) {
		object_set_x_pos(c, object_get_x_pos(c) + speed * dt * factor);
	}
	if (up && !collision_y) {
		object_set_y_pos(c, object_get_y_pos(c) - speed * dt * factor);

	}
	if (down && !collision_y) {
		object_set_y_pos(c, object_get_y_pos(c) + speed * dt * factor);
	}
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
	moves the character on the renderer, gives 1 if the given key moves the character

	Output:
	0 when the input isnt about moving or keycode is equal to NULL.
*/
int move_charachter(object_list* list, object* c, float dt) {
	if (!c || !list) {
		return 0;
	}
	bool collision_x = check_all_collision_x(c, list, dt);
	bool collision_y = check_all_collision_y(c, list, dt);
	if (collision_x && collision_y) {
		return 0;
	}

	if (object_get_bool_up(c)) {
		update_charachter(c, true, false, false, false, dt, object_get_speed(c), collision_x, collision_y);
	}
	if (object_get_bool_left(c)) {
		update_charachter(c, false, false, true, false, dt, object_get_speed(c), collision_x, collision_y);
	}
	if (object_get_bool_right(c)) {
		update_charachter(c, false, false, false, true, dt, object_get_speed(c), collision_x, collision_y);
	}
	if (object_get_bool_down(c)) {
		update_charachter(c, false, true, false, false, dt, object_get_speed(c), collision_x, collision_y);
	}
	return 1;
}


/*
	puts character on the renderer, using the struct shape pointer.
*/
void draw_character(SDL_Renderer* renderer, object* c) {
	SDL_SetRenderDrawColor(renderer, object_get_color(c).r, object_get_color(c).g, object_get_color(c).b, object_get_color(c).a);
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
	if (object_get_type(c) == TRIANGLE) {

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



/*
	sets movement boolean of the shape pointer all to false.
*/
 void set_all_false(object* s_p) {
	if (!s_p) {
		return;
	}
	object_set_bool_left(s_p, false);
	object_set_bool_down(s_p, false);
	object_set_bool_up(s_p, false);
	object_set_bool_right(s_p, false);
}

 void free_all_things(object_list* list) {
	if (list) {
		free_object_list(list);
	}
}

 void reset_dx_dy(object* c) {
	if (!c) {
		return;
	}
	object_set_future_dx(c, 0.0f);
	object_set_future_dy(c, 0.0f);
}

 void reset_all_dx_dy(object_list* list) {
	if (!list || !object_list_get_start_node(list)) {
		return;
	}
	node* current_node = object_list_get_start_node(list);
	while (current_node) {
		reset_dx_dy(node_get_object(current_node));
		current_node = node_get_next(current_node);
	}
}