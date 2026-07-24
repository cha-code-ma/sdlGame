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


struct node {
	object* character;
	struct node* next;
};

struct object_list {
	node* start_node;
	size_t count;

};

struct object {
	object_type my_shape;
	all_states state;

	float x_position;
	float y_position;
	float x_size;
	float y_size;
	float future_dx;
	float future_dy;
	float speed;
	SDL_Color color;

	int frame;
	float frame_time;
	int amount_frames_animation;
	bool animation;

	bool move_up;
	bool move_down;
	bool move_left;
	bool move_right;

	bool visible;
	bool collision;

	unsigned int mask;
	unsigned int layer;
	SDL_Texture* texture;
};

/*
	Initializes a struct shape pointer, inputs are obvious.

	Output:
	returns shape pointer is everything went well, otherwise NULL
*/
object* player_init(
	object_type my_shape,
	float x_pos,
	float y_pos,
	float x_size,
	float y_size,
	float speed,
	bool animation,
	SDL_Color color,
	object_list* list_object,   // list_c is verwijderd
	unsigned int layer,
	unsigned int mask,
	bool visible,
	bool player,
	bool collision,
	int amount_frames_animation
) {
	object* s_p = malloc(sizeof(object));
	if (!s_p) {
		return NULL;
	}
	int check = 1;
	node* n_p = node_init(s_p);


	if (!check) {
		free(s_p);
		return NULL;
	}
	check = node_insert(list_object, n_p);
	if (!check) {
		free(s_p);
		return NULL;
	}
		list_object->count++;

	s_p->my_shape = my_shape;
	s_p->x_position = x_pos;
	s_p->y_position = y_pos;
	s_p->x_size = x_size;
	s_p->y_size = y_size;
	s_p->state = IDLE;
	s_p->animation = animation;
	s_p->move_down = false;
	s_p->move_left = false;
	s_p->move_right = false;
	s_p->move_up = false;
	s_p->color = color;
	s_p->visible = true;
	s_p->mask = mask;
	s_p->layer = layer;
	s_p->future_dx = 0.0f;
	s_p->future_dy = 0.0f;
	s_p->speed = speed;
	s_p->collision = collision;
	s_p->amount_frames_animation = amount_frames_animation;
	s_p->frame_time = 0.0f;
	s_p->texture = NULL;
	return s_p;
}

int object_excist(object* obj) {
	if (obj) {
		return 1;
	}
	return 0;
}
float object_get_x_pos(object* obj) {

	return obj->x_position;
}

float object_get_y_pos(object* obj) {
	return obj->y_position;
}

float object_get_x_size(object* obj) {
	return obj->x_size;
}

float object_get_y_size(object* obj) {
	return obj->y_size;
}

float object_get_future_dx(object* obj) {
	return obj->future_dx;
}

float object_get_future_dy(object* obj) {
	return obj->future_dy;
}

float object_get_future_x_pos(object* obj) {
	return obj->x_position + obj->future_dx;
}

float object_get_future_y_pos(object* obj) {
	return obj->y_position + obj->future_dy;
}

float object_get_speed(object* obj) {
	return obj->speed;
}

SDL_Color object_get_color(object* obj) {
	return obj->color;
}

int object_get_animation_frame(object* obj) {
	return obj->frame;
}

unsigned int object_get_mask(object* obj) {
	return obj->mask;
}

unsigned int object_get_layer(object* obj) {
	return obj->layer;
}

bool object_get_visible(object* obj) {
	return obj->visible;
}

bool object_get_collision(object* obj) {
	return obj->collision;
}

bool object_get_animation(object* obj) {
	return obj->animation;
}

float object_get_frame_time(object* obj) {
	return obj->frame_time;
}

int object_set_x_pos(object* obj, float x_pos) {
	if (!obj) {
		return 0;
	}
	obj->x_position = x_pos;
	return 1;
}


int object_set_y_pos(object* obj, float y_pos) {
	if (!obj) {
		return 0;
	}
	obj->y_position = y_pos;
	return 1;
}


int object_set_x_size(object* obj, float x_size) {
	if (!obj) {
		return 0;
	}
	obj->x_size = x_size;
	return 1;
}

int object_set_y_size(object* obj, float y_size) {
	if (!obj) {
		return 0;
	}
	obj->y_size = y_size;
	return 1;
}


int object_set_future_dx(object* obj, float future_dx) {
	if (!obj) {
		return 0;
	}
	obj->future_dx = future_dx;
	return 1;
}


int object_set_future_dy(object* obj, float future_dy) {
	if (!obj) {
		return 0;
	}
	obj->future_dy = future_dy;
	return 1;
}



int object_set_speed(object* obj, float speed) {
	if (!obj) {
		return 0;
	}
	obj->speed = speed;
	return 1;
}


int object_set_color(object* obj, SDL_Color color) {
	if (!obj) {
		return 0;
	}
	obj->color = color;
	return 1;
}


int object_set_animation_frame(object* obj, int frame) {
	if (!obj) {
		return 0;
	}
	obj->frame = frame;
	return 1;
}


int object_set_mask(object* obj, unsigned int mask) {
	if (!obj) {
		return 0;
	}
	obj->mask = mask;
	return 1;
}


int object_set_layer(object* obj, unsigned int layer) {
	if (!obj) {
		return 0;
	}
	obj->layer = layer;
	return 1;
}

int object_set_visible(object* obj, bool visible) {
	if (!obj) {
		return 0;
	}
	obj->visible = visible;
	return 1;
}


int object_set_collision(object* obj, bool collision) {
	if (!obj) {
		return 0;
	}
	obj->collision = collision;
	return 1;
}

int object_set_animation(object* obj, bool animation) {
	if (!obj) {
		return 0;
	}
	obj->animation = animation;
	return 1;
}

int object_set_frame_time(object* obj, float frame_time) {
	if (!obj) {
		return 0;
	}
	obj->frame_time = frame_time;
	return 1;
}

int object_get_amount_frames_animation(object* obj) {
	return obj->amount_frames_animation;
}
int object_set_amount_frames_animation(object* obj, int amount) {
	if (!obj) {
		return 0;
	}
	obj->amount_frames_animation = amount;
	return 1;
}

bool object_get_bool_left(object* obj) {
	return obj->move_left;
}

bool object_get_bool_right(object* obj) {
	return obj->move_right;
}

bool object_get_bool_up(object* obj) {
	return obj->move_up;
}

bool object_get_bool_down(object* obj) {
	return obj->move_down;
}

int object_set_bool_left(object* obj, bool left) {
	if (!obj) {
		return 0;
	}
	obj->move_left = left;
	return 1;
}

int object_set_bool_right(object* obj, bool right) {
	if (!obj) {
		return 0;
	}
	obj->move_right = right;
	return 1;
}

int object_set_bool_up(object* obj, bool up) {
	if (!obj) {
		return 0;
	}
	obj->move_up = up;
	return 1;
}

int object_set_bool_down(object* obj, bool down) {
	if (!obj) {
		return 0;
	}
	obj->move_down = down;
	return 1;
}

int object_set_type(object* obj, object_type type) {
	if (!obj) {
		return 0;
	}
	obj->my_shape = type;
	return 1;
}

object_type object_get_type(object* obj) {
	return obj->my_shape;
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