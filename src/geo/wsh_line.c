//
//  wsh_line.c
//  wash
//
//  Created by Andrew Macfarlane on 12/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

/* -- Includes -- */

/* internal includes. */

#include "wsh_line.h"
#include "wsh_point.h"
#include <wsh/wsh.h>

#define LINE_START_SIZE 256
#define LINE_MAX_SIZE 1024

//#include "../util/w_gpc.h"
//#include "../util/wsh_line_ops.h"
#include <math.h>
#include <string.h>

WLineHnd* wsh_line_hnd_create(void)
{
	WLineHnd* hnd = calloc(1, sizeof(WLineHnd));
	return hnd;
}

WLineHnd* wsh_line_hnd_create_with_data(void)
{
	WLineHnd* hnd = calloc(1, sizeof(WLineHnd));
	hnd->src      = wsh_line_create_with_reserved(LINE_START_SIZE);
	return hnd;
}

WLineHnd* wsh_line_hnd_create_with_addr(WLine* addr)
{
	WLineHnd* hnd = calloc(1, sizeof(WLineHnd));
	hnd->src      = addr;
	return hnd;
}

WLineHnd* wsh_line_hnd_copy(WLineHnd* hnd)
{
	// todo implement this

	return NULL;
}

void wsh_line_hnd_destroy(WLineHnd* hnd)
{
	free(hnd->src);

	free(hnd);
	//	totally dead
}

WLine* wsh_line_create(void)
{
	WLine* l = calloc(1, sizeof(WLine));

	l->data       = 0;
	l->num	= 0;
	l->reserved   = 0;
	l->has_fill   = false;
	l->has_stroke = false;
	//l->tess       = NULL;
	//l->brush      = NULL;
	l->closed = false;
	l->z      = 0;

	WRect b;
	b.pos.x = b.pos.y = b.size.x = b.size.y = 0;
	l->bounds				= b;

	/*
	 WTransform t;
	 t.scale.x = t.scale.y = t.scale.z = 1;
	 t.position.x = t.position.y = t.position.z = 0;
	 t.rotation.x = t.rotation.y = t.rotation.z = 0;
	 t.opacity				   = 1;
	 t.anchor.x = t.anchor.y = t.anchor.z = 0;

	 l->transform = t;
	 */
	return l;
}

WLine* wsh_line_create_with_reserved(unsigned int num)
{
	WLine* l    = wsh_line_create();
	l->reserved = num;
	l->data     = calloc(l->reserved, sizeof(WPoint));
	return l;
}

void wsh_line_calc_bounds(WLine* src)
{
	double minx, miny, maxx, maxy;

	minx = miny = INFINITY;
	maxx = maxy = -INFINITY;

	for (int i = 0; i < src->num; ++i)
	{

		WPoint* p = &src->data[i];
		double  x = p->x;
		double  y = p->y;

		if (x < minx)
			minx = x;
		if (x > maxx)
			maxx = x;
		if (y < miny)
			miny = y;
		if (y > maxy)
			maxy = y;
	}

	src->bounds.pos.x  = minx;
	src->bounds.pos.y  = miny;
	src->bounds.size.x = maxx - minx;
	src->bounds.size.y = maxy - miny;
}
void wsh_line_add_point2f(WLine* line, double x, double y)
{
	WPoint p;
	p.x = x;
	p.y = y;
	wsh_line_add_point(line, p);
}

void wsh_line_add_point(WLine* line, WPoint p)
{
	if (!line)
	{
#ifdef DEBUG
		wsh_log("Cannot add to a NULL line!");
#endif
		return;
	}

	if (!line->data)
	{
		line->reserved = LINE_START_SIZE;
		//	leaky
		//line->data     = calloc(line->reserved, sizeof *line->data);
		line->data = calloc(line->reserved, sizeof(WPoint));
	}

	if (line->num == line->reserved)
	{
		(line->reserved) *= 2;
		//	line->data = realloc(line->data, sizeof *line->data * line->reserved);
		line->data = realloc(line->data, sizeof(WPoint) * line->reserved);
	}

	line->data[line->num] = p;

	line->num++;
}

