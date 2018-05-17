//
//  wsh_math.h
//  wsh
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef wsh_math_h
#define wsh_math_h

#include "../geo/wsh_point.h"
#include <math.h>

static inline double w_dist2d(double x1, double y1, double x2, double y2)
{
	return sqrt((fabs(x1 - x2)) * (fabs(x1 - x2)) +
		    (fabs(y1 - y2)) * (fabs(y1 - y2)));
}

static inline double wsh_dist2d_p(WPoint* a, WPoint* b)
{
	return sqrt((fabs(a->x - b->x)) * (fabs(a->x - b->x)) +
		    (fabs(a->y - b->y)) * (fabs(a->y - b->y)));
}

static inline double wsh_dist2d_wp(WPoint* a, WPoint* b)
{
	return sqrt((fabs(a->x - b->x)) * (fabs(a->x - b->x)) +
		    (fabs(a->y - b->y)) * (fabs(a->y - b->y)));
}

static inline double wsh_radians_to_degrees(double angle)
{
	return angle * (180 / M_PI);
}

static inline double wsh_degrees_to_radians(double angle)
{
	return angle * (M_PI / 180);
}

static inline double wsh_angle_from_points(double ax, double ay, double bx, double by)
{

	double dx    = bx - ax;
	double dy    = by - ay;
	double angle = atan2(dy, dx);
	return angle;
}

#endif /* wsh_math_h */
