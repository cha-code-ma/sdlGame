/*

*/
#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H
#include "structs.h"

object_list* object_list_init(void);

node* node_init(sub_object* sub_obj);

void free_node(node* n);

node* node_remove_List(node* n_p, object_list* list);

int node_insert(object_list* list_c, node* n_p);


void free_object_list(object_list* list_c);
#endif


