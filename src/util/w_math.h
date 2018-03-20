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

<<<<<<< HEAD

 
static inline double dist2d(double x1, double y1, double x2, double y2)
=======
/*
 
static  double dist2d(double x1, double y1, double x2, double y2)
>>>>>>> 8db3a3a219f80087e176ddd31b6c0294b78305da
{
	return sqrt((fabs(x1 - x2)) * (fabs(x1 - x2)) +
		    (fabs(y1 - y2)) * (fabs(y1 - y2)));
}

<<<<<<< HEAD
static inline double dist2d_p(WPoint* a, WPoint* b)
=======
static  double dist2d_p(WPoint* a, WPoint* b)
>>>>>>> 8db3a3a219f80087e176ddd31b6c0294b78305da
{
	return sqrt((fabs(a->x - b->x)) * (fabs(a->x - b->x)) +
		    (fabs(a->y - b->y)) * (fabs(a->y - b->y)));
}

<<<<<<< HEAD
static inline double dist2d_wp(WPoint* a, WPoint* b)
=======
static  double dist2d_wp(WPoint* a, WPoint* b)
>>>>>>> 8db3a3a219f80087e176ddd31b6c0294b78305da
{
	return sqrt((fabs(a->x - b->x)) * (fabs(a->x - b->x)) +
		    (fabs(a->y - b->y)) * (fabs(a->y - b->y)));
}
<<<<<<< HEAD
=======
*/

>>>>>>> 8db3a3a219f80087e176ddd31b6c0294b78305da
#endif /* w_math_h */
