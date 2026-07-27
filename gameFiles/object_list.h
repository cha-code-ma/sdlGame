/*

*/
#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

typedef struct object object;
typedef struct node node;
typedef struct object_list object_list;
typedef struct sprite_list sprite_list;



/*
	initializes a struct all_characters_list pointer

	Output:
	if everything went well, it outputs the object_list pointer, else NULL
*/
object_list* object_list_init(void);

/*
	Get start  node of the stuct obejct_list
*/
node* object_list_get_start_node(object_list* list);

/*
	Initializes a struct node pointer.

	Output:
	returns the node pointer is everything went well, otherwise NULL
*/
node* node_init(object* s_p);

/*
	deletes the malloced struct node pointer.
*/
void node_delete(node* n_p);

/*
	Removes the input node pointer n_p from the object pointer list and returns it.
	While keeping the linked list in tact.
*/
node* node_remove_List(node* n_p, object_list* list);

/*
	Inserts a struct node into the struct object_list

	Output:
	returns 1 if insert went well, returns 0 if something went wrong
*/
int node_insert(object_list* list_c, node* n_p);

/*
	frees the struct object_list pointer
*/
void free_object_list(object_list* list_c);

/*
	Gets the struct object pointer of the node
*/
object* node_get_object(node* n_p);

/*
	Gets the next node of the linked list struct object_list
*/
node* node_get_next(node* n_p);

/*
	Adds amount to count, allows negatives numbers
*/
void object_list_count(object_list* list, int add_amount);
#endif


