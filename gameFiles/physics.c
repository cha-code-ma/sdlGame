/*

*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include "object.h"
#include "physics.h"
#include "object_list.h"






int check_collision_x(object* obj1, object* obj2) {
	if ((!(object_get_mask(obj1) & object_get_layer(obj2)) && (object_get_mask(obj2) & object_get_layer(obj1)))
		|| !object_get_collision(obj1) || !object_get_collision(obj2)) {
		return 0;
	}
	float obj1_left = object_get_x_pos(obj1) + object_get_future_dx(obj1);
	float obj1_right = object_get_x_pos(obj1) +  object_get_x_size(obj1) + object_get_future_dx(obj1);

	float obj2_left = object_get_x_pos(obj2) + object_get_future_dx(obj2);
	float obj2_right = object_get_x_pos(obj2) + object_get_x_size(obj2) + object_get_future_dx(obj2);

	float obj1_top = object_get_y_pos(obj1);
	float obj1_bottom = object_get_y_pos(obj1) + object_get_y_size(obj1);


	float obj2_top = object_get_y_pos(obj2);
	float obj2_bottom = object_get_y_pos(obj2) + object_get_y_size(obj2);

	if (obj1_right > obj2_left &&
		obj1_left   < obj2_right &&
		obj1_bottom > obj2_top &&
		obj1_top < obj2_bottom)
	{
		return 1;
	}
	return 0;
}


int check_collision_y(object* obj1, object* obj2) {
	if ((!(object_get_mask(obj1) & object_get_layer(obj2)) && (object_get_mask(obj2) & object_get_layer(obj1)))
		|| !object_get_collision(obj1) || !object_get_collision(obj2)) {
		return 0;
	}

	float obj1_left = object_get_x_pos(obj1);
	float obj1_right = object_get_x_pos(obj1) + object_get_x_size(obj1);

	float obj2_left = object_get_x_pos(obj2);
	float obj2_right = object_get_x_pos(obj2) + object_get_x_size(obj2);

	float obj1_top = object_get_y_pos(obj1) + object_get_future_dy(obj1);
	float obj1_bottom = object_get_y_pos(obj1) + object_get_y_size(obj1) + object_get_future_dy(obj1);


	float obj2_top =  object_get_y_pos(obj2) + object_get_future_dy(obj2);
	float obj2_bottom = object_get_y_pos(obj2) + object_get_y_size(obj2) + object_get_future_dy(obj2);

	if (obj1_bottom > obj2_top &&
		obj1_top    < obj2_bottom &&
		obj1_right  > obj2_left &&
		obj1_left < obj2_right)
	{
		return 1;
	}
	return 0;
}

int check_all_collision_y(object* obj1, object_list* list, float dt) {
	int collision;
	if (!obj1 || !list) {
		return -1;
	}
	if (!object_list_get_start_node(list)) {
		return 0;
	}
	node* current_node = object_list_get_start_node(list);

	while (current_node) {
		if (node_get_object(current_node) == obj1) {
			current_node = node_get_next(current_node);
			continue;
		}
		collision = check_collision_y(obj1, node_get_object(current_node));
		if (collision == -1) {
			return -1;
		}
		if (collision) {
			return 1;
		}
		current_node = node_get_next(current_node);
	}
	return 0;
}

int check_all_collision_x(object* obj1, object_list* list, float dt) {
	int collision;
	if (!obj1 || !list) {
		return -1;
	}
	if (!object_list_get_start_node(list)) {
		return 0;
	}
	node* current_node = object_list_get_start_node(list);

	while (current_node) {
		if (node_get_object(current_node) == obj1) {
			current_node = node_get_next(current_node);
			continue;
		}
		collision = check_collision_x(obj1, node_get_object(current_node));
		if (collision == -1) {
			return -1;
		}
		if (collision) {
			return 1;
		}
		current_node = node_get_next(current_node);
	}
	return 0;
}

void update_future_movement(object* c, bool left, bool right, bool up, bool down, float dt) {
	if (!c) {
		return;
	}
	object_set_future_dx(c, 0.0f);
	object_set_future_dy(c, 0.0f);

	if (left) {
		object_set_future_dx(c, -(object_get_speed(c) * dt));
	}
	if (right) {
		object_set_future_dx(c, object_get_speed(c) * dt);
	}
	if (up) {
		object_set_future_dy(c, -(object_get_speed(c) * dt));
	}
	if (down) {
		object_set_future_dy(c, object_get_speed(c) * dt);
	}
}
