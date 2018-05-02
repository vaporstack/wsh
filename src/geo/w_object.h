//
//  w_object.h
//  wash
//
//  Created by Andrew Macfarlane on 12/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#ifndef w_object_h
#define w_object_h

#include "../w_includes.h"

//#include <stdbool.h>

#include "w_line.h"
#include "w_rect.h"
#include "w_transform.h"

typedef struct WObject
{
	//	todo: clean this up!
	bool		normalized;
	int		num_lines;
	WLine**		lines;
	struct WObject* parent;
	WRect		bounds;
	WTransform      transform;
} WObject;

typedef struct WObjectHnd
{
	bool     valid;
	WObject* src;
} WObjectHnd;

unsigned long long w_object_sum_points(WObject* obj);

WObjectHnd w_object_hnd_create(WObject* parent);
WObjectHnd w_object_hnd_destroy(WObjectHnd* hnd);
WObjectHnd w_object_hnd_copy(WObjectHnd* hnd);

WObject* w_object_create(WObject* parent);
void     w_object_destroy(WObject* obj);
void     w_object_destroy_void(void* obj);

void w_object_add_line(WObject*, WLine*);
void w_object_remove_line(WObject*, WLine*);

void     w_object_center(WObject* obj);
WObject* w_object_copy(WObject* obj);
WObject* w_object_copy_from_percentage(WObject* obj, double t);

//	all lines in the frame are drawn consecutively
void w_object_normalize_time_continuous(WObject* obj);

//	all lines in the frame draw at once at the same rate
void w_object_normalize_time_exploded(WObject* obj);

//	all lines in the frame draw at timed to the line that took the longest to draw
void w_object_normalize_time_exploded_accurate(WObject* obj);


void     w_object_normalize(WObject* obj);
void     w_object_simplify(WObject*, double r);
void     w_object_douglaspeucker(WObject*, double r);
void	w_object_scale(WObject* obj, double modx, double mody);
void w_object_move(WObject* obj, double dx, double dy);
void w_object_calc_bounds(WObject*);
void w_object_set_closed(WObject* obj, bool val);

/*
void		w_object_frame_next(WObject*);
void		w_object_frame_prev(WObject*);
WObject*	w_object_frame_create(WObject* obj, int pos);
void		w_object_frame_delete(WObject* obj, int pos);

*/

#endif /* w_object_h */