// TODO move this somewhere higher level, line is a core data type and
// shouldn't know about
//	tesselation and such

//	update, this HAS been moved higher level
/*
 #ifdef DISABLE_UNTIL_WORKLINE_REFACTOR_COMPLETE

 if (line->closed)
 {
 if (line->tess)
 {
 w_gpc_tess_destroy(line);
 }

 w_gpc_tess_create(line);
 // wsh_line_ops_smooth(line->brush->stroke->tess, 8);
 if (line->brush)
 {
 if (line->brush->stroke)
 {
 // wsh_line_ops_smooth(line->brush->stroke->tess,
 // 8);
 }
 else
 {
 printf("!");
 }
 }
 }
 else
 {
 if (line->tess)
 {
 w_gpc_tess_destroy(line);
 }
 }
 #endif
 */
#include <assert.h>

void wsh_line_concat(WLine* dst, WLine* src)
{
	for (long i = 0; i < src->num; ++i)
	{
		wsh_line_add_point(dst, src->data[i]);
	}
}

void wsh_line_concat_range(WLine* dst, WLine* src, long start, long end)
{

	if (start < 0)
		start = 0;

	if (end < 0)
		end = src->num;

	assert(end > start);
	//while( start < end )
	for (long i = start; i < end; ++i)
	{
		wsh_line_add_point(dst, src->data[i]);
	}
}

WLine* wsh_line_copy(WLine* old)
{

	if (old == NULL)
	{
#ifdef DEBUG
		wsh_log("tried to copy a null line.");
#endif
		return NULL;
	}
	else if (old->data == NULL)
	{
#ifdef DEBUG
		wsh_log("Tried to copy a line with no data!");
#endif
		return NULL;
	}

	WLine* new      = wsh_line_create();
	new->num	= old->num;
	new->reserved   = old->reserved;
	new->data       = calloc(new->reserved, sizeof(WPoint)); //(sizeof *new->data) * new->reserved);
	new->has_fill   = old->has_fill;
	new->has_stroke = old->has_stroke;
	new->stroke     = old->stroke;
	new->fill       = old->fill;
	new->closed     = old->closed;
	new->fill       = old->fill;
	new->stroke     = old->stroke;
	new->bounds     = old->bounds;
	for (int i = 0; i < new->num; ++i)
	{

		new->data[i].x	= old->data[i].x;
		new->data[i].y	= old->data[i].y;
		new->data[i].pressure = old->data[i].pressure;
		new->data[i].tilt_x   = old->data[i].tilt_x;
		new->data[i].tilt_y   = old->data[i].tilt_y;
		new->data[i].rotation = old->data[i].rotation;
		new->data[i].time     = old->data[i].time;
	}

	//WLineHnd* new_hnd = wsh_line_hnd_create();
	//new_hnd->src      = new;

	//if (old->brush != NULL) {
	//	new->brush = w_brush_copy(old->brush, new_hnd);
	//}
	//	this will break
	// new->brush = old->brush;
	return new;
}

WLine* wsh_line_copy_percentage(WLine* old, double v)
{
	if (old == NULL)
	{
#ifdef DEBUG
		wsh_log("tried to copy a null line.");
#endif
		return NULL;
	}
	else if (old->data == NULL)
	{
#ifdef DEBUG
		wsh_log("Tried to copy a line with no data!");
#endif
		return NULL;
	}

	WLine* new = wsh_line_create();
	//new->num	= old->num;
	//new->reserved   = old->reserved;
	//new->data       = malloc((sizeof *new->data) * new->reserved);
	new->has_fill   = old->has_fill;
	new->has_stroke = old->has_stroke;
	new->stroke     = old->stroke;
	new->fill       = old->fill;
	new->closed     = old->closed;
	new->fill       = old->fill;
	new->stroke     = old->stroke;

	for (int i = 0; i < old->num; ++i)
	{

		WPoint p = old->data[i];
		if (p.time > v)
			break;
		wsh_line_add_point(new, p);
		/*
		 new->data[i].x	= old->data[i].x;
		 new->data[i].y	= old->data[i].y;
		 new->data[i].pressure = old->data[i].pressure;
		 new->data[i].tilt_x   = old->data[i].tilt_x;
		 new->data[i].tilt_y   = old->data[i].tilt_y;
		 new->data[i].rotation = old->data[i].rotation;
		 new->data[i].time     = old->data[i].time;
		 */
	}

	//WLineHnd* new_hnd = wsh_line_hnd_create();
	//new_hnd->src      = new;

	//if (old->brush != NULL) {
	//	new->brush = w_brush_copy(old->brush, new_hnd);
	//}
	//	this will break
	// new->brush = old->brush;
	//printf("sliced %llu-> %llu\n", old->num, new->num);
	return new;
}

