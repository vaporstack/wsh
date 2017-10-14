//
//  w_transform.c
//  wash
//
//  Created by Andrew Macfarlane on 1/2/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "w_transform.h"


void	w_transform_reset(WTransform* t)
{
	t->anchor.x = t->anchor.y = t->anchor.z = 0;
	t->position.x = t->position.x = t->position.z = 0;
	t->rotation.x = t->rotation.y = t->rotation.z = 0;
	t->scale.x = t->scale.y = t->scale.z = 1;
	t->opacity = 1.;
	
	
}

void 	w_transform_apply(WTransform* t)
{
	
	
}

void 	w_transform_deapply(WTransform* t)
{
	
	
}


