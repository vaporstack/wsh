
//  w_line_ops.c
//  w_line_ops
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_line_ops_h_
#define w_line_ops_h_

#include "../geo/w_line.h"

WLine*	w_line_ops_dedupe(WLine*);
WLine*	w_line_ops_subdiv(WLine*, double);
WLine*	w_line_ops_smooth(WLine*, double);
WLine*	w_line_ops_simplify(WLine*, double);
WLine*	w_line_ops_douglaspeucker(WLine*, double);
double	w_line_ops_sum(WLine*);

#endif
