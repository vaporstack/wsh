
//  w_line_ops.c
//  w_line_ops
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_line_ops_h_
#define w_line_ops_h_

#include "../geo/w_line.h"

//	todo: clarify (decide) whether all of these operations
//	work in-place or if they actually return a modified copy
//	right now it's like 50/50.  probably should return copies
//	across the board

WLine* w_line_ops_dedupe(WLine*);
WLine* w_line_ops_subdiv(WLine*, double);
WLine* w_line_ops_smooth(WLine*, double);
WLine* w_line_ops_simplify(WLine*, double);
WLine* w_line_ops_douglaspeucker(WLine*, double);
double w_line_ops_sum(WLine*);

bool w_line_ops_rect_intersects(WLine* line, WRect* rect);
bool w_line_ops_rect_contains(WLine* line, WRect* rect);

#endif
