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


#ifndef __APPLE__

#ifndef M_PI
#define M_E 2.71828182845904523536
#define M_LOG2E 1.44269504088896340736
#define M_LOG10E 0.434294481903251827651
#define M_LN2 0.693147180559945309417
#define M_LN10 2.30258509299404568402
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#define M_PI_4 0.785398163397448309616
#define M_1_PI 0.318309886183790671538
#define M_2_PI 0.636619772367581343076
#define M_1_SQRTPI 0.564189583547756286948
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2 1.41421356237309504880
#define M_SQRT_2 0.707106781186547524401
#endif

#endif


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

static inline double wsh_angle_from_points_p(WPoint* a, WPoint* b)
{
	
	double dx    = b->x - a->x;
	double dy    = b->y - a->y;
	double angle = atan2(dy, dx);
	return angle;
}

static inline double wsh_angle_from_points(double ax, double ay, double bx, double by)
{

	double dx    = bx - ax;
	double dy    = by - ay;
	double angle = atan2(dy, dx);
	return angle;
}

#endif /* wsh_math_h */
