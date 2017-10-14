
//  w_brush.c
//  w_brush
//
//  Created by Andrew Macfarlane on 12/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "w_brush.h"

#include <stdbool.h>
#include <stdio.h>

#include <math.h>
#include <string.h>

#include "../util/w_line_ops.h"
#include "../util/w_gpc.h"
#include <r4/src/core/c_math.h>



void	w_brush_update_custom(WBrush* brush, brush_update_func cb);

void	w_brush_update_new_slow(WBrush* brush);
void	w_brush_update_old_fast(WBrush* brush);

WBrush* w_brush_create( struct WLineHnd* ref, double width)
{
	WBrush* brush = calloc(1, sizeof(WBrush));
	brush->hnd = ref;
	brush->needs_update = true;
	brush->data = NULL;
	brush->data = 0;
	brush->stroke = NULL;
	brush->width = width;
	brush->update_func = NULL;
	
	return brush;
}


WBrush* w_brush_copy( struct WBrush* old, struct WLineHnd* hnd)
{
	
	if( old == NULL )
	{
		printf("tried to copy a null brush\n");
		return NULL;
	}
	
	//WBrush* old = src->brush;
	if (!old )
		return NULL;
	
	WBrush* brush = w_brush_create(hnd, old->width);
	brush->needs_update = old->needs_update;
	
	if ( old->stroke )
	{
		//brush->stroke = calloc(1, sizeof(WLine));
		brush->stroke = w_line_copy(old->stroke);
		//memcpy(brush->stroke, old->stroke, sizeof(WLine));
	}
	
	brush->hnd = hnd;
	printf("Copied a brush for line %p\n", old);
	if(old->stroke)
	{
		if ( old->stroke->tess	)
		{
			w_gpc_tess_create(brush->stroke);
		}
	}
	
	return brush;
	
}


void		w_brush_destroy(WBrush* brush)
{
	//free(brush->hnd);
	brush->hnd->src = NULL;
	free(brush->data);
	//printf("Destroying a brush for line %p\n", brush->hnd);
	//free(brush);
}

/*
 static inline float angle_from_points(int x1, int y1, int x2, int y2)
 {
 float dx = x2 - x1;
 float dy = y2 - y1;
 float angle = atan2(dy,dx);
 //return atan2(dy, dx);
 
 
 
 if (dy < 0 ) {
 angle += 2 * (float)M_PI;
 }
 // map to [0, 1] range
 angle /= (2 * (float)M_PI);
 angle *= 360;
 angle -= 270;
 return angle;
 }
 
 
 static inline float angle_from_points_p(WPoint a, WPoint b)
 {
 return angle_from_points(a.x,a.y, b.x,b.y);
 }
 
 */


/*
 
 static inline float deg2rad(float input){
 
 return M_PI * input / 180 ;
 }
 
 */


//#define mult .125


void		w_brush_update_custom(WBrush* brush, brush_update_func func)
{
	func(brush);
}


void		w_brush_update(WBrush* brush)
{
	if ( brush->update_func )
	{
		brush_update_func f = (brush_update_func) brush->update_func;
		
		f(brush);
	}else{
		//w_brush_update_new_slow( brush);
		w_brush_update_old_fast(brush);
	}
}
	


static void _brush_tangents(WBrush* brush, WPoint a, WPoint b, double* lx, double* ly, double* rx, double *ry)
{
	
	double ang  = deg2rad(angle_from_points_p(a, b));
	double ps = a.pressure;
	
	*lx = a.x - ( ps * cos(ang) * brush->width);
	*ly = a.y - ( ps * sin(ang) * brush->width);
	
	*rx = b.x + ( ps * cos(ang) * brush->width);
	*ry = b.y + ( ps * sin(ang) * brush->width);
	
}

