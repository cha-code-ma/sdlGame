/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include "object.h"
#include "physics.h"

struct object_list {
	node* start_node;
	size_t count;

};

struct node {
	object* character;
	struct node* next;
};


object_list* object_list_init(void) {
	object_list* l_c = malloc(sizeof(object_list));
	if (!l_c) {
		return NULL;
	}
	l_c->start_node = NULL;
	l_c->count = 0;
	return l_c;
}

void object_list_count(object_list* list, int add_amount) {
	if (!list) {
		return;
	}
	list->count += add_amount;
}

node* object_list_get_start_node(object_list* list) {
	return list->start_node;
}

node* node_init(object* s_p) {
	node* n_p = malloc(sizeof(node));
	if (!n_p) {
		return NULL;
	}
	n_p->character = s_p;
	n_p->next = NULL;
	return n_p;
}

void node_delete(node* n_p) {
	if (!n_p) {
		return;
	}
	if (n_p->character) {
		free(n_p->character);
	}
	free(n_p);
}


node* node_remove_List(node* n_p, object_list* list) {
	if (!n_p || !list || !list->start_node) {
		return NULL;
	}
	node* current_node = list->start_node;
	if (current_node == n_p) {
		if (current_node->next) {
			list->start_node = current_node->next;
		}
		return current_node;
	}
	if (!current_node->next) {
		return NULL;
	}
	node* before_node = current_node;
	current_node = current_node->next;
	while (current_node) {
		if (current_node == n_p) {
			if (current_node->next) {
				before_node->next = current_node->next;
				return current_node;
			}
			before_node->next = NULL;
			return current_node;
		}
		before_node = current_node;

		current_node = current_node->next;
	}
	return NULL;
}

int node_insert(object_list* list_c, node* n_p) {
	if (!list_c || !n_p) {
		return 0;
	}
	if (!list_c->start_node) {
		list_c->start_node = n_p;
		return 1;
	}
	node* current_node = list_c->start_node;

	while (current_node) {
		if (!current_node->next) {
			current_node->next = n_p;
			list_c->count++;
			return 1;
		}
		current_node = current_node->next;
	}
	return 0;
}


void free_object_list(object_list* list_c) {
	if (!list_c) {
		return;
	}
	if (!list_c->start_node) {
		free(list_c);
		return;
	}

	node* current_node = list_c->start_node;

	while (current_node) {
		node* temp_node = current_node->next;
		node_delete(current_node);
		current_node = temp_node;
	}
	free(list_c);
}


object* node_get_object(node* n_p) {
	return n_p->character;
}

node* node_get_next(node* n_p) {
	return n_p->next;
}
