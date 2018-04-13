//
//  ops.c
//  wash-demo
//
//  Created by vs on 4/7/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "ops.h"
#include "../wash_demo_common.h"
#include <stdlib.h>


void scale_object_to_window(WObject* obj)
{
	w_object_calc_bounds(obj);
	WRect bounds = obj->bounds;
	
	//shift it so lower left corner is 0,0
	w_object_move(obj, bounds.pos.x * -1, bounds.pos.y * -1);
	w_object_calc_bounds(obj);

	
	double dx = obj->bounds.size.x / frame_h;
	double dy = obj->bounds.size.y / frame_w;
	
	dx = window_w / obj->bounds.size.x;
	dy = window_h / obj->bounds.size.y;
	
	
	printf("Should scale object to %f %f\n", dx, dy);

	double d = (dx > dy ) ? dx : dy;

	w_object_scale(obj, d, d );

	w_object_calc_bounds(obj);
	
}

void scale_sequence_to_window(WSequence* seq )
{
	//w_sequence_normalize(document.src->sequence.src);
	//WSequence* seq = document.src->sequence.src;
	w_sequence_calc_bounds(seq);
	WRect bounds = seq->bounds;
	
	//shift it so lower left corner is 0,0
	w_sequence_move(seq, bounds.size.x * 1, bounds.size.y * 1);
	w_sequence_calc_bounds(seq);
	
	
	
	double dx = seq->bounds.size.x / frame_h;
	double dy = seq->bounds.size.y / frame_w;
	
	dx = window_w / seq->bounds.size.x;
	dx = window_h / seq->bounds.size.y;
	
	printf("Should scale sequence to %f %f\n", dx, dy);
	//	dx here twice on purpose for testing
	w_sequence_scale(seq, dx, dx);
	
	w_sequence_calc_bounds(seq);
	//w_sequence_move(seq, frame_h* -.5, frame_w * -.5);
	w_sequence_calc_bounds(seq);
}
