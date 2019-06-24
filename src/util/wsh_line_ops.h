
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

/** 	\fn wsh_line_ops_dedupe
 *
 *	\brief return a copy of the line, duplicates removed.
 *	\param line  WLine to be deduplicated
 *	\todo make it return the same line and self cleanup?
 */
WLine* wsh_line_ops_dedupe(WLine* line);

/** 	\fn wsh_line_ops_dedupe_inplace
 *
 *	\brief remove any duplicate points in-place
 *	\param line  WLine to be deduplicated
 *	\todo implement the damn thing lol
 */
void wsh_line_ops_dedupe_inplace(WLine* line);

/**
 *
 *	method to check if the line has any line segments > delta
 *
 */
bool wsh_line_ops_subdivide_needed(WLine* line, double delta);

/**
 *
 *	return a segmented copy of the line, with divisions size delta
 *
 */
WLine* wsh_line_ops_subdivide(WLine* line, double delta);
void wsh_line_ops_smooth_inplace(WLine* line, double delta);
WLine* wsh_line_ops_simplify(WLine* line, double delta);
WLine* wsh_line_ops_douglaspeucker(WLine* line, double delta);

/*
*
*	return an imitation of the input line
*
*/

WLine* wsh_line_imitate(WLine* line, double time_variance, double dist_variance);

/**
 *
 *	return the angle of the start and end points of the line
 *
 */
double wsh_line_ops_angle(WLine* l);

/**
 *
 *	return the total length of a line
 *
 */
double wsh_line_ops_sum(WLine*);

/**
 *
 *	simply return the delta of start and end points of a line, for straightish lines mostly
 *
 */
double wsh_line_ops_length_simple(WLine* line);

/**
 *
 *	take a line and project it to be straight from start to end (copies)
 *
 */
WLine* wsh_line_ops_straighten_bruteforce(WLine* line, double theta);

/**
 *
 *	take a line and map it to points a, b
 *
 */
WLine* wsh_line_ops_map(WLine* line, WPoint a, WPoint b);

/*
*
*	take a line and try hilariusly to fit it to another line.
*
*/

WLine* wsh_line_ops_remap(WLine* src, WLine* target);

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
