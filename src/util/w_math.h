//
//  w_math.h
//  wsh
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef w_math_h
#define w_math_h

#include "../geo/w_point.h"
#include <math.h>

static inline double w_dist2d(double x1, double y1, double x2, double y2)
{
	return sqrt((fabs(x1 - x2)) * (fabs(x1 - x2)) +
		    (fabs(y1 - y2)) * (fabs(y1 - y2)));
}

static inline double w_dist2d_p(WPoint* a, WPoint* b)
{
	return sqrt((fabs(a->x - b->x)) * (fabs(a->x - b->x)) +
		    (fabs(a->y - b->y)) * (fabs(a->y - b->y)));
}

static inline double w_dist2d_wp(WPoint* a, WPoint* b)
{
	return sqrt((fabs(a->x - b->x)) * (fabs(a->x - b->x)) +
		    (fabs(a->y - b->y)) * (fabs(a->y - b->y)));
}

#endif /* w_math_h */
