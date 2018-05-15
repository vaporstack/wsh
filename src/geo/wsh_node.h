
//  w_node.c
//  w_node
//
//  Created by Andrew Macfarlane on 09/09/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_node_h_
#define w_node_h_

#include "wsh_object.h"

typedef struct WNode
{
	WObject*      art;
	struct WNode* parent;
	struct WNode* children;
	struct WNode* next;
	struct WNode* prev;
	int	   num_children;

} WNode;

WNode* w_node_create(WNode* parent);
void   w_node_destroy(WNode* node);

#endif