WLine* wsh_line_reverse(WLine* old)
{
	WLine* new = wsh_line_create();
	//new->num	= old->num;
	//new->reserved   = old->reserved;
	//new->data       = malloc((sizeof *new->data) * new->reserved);
	new->has_fill   = old->has_fill;
	new->has_stroke = old->has_stroke;
	new->stroke     = old->stroke;
	new->fill       = old->fill;
	new->closed     = old->closed;
	new->fill       = old->fill;
	new->stroke     = old->stroke;

	for (int i = 0; i < old->num; ++i)
	{
		WPoint p = old->data[old->num - i];
		wsh_line_add_point(new, p);
	}
	return new;
}

void wsh_line_copy_attribs(WLine* to, WLine* from)
{
	to->has_stroke = from->has_stroke;
	to->has_fill   = from->has_fill;
	to->stroke     = from->stroke;
	to->fill       = from->fill;
	to->closed     = from->closed;
	//	todo : copy brush here too?  other stuff?
}

//	returns a copy of the last point. shortens the line

WPoint* wsh_line_pop_back(WLine* line)
{
	if (line->num <= 0)
	{
		wsh_log("Error, tried to pop an empty line\n");
		return NULL;
	}
	WPoint  p   = line->data[line->num - 1];
	WPoint* ret = wsh_point_copy(&p);
	;
	return ret;
}

void wsh_line_destroy(WLine* line)
{
	if (!line)
	{
#ifdef DEBUG
		wsh_log("I refuse to destroy something that is already "
			"destroyed lol\n");
#endif
		return;
	}

	if (line->data != NULL)
		free(line->data);
	line->num      = 0;
	line->reserved = 0;
	line->data     = NULL;
	//if (line->brush) {
	//	w_brush_destroy(line->brush);
	//}
	//if (line->tess) {
	//	w_gpc_tess_destroy(line);
	//}
	free(line);
}

void wsh_line_find_mins(WLine* line, double* o_x, double* o_y)
{
	unsigned long long np = line->num;
	double		   mx, my;
	mx = my = 0;
	for (int j = 0; j < np; ++j)
	{
		WPoint* p = &line->data[j];
		double  x = p->x;
		double  y = p->y;
		if (j == 0)
		{
			mx = x;
			my = y;
		}
		if (x < mx)
			mx = x;
		if (y < my)
			my = y;
	}

	*o_x = mx;
	*o_y = my;
}

void wsh_line_rotate(WLine* line, double cx, double cy, double r)
{
	for (int i = 0; i < line->num; i++)
	{
		WPoint* p = &line->data[i];
		wsh_point_rotate(p, cx, cy, r);
	}
}
#include "../util/wsh_math.h"

void wsh_line_rotate_d(WLine* line, double cx, double cy, double d)
{
	double r = wsh_degrees_to_radians(d);
	for (int i = 0; i < line->num; i++)
	{
		WPoint* p = &line->data[i];
		wsh_point_rotate(p, cx, cy, r);
	}
}

void wsh_line_move(WLine* line, double x, double y)
{

	unsigned long long np = line->num;

	for (int j = 0; j < np; ++j)
	{
		WPoint* p = &line->data[j];
		p->x += x;
		p->y += y;
	}
	//	todo: take a stance on whether these methods should implicitly
	//	recalculate bounds or if that's wasteful and up to the user
	wsh_line_calc_bounds(line);
}