void	w_brush_update_new_slow(WBrush* brush)
{
	if ( !brush ) {
		printf("oops");
		//		oops
		return;
		
	}
	
	//printf("Updating brush!\n");
	
	
	double nx, ny;
	double px, py;
	double x, y;
	px = py = x = y = nx = ny = 0;
	WLine* src = brush->hnd->src;
	
	WLine* cpy = w_line_copy(src);
	w_line_ops_smooth(cpy, 4);
	printf("cpy line for brush has %llu points\n", cpy->num);
	printf("src line for brush has %llu points\n", src->num);
	WLine* stroke = w_line_create();
	for ( int i = 0 ; i < cpy->num-1; i++ )
	{
		
		WPoint p = cpy->data[i];
		
		x = p.x;
		y = p.y;
		
		WPoint np = cpy->data[i+1];
		
		nx = np.x;
		ny = np.y;
		
		//	first
		if ( i == 0 )
		{
			w_line_add_point(stroke, p);
		}
		
		
		if ( i > 0 && i < cpy->num-1 )
		{
			
			double lx;
			double ly;
			double rx, ry;
			
			_brush_tangents(brush, p, np, &lx, &ly, &rx, &ry);
			
			WPoint* l = w_point_create_2f(lx, ly);
			WPoint* r = w_point_create_2f(rx, ry);
			w_line_add_point(stroke, *l);
			w_line_add_point(stroke, *r);
			
		}
		
		if ( i == cpy->num-2)
		{
			w_line_add_point(stroke, p);
		}
		
		
		
		stroke->closed = true;
		stroke->has_fill = true;
		stroke->has_stroke = true;
		stroke->fill.r = 1;
		stroke->fill.g = 0;
		stroke->fill.b = 1;
		stroke->fill.a = .5;
		
		
		if(brush->stroke )
		{
			w_line_destroy(brush->stroke);
		}
		
		brush->stroke = stroke;
		printf("Created stroke with %llu points\n", stroke->num);
		
	}
	
	brush->needs_update = false;
	
}

void	w_brush_update_old_fast(WBrush* brush)
{
	if ( !brush ) {
		printf("oops");
		//		oops
		return;
		
	}
	
	//printf("Updating brush!\n");
	
	//	todo make this not horrible
	WLine* left = w_line_create();
	WLine* right = w_line_create();
	
	WLine* l = brush->hnd->src;
	if ( !l )
		return;
	
	if ( l->num < 2 )
		return;
	unsigned long long num = l->num;
	
	for ( int i = 0 ; i < num ; ++i )
	{
		WPoint p = l->data[i];
		double ps = p.pressure;
		
		double ang = 0;
		if ( i > 1 )
		{
			WPoint before = l->data[i-1];
			double d = deg2rad(angle_from_points_p(p, before));
			ang += d;
		}
		
		WPoint p1, p2;
		
		w_point_zero(&p1);
		w_point_zero(&p2);
		
		p1.x = p.x - ( ps * cos(ang) * brush->width);
		p1.y = p.y - ( ps * sin(ang) * brush->width);
		
		p2.x = p.x + ( ps * cos(ang) * brush->width);
		p2.y = p.y + ( ps * sin(ang) * brush->width);
		
		w_line_add_point(left, p1);
		w_line_add_point(right, p2);
	}
	
	
	WLine* stroke = w_line_copy(left);
	for ( signed long long i = right->num-1 ; i > 0; i-- )
	{
		w_line_add_point(stroke, right->data[i]);
	}
	
	//r_color(0,0,0,.5);
	
	stroke->closed = true;
	stroke->has_fill = true;
	stroke->has_stroke = true;
	stroke->fill.r = 1;
	stroke->fill.g = 0;
	stroke->fill.b = 1;
	stroke->fill.a = .5;
	
	//	IMPORTANT
	w_line_ops_smooth(stroke, 4);
	w_gpc_tess_create(stroke);
	w_line_ops_smooth(stroke, 8);
	
	
	//r_poly(stroke);
	
	w_line_destroy(left);
	w_line_destroy(right);
	
	
	if(brush->stroke )
	{
		w_line_destroy(brush->stroke);
	}
	brush->stroke = stroke;
	
	brush->needs_update = false;
	
	
}

