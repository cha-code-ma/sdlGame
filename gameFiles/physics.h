/*

*/
#ifndef PHYSICS_H
#define PHYSICS_H

#include <SDL3/SDL.h>
#include <stdbool.h>


typedef struct node node;
typedef struct object object;
typedef struct object_list object_list;

/*
	checks collision on the X-axis between 2 struct shape pointers, also looking at layer and mask

	Output:
	returns 1 if collison has occured, return 0 if not.
*/
int check_collision_x(object* obj1, object* obj2);

/*
	checks collision on the Y-axis between 2 struct shape pointers, also looking at layer and mask

	Output:
	returns 1 if collison has occured, return 0 if not.
*/
int check_collision_y(object* obj1, object* obj2);

/*
	checks all collisions on the Y-axis between the input :struct shape pointer obj1 and all objects in the scene.

	Output:
	returns 0 is there is no collision, returns 1 if there was a collision with any object of
	the scene.
	Returns -1 if something went wrong.
*/
int check_all_collision_y(object* obj1, object_list* list, float dt);

/*
	checks all collisions on the X-axis between the input :struct shape pointer obj1 and all objects in the scene.

	Output:
	returns 0 is there is no collision, returns 1 if there was a collision with any object of
	the scene.
	Returns -1 if something went wrong.
*/
int check_all_collision_x(object* obj1, object_list* list, float dt);

/*
	Sets the potential dy, dx of the struct object. So it can calculate later if a collision
	will occur when moving.
*/
void update_future_movement(object* c, bool left, bool right, bool up, bool down, float dt);

#endif
