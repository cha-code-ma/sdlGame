/*

*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <stdbool.h>
#include "object.h"
#include "structs.h"


object_list* object_list_init(void) {
	object_list* l_c = malloc(sizeof(object_list));
	if (!l_c) {
		return NULL;
	}
	l_c->start_node = NULL;
	l_c->count = 0;
	return l_c;
}

node* node_init(sub_object* sub_obj) {
	node* n = malloc(sizeof(node));
	if (!n) {
		return NULL;
	}
	n->sub_obj = sub_obj;
	n->next = NULL;
	return n;
}

void free_node(node* n) {
	if (!n) {
		return;
	}
	if (n->sub_obj) {
		free(n->sub_obj);
	}
	free(n);
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
		free_node(current_node);
		current_node = temp_node;
	}
	free(list_c);
}