void wsh_line_scale(WLine* line, double x, double y)
{
	unsigned long long np = line->num;

	for (int j = 0; j < np; ++j)
	{
		WPoint* p = &line->data[j];
		p->x *= x;
		p->y *= y;
	}
	wsh_line_calc_bounds(line);
}

void wsh_line_normalize_time(WLine* l)
{
	if (!l)
	{
#ifdef DEBUG
		wsh_log("Tried to normalize time for a NULL line.");
#endif
		return;
	}
	double first = l->data[0].time;
	//printf("First time is %f\n", first);
	for (int i = 0; i < l->num; i++)
	{
		l->data[i].time -= first;
	}
}

static void bounds_and_avgs(WLine* l, double* _minx, double* _miny, double* maxx, double* maxy, double* _avgx, double* _avgy)
{
	//double minx, miny, maxx, maxy;
	//double avgx, avgy;
	//avgx = avgy = 0;
}

//	todo:	this method copies, maybe have one that does it inplace?
WLine* wsh_line_normalize(WLine* l, double* o_dx, double* o_dy)
{

	WRect obnds = l->bounds;

	WLine* nl = wsh_line_normalize_square(l, o_dx, o_dy);

	double ar = obnds.size.y / obnds.size.x;
	wsh_line_calc_bounds(l);

	if (obnds.size.x > obnds.size.y)
	{
		wsh_line_scale(nl, 1, ar);
	}
	else
	{
		wsh_line_scale(nl, ar, 1);
	}
	wsh_line_calc_bounds(nl);

	//if ( bnds->size.y > 1 || bnds->size.y < -1 || bnds->size.x > 1 || bnds->size.x < -1)
	//{
	//	printf("ERROR normalizing, data exceeded 1!\n");

	//}
	return nl;
}

