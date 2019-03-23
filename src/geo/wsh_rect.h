//
//  wsh_rect.h
//  wash
//
//  Created by Andrew Macfarlane on 1/2/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef wsh_rect_h
#define wsh_rect_h

#include "wsh_point.h"

//	todo : kill this?
typedef struct
{
	WPoint pos;
	WPoint size;
} WRect;


WRect wsh_rect_create_impossible(void);
void wsh_rect_union(WRect* dst, WRect a, WRect b);
void wsh_rect_reset(WRect* bounds);
int  wsh_rect_within_bounds(WRect* bounds, double x, double y);

#endif /* wsh_rect_h */
