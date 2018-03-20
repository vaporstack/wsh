
//  w_node.c
//  w_node
//
//  Created by Andrew Macfarlane on 09/09/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "w_node.h"

WNode* w_node_create(WNode* parent)
{
	WNode* rec  = calloc(1, sizeof(WNode));
	rec->parent = parent;

	return rec;
}

void w_node_destroy(WNode* node)
{
	for (int i = 0; i < node->num_children; i++) {
		WNode* child = &node->children[i];
		w_node_destroy(child);
		child = NULL;
	}
}
