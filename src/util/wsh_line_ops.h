
//  wsh_line_ops.c
//  wsh_line_ops
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef wsh_line_ops_h_
#define wsh_line_ops_h_

#include "../geo/wsh_line.h"

//	todo: clarify (decide) whether all of these operations
//	work in-place or if they actually return a modified copy
//	right now it's like 50/50.  probably should return copies
//	across the board

WLine* wsh_line_ops_dedupe(WLine*);
WLine* wsh_line_ops_subdiv(WLine*, double);
WLine* wsh_line_ops_smooth(WLine*, double);
WLine* wsh_line_ops_simplify(WLine*, double);
WLine* wsh_line_ops_douglaspeucker(WLine*, double);

/**
 *
 *	return the total length of a line
 *
 */
double wsh_line_ops_sum(WLine*);

/**
 *
 *	simple return the delta of start and end points of a line, for straightish lines mostly
 *
 */
double wsh_line_ops_length(WLine* line);

/**
 *
 *	take a line and project it to be straight from start to end (copies)
 *
 */
WLine* wsh_line_ops_straighten(WLine* line);

/**
 *
 *	take a line and map it to points a, b
 *
 */
WLine* wsh_line_ops_map(WLine* line, WPoint a, WPoint b);

/*
 *
 *	test to see if a line intersects a rect
 *
 */
bool wsh_line_ops_rect_intersects(WLine* line, WRect* rect);

/*
 *
 *	test to see if a line is fully contained in a rect
 *
 */

bool wsh_line_ops_rect_contains(WLine* line, WRect* rect);

#endif
