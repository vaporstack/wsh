
//  w_brush.c
//  w_brush
//
//  Created by Andrew Macfarlane on 12/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_brush_h_
#define w_brush_h_

#include "../geo/w_line.h"
#include <stdbool.h>

enum
{
	W_BRUSH_TYPE_NONE,
	W_BRUSH_TYPE_FULL,
	W_BRUSH_TYPE_DISTANCE,
	W_BRUSH_TYPE_RIDIC
};

typedef struct WBrush
{
	int brush_type;
	bool needs_update;
	double width;
	struct WLineHnd * hnd;
	struct WLine* stroke;
	double* data;
	void*	extra;
	unsigned long num;
	void* update_func;
} WBrush;

typedef void (*brush_update_func)(WBrush*);


void		w_brush_update_custom(WBrush* brush, brush_update_func func);

struct WBrush*	w_brush_create( struct WLineHnd* hnd, double width);
struct WBrush*	w_brush_copy( struct WBrush* brush, struct WLineHnd* hnd);
void		w_brush_destroy(struct WBrush* );
void		w_brush_update(WBrush* );
void		w_brush_draw(WBrush* );

#endif