//	todo:	this method copies, maybe have one that does it inplace?
WLine* wsh_line_normalize_square(WLine* l, double* o_dx, double* o_dy)
{
	if (!l)
	{
#ifdef DEBUG
		wsh_log("Can't normalize a NULL line!");
#endif
		return NULL;
	}

	WLine* normal = wsh_line_create();
	double minx, miny, maxx, maxy;
	double avgx, avgy;
	//minx = maxx = miny = maxy = -77777;
	minx = miny = -INFINITY;
	maxx = maxy = INFINITY;

	avgx = avgy = 0;
	unsigned long long i, j;
	i = j		      = 0;
	unsigned long long np = l->num;

	for (int j = 0; j < np; ++j)
	{

		WPoint p = l->data[j];
		double x = p.x;
		double y = p.y;

		if (j == 0)
		{
			minx = maxx = x;
			miny = maxy = y;
		}

		if (j == 0 && i == 0)
		{
			minx = maxx = x;
			miny = maxy = y;
		}

		avgx += x;
		avgy += y;

		if (minx > x)
			minx = x;
		if (maxx < x)
			maxx = x;
		if (miny < y)
			miny = y;
		if (maxy > y)
			maxy = y;
		// total++;
	}

	avgx /= np;
	avgy /= np;

	double dx = maxx - minx;
	double dy = maxy - miny;

	//	these got unused
	// double px = minx + ( dx * .5);
	// double py = miny + ( dy * .5);
	// double ar = fabs(dx) / fabs(dy);

	// printf("ar: %f\n", ar);

	for (int j = 0; j < np; ++j)
	{
		WPoint* p  = &l->data[j];
		WPoint* np = wsh_point_create();
		np->x      = p->x;
		np->y      = p->y;

		// np->x -= px;
		// np->y -= py;

		np->x -= avgx;
		np->y -= avgy;

		np->x /= dx;
		np->y /= dy;

		wsh_line_add_point(normal, *np);
	}
	if (o_dx)
		*o_dx = dx;
	if (o_dy)
		*o_dy = dy;

	wsh_line_calc_bounds(normal);

	return normal;
}
void wsh_line_normalize_inplace(WLine* l, double* o_dx, double* o_dy)
{

	// WLine* normal = wsh_line_create();
	double minx, miny, maxx, maxy;
	double avgx, avgy;

	minx = miny = -INFINITY;
	maxx = maxy = INFINITY;
	avgx = avgy = 0;
	unsigned long long i, j;
	i = j		      = 0;
	unsigned long long np = l->num;

	for (int j = 0; j < np; ++j)
	{

		WPoint p = l->data[j];
		double x = p.x;
		double y = p.y;

		if (j == 0)
		{
			minx = maxx = x;
			miny = maxy = y;
		}

		if (j == 0 && i == 0)
		{
			minx = maxx = x;
			miny = maxy = y;
		}

		avgx += x;
		avgy += y;

		if (minx > x)
			minx = x;
		if (maxx < x)
			maxx = x;
		if (miny < y)
			miny = y;
		if (maxy > y)
			maxy = y;
		// total++;
	}

	avgx /= np;
	avgy /= np;

	double dx = maxx - minx;
	double dy = maxy - miny;

	//	these got unused
	// double px = minx + ( dx * .5);
	// double py = miny + ( dy * .5);
	// double ar = fabs(dx) / fabs(dy);

	// printf("ar: %f\n", ar);

	for (int j = 0; j < np; ++j)
	{
		WPoint* p = &l->data[j];
		// WPoint* np = wsh_point_create();
		// np->x = p->x;
		// np->y = p->y;

		// np->x -= px;
		// np->y -= py;

		p->x -= avgx;
		p->y -= avgy;

		p->x /= dx;
		p->y /= dy;

		// wsh_line_add_point(normal, *np);
		//	redundant?
		l->data[j].x = p->x;
		l->data[j].y = p->y;
	}
	*o_dx = dx;
	*o_dy = dy;

	// return normal;
}
/*
 double minx, miny, maxx, maxy;
 double avgx, avgy;
 //	todo: fetch the first one instead of this cuz this is
 //	error prone as fuck!
 minx = maxx = miny = maxy = -77777;
 avgx = avgy = 0;
 int num = obj->num;
 int total = 0;

 for (int i = 0 ; i < num; ++i )
 {
 WLine* l = obj->lines[i];

 unsigned long long np = l->num;

 for ( int j = 0; j < np; ++j )
 {


 WPoint p = l->data[j];
 double x = p.x;
 double y = p.y;
 if ( j == 0 && i == 0 )
 {
 minx = maxx = x;
 miny = maxy = y;
 }

 avgx += x;
 avgy += y;

 if ( minx > x ) minx = x;
 if ( maxx < x ) maxx = x;
 if ( miny < y ) miny = y;
 if ( maxy > y ) maxy = y;
 total++;
 }

 }

 avgx /= total;
 avgy /= total;

 double dx = fabs(maxx - minx);
 double dy = fabs(maxy - miny);

 obj->bounds.pos.x = minx;
 obj->bounds.pos.y = miny;
 obj->bounds.size.x = dx;
 obj->bounds.size.y = dy;


 obj->transform.scale.x = dx;
 obj->transform.scale.y = dy;
 obj->transform.position.x = avgx;
 obj->transform.position.y = avgy;

 double offx = dx * .5 - avgx * .5;
 double offy = dy * .5 - avgy * .5;


 obj->transform.anchor.x = offx;
 obj->transform.anchor.y = offy;

 for ( int i = 0 ; i < num; ++i )
 {
 WLine* l = obj->lines[i];

 unsigned long long np = l->num;
 for ( unsigned long long j = 0; j < np; ++j )
 {
 //	shift all geometry to the average
 WPoint* p = &l->data[j];

 p->x -= avgx;
 p->y -= avgy;

 p->x /= dx;
 p->y /= dy;


 }
 }

 double ar =	fabs(dy / dx);

 obj->bounds.size.x = 1;
 obj->bounds.size.y = ar;
 obj->bounds.pos.x = -.5 * dx;
 obj->bounds.pos.y = -.5 * dx;


 obj->normalized = true;


 */
