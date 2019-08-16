//
//  wsh_object.h
//  wash
//
//  Created by Andrew Macfarlane on 12/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#ifndef wsh_object_h
#define wsh_object_h

#include "../wsh_includes.h"

//#include <stdbool.h>

#include "wsh_line.h"
#include "wsh_rect.h"
#include "wsh_transform.h"

typedef struct WObject
{
	//	todo: clean this up!
	bool		normalized;
	unsigned long   num;
	WLine**		lines;
	//	removing this since I long ago decided this is purely a storage class
	//struct WObject* parent;
	WRect		bounds;
	WTransform      transform;
} WObject;

typedef struct WObjectHnd
{
	//bool     valid;
	WObject* src;
} WObjectHnd;

unsigned long long wsh_object_sum_points(WObject* obj);

WObjectHnd wsh_object_hnd_create(WObject* parent);
WObjectHnd wsh_object_hnd_destroy(WObjectHnd* hnd);
WObjectHnd wsh_object_hnd_copy(WObjectHnd* hnd);

WObject* wsh_object_create(void);
void     wsh_object_destroy(WObject* obj);
void     wsh_object_destroy_void(void* obj);

void wsh_object_add_line(WObject*, WLine*);
WLine* wsh_object_remove_line(WObject*, WLine*);

void     wsh_object_center(WObject* obj);
WObject* wsh_object_copy(WObject* obj);
WObject* wsh_object_copy_from_percentage(WObject* obj, double t);

//	find the earliest recorded point and shift everything up
void wsh_object_time_trim_head(WObject* obj);

//	all lines in the frame are drawn consecutively
void wsh_object_time_normalize_continuous(WObject* obj);

//	all lines in the frame draw at once at the same rate
void wsh_object_time_normalize_exploded(WObject* obj);

//	all lines in the frame draw at timed to the line that took the longest to draw
void wsh_object_time_normalize_exploded_accurate(WObject* obj);

void     wsh_object_center(WObject* obj);
WObject* wsh_object_copy(WObject* obj);
WObject* wsh_object_copy_from_percentage(WObject* obj, double t);

//	scale the object so that it has coordinates of 1
void     wsh_object_normalize(WObject* obj);
void     wsh_object_simplify(WObject*, double r);
void     wsh_object_douglaspeucker(WObject*, double r);
void     wsh_object_scale(WObject* obj, double modx, double mody);
void     wsh_object_translate(WObject* obj, double dx, double dy);
void     wsh_object_rotate(WObject* obj, double cx, double cy, double r);
void     wsh_object_calc_bounds(WObject*);
void     wsh_object_set_closed(WObject* obj, bool val);
void     wsh_object_transform_reset(WObject* obj);

/*
void		wsh_object_frame_next(WObject*);
void		wsh_object_frame_prev(WObject*);
WObject*	wsh_object_frame_create(WObject* obj, int pos);
void		wsh_object_frame_delete(WObject* obj, int pos);

*/

#endif /* wsh_object_h */
