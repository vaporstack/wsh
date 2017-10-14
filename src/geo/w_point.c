//
//  w_point.c
//  wash
//
//  Created by Andrew Macfarlane on 12/9/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#include "w_point.h"
#include "../w_includes.h"


/** @brief Create a point, on the heap.
 *
 *  Create a point
 *
 *  @return The point structure, allocated on heap.
 */

WPoint* w_point_create(){
	WPoint* p = calloc(1, sizeof(WPoint));
	//WPoint p;
	//(*p).x = .7;
	p->x = 0;
	return p;
}


/** @brief Create a point, on the heap.
 *
 *  Create a point from two coordinates.
 *
 *  @param x The x coordinate
 *  @param y The y coordinate
 *  @return The point structure, allocated on heap.
 */

WPoint* w_point_create_2f(double x, double y)
{
	WPoint* p = w_point_create();
	p->x = x;
	p->y = y;
	return p;

}

void	w_point_zero(WPoint* p)
{
	p->pressure = p->rotation = p->tilt_x = p->tilt_y = p->time = p->x = p->y = 0;
}

