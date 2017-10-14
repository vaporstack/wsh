//
//  w_line.h
//  wash
//
//  Created by Andrew Macfarlane on 12/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#ifndef w_line_h
#define w_line_h

#include <stdbool.h>

#include "../w_includes.h"

#include "w_transform.h"
#include "w_rect.h"

#include "w_point.h"	
#include "w_color.h"
#include "../decor/w_brush.h"

typedef struct WLine
{
	bool closed;
	bool has_stroke;
	bool has_fill;
	unsigned long long num;
	unsigned long long reserved;
	void*	tess;
	WPoint* data;
	//	todo:
	//	refactor to have the brush owned elsewhere, it is not a core datatype
	struct WBrush* brush;
	WColor fill;
	WColor stroke;
	WRect bounds;
	WTransform transform;
} WLine;

typedef struct WLineHnd
{
	WLine* src;

} WLineHnd;

typedef unsigned long long ull;

WLineHnd*	w_line_hnd_create(void);
WLineHnd*	w_line_hnd_copy(WLineHnd*);

//	todo: ask people what the convention is here
void		w_line_copy_attribs(WLine* to, WLine* from);
void 		w_line_hnd_destroy(WLineHnd*);
void		w_line_hnd_add_point(WLineHnd, WPoint);

void		w_line_offset(WLine* src, double x, double y);
void		w_line_scale(WLine* src, double x, double y);

void		w_line_find_mins(WLine* src, double* x, double* y);
void		w_line_find_maxs(WLine* src, double* x, double* y);

WLine*		w_line_create(void);
WLine* 		w_line_copy(WLine*);
void		w_line_concat(WLine* dst, WLine* src, ull, ull);

void 		w_line_destroy(WLine* );

void 		w_line_add_point(WLine*, WPoint );

WLine* 		w_line_normalize(WLine*, double* dx, double* dy);
void 		w_line_normalize_inplace(WLine*, double* dx, double* dy);

#endif /* w_line_h */
