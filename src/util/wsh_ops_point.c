//
//  wsh_ops_point.c
//  wsh
//
//  Created by vs on 5/14/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include "wsh_ops_point.h"

#include "wsh_math.h"

double wsh_ops_point_dist(WPoint a, WPoint b)
{
	return wsh_dist2d_wp(&a, &b);
}
