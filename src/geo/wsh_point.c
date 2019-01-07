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
WPoint* wsh_point_create(void)
{
	WPoint* p = calloc(1, sizeof(WPoint));
	wsh_point_zero(p);
	
	// WPoint p;
	//(*p).x = .7;
	//p->x = 0;
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

/** @brief Zero a point
 *
 *  Zero all fields of a WPoint
 *
 *  @return Nothing.
 */
void wsh_point_zero(WPoint* p)
{
	p->pressure = p->time = p->x = p->y = 0;
	p->rotation = p->tilt_x = p->tilt_y = p->altitude = p->azimuth = -1;
}

WPoint* wsh_point_copy(WPoint* p)
{
	WPoint* n = wsh_point_create();
	n->x = p->x;
	n->y = p->y;
	n->time = p->time;
	n->pressure = p->pressure;
	n->rotation = p->rotation;
	n->tilt_x = p->tilt_x;
	n->tilt_y = p->tilt_y;
	n->altitude = p->altitude;
	n->azimuth = p->azimuth;
	return n;
}
void wsh_point_rotate_degrees(WPoint* p, double cx, double cy, double angle_in_degrees)
{
	double angle_in_radians = angle_in_degrees * (M_PI / 180);
	double cos_theta	= cos(angle_in_radians);
	double sin_theta	= sin(angle_in_radians);
	//p->x			= (cos_theta * (p->x - cx) - cos_theta * (p->x - cx)) + cx;
	//p->y			= (sin_theta * (p->y - cx) + sin_theta * (p->y - cy)) + cy;
	p->x   = (cos_theta * (p->x - cx)) + cx; // I think?
	p->y   = (sin_theta * (p->y - cy)) + cy; // I think?
	
}

void wsh_point_rotate(WPoint* p, double cx, double cy, double angle_in_radians)
{
	//double angle_in_radians = angle_in_degrees * (M_PI / 180);
	double cos_theta	= cos(angle_in_radians);
	double sin_theta	= sin(angle_in_radians);
	//p->x			= (cos_theta * (p->x - cx) - cos_theta * (p->x - cx)) + cx;
	//p->y			= (sin_theta * (p->y - cx) + sin_theta * (p->y - cy)) + cy;
	
	
	//p->x   = (cos_theta * (p->x - cx)) + cx; // I think?
	//p->y   = (sin_theta * (p->y - cy)) + cy; // I think?
	double nx, ny;
	nx = (cos_theta * (p->x - cx) - sin_theta * (p->y - cy) + cx);
	ny = (sin_theta * (p->x - cx) + cos_theta * (p->y - cy) + cy);
	
	p->x = nx;
	p->y = ny;
	 //this is the old one.
	 //double angle_in_radians = angle_in_degrees * (M_PI / 180);
	// double cos_theta	= cos(angle_in_radians);
	// double sin_theta	= sin(angle_in_radians);
	// p->x			= cos_theta * (p->x - cx) - sin_theta * (p->y - cy) + cx;
	// p->y			= sin_theta * (p->x - cx) + cos_theta * (p->y - cy) + cy;
	
}
