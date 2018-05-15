//
//  wsh_transform.c
//  wash
//
//  Created by Andrew Macfarlane on 1/2/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "wsh_transform.h"

void wsh_transform_reset(WTransform* t)
{
	t->anchor.x = t->anchor.y = t->anchor.z = 0;
	t->position.x = t->position.x = t->position.z = 0;
	t->rotation.x = t->rotation.y = t->rotation.z = 0;
	t->scale.x = t->scale.y = t->scale.z = 1;
	t->opacity			     = 1.;
}

void wsh_transform_apply(WTransform* t){

};

void wsh_transform_deapply(WTransform* t)
{
}
