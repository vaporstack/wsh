
//  w_sgraph.c
//  w_sgraph
//
//  Created by Andrew Macfarlane on 15/10/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_sgraph_h_
#define w_sgraph_h_
#include "../geo/wsh_object.h"
#include "../geo/wsh_transform.h"

typedef struct WGraphNode
{
	int	foo;
	WTransform transform;
	WObject    art;

} WGraphNode;

WGraphNode* w_sgraph_create(void);
void	w_sgraph_destroy(WGraphNode* node);

#endif
