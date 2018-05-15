//
//  wsh_point.c
//  wash
//
//  Created by Andrew Macfarlane on 12/9/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#include "wsh_point.h"
#include "../wsh_includes.h"

/** @brief Create a point, on the heap.
 *
 *  Create a point
 *
 *  @return The point structure, allocated on heap.
 */

WPoint* wsh_point_create()
{
	WPoint* p = calloc(1, sizeof(WPoint));
	// WPoint p;
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

WPoint* wsh_point_create_2f(double x, double y)
{
	WPoint* p = wsh_point_create();
	p->x      = x;
	p->y      = y;
	return p;
}

void wsh_point_zero(WPoint* p)
{
	p->pressure = p->rotation = p->tilt_x = p->tilt_y = p->time = p->x = p->y = 0;
}

void wsh_point_rotate(WPoint* p, double cx, double cy, double angle_in_degrees)
{
	double angle_in_radians = angle_in_degrees * (M_PI / 180);
	double cos_theta	= cos(angle_in_radians);
	double sin_theta	= sin(angle_in_radians);
	p->x			= (cos_theta * (p->x - cx) - sin_theta * (p->x - cy)) + cx;
	p->y			= (sin_theta * (p->y - cx) + cos_theta * (p->y - cy)) + cy;
}
