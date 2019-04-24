//
//  wsh_rect.c
//  wash
//
//  Created by Andrew Macfarlane on 1/2/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "wsh_rect.h"

#include <math.h>

WRect wsh_rect_create_impossible(void)
{
	WRect r;
	r.pos.x = r.pos.y = INFINITY;
	r.size.x =r.size.y = -INFINITY;
	return r;
}

void wsh_rect_union(WRect* dst, WRect a, WRect b)
{
	//double minx, miny, maxx, maxy;
	//minx = miny = INFINITY;
	//maxx = maxy = -INFINITY;
	dst->pos.x = ( a.pos.x < b.pos.x ) ? a.pos.x : b.pos.x;
	dst->pos.y = ( a.pos.y < b.pos.y ) ? a.pos.y : b.pos.y;
	dst->size.x = ( a.size.x > b.size.x ) ? a.size.x : b.size.x;
	dst->size.y = ( a.size.y > b.size.y ) ? a.size.y : b.size.y;
}


void wsh_rect_reset(WRect* bounds)
{
	bounds->pos.x  = 0;
	bounds->pos.y  = 0;
	bounds->size.x = 0;
	bounds->size.y = 0;
}


int wsh_rect_within_bounds(WRect* bounds, double x, double y)
{
	return (x >= bounds->pos.x && y >= bounds->pos.y && x <= bounds->pos.x + bounds->size.x && y <= bounds->pos.y + bounds->size.y);
}
