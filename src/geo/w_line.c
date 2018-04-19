//
//  w_line.c
//  wash
//
//  Created by Andrew Macfarlane on 12/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

/* -- Includes -- */

/* internal includes. */

#include "w_line.h"
#include "w_point.h"

#define LINE_START_SIZE 256
#define LINE_MAX_SIZE 1024

//#include "../util/w_gpc.h"
//#include "../util/w_line_ops.h"
#include <math.h>
#include <string.h>

WLineHnd* w_line_hnd_create(void)
{
	WLineHnd* hnd = calloc(1, sizeof(WLineHnd));
	return hnd;
}

WLineHnd* w_line_hnd_create_with_data(void)
{
	WLineHnd* hnd = calloc(1, sizeof(WLineHnd));
	hnd->src      = w_line_create();
	return hnd;
}

WLineHnd* w_line_hnd_create_with_addr(WLine* addr)
{
	WLineHnd* hnd = calloc(1, sizeof(WLineHnd));
	hnd->src      = addr;
	return hnd;
}

WLineHnd* w_line_hnd_copy(WLineHnd* hnd)
{
	// todo implement this

	return NULL;
}

void w_line_hnd_destroy(WLineHnd* hnd)
{
	free(hnd->src);

	free(hnd);
	//	totally dead
}

WLine* w_line_create()
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

void w_line_calc_bounds(WLine* src)
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
void w_line_add_point2f(WLine* line, double x, double y)
{
	WPoint p;
	p.x = x;
	p.y = y;
	w_line_add_point(line, p);
}

void w_line_add_point(WLine* line, WPoint p)
{
	if (!line)
	{
		printf("Cannot add to a NULL line!\n");
		return;
	}
	
	if (!line->data)
	{
		line->reserved = LINE_START_SIZE;
		//	leaky
		//line->data     = calloc(line->reserved, sizeof *line->data);
		line->data     = calloc(line->reserved, sizeof(WPoint));
	}

	if (line->num == line->reserved)
	{
		(line->reserved) *= 2;
	//	line->data = realloc(line->data, sizeof *line->data * line->reserved);
		line->data = realloc(line->data, sizeof (WPoint) * line->reserved);
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
 // w_line_ops_smooth(line->brush->stroke->tess, 8);
 if (line->brush)
 {
 if (line->brush->stroke)
 {
 // w_line_ops_smooth(line->brush->stroke->tess,
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

void w_line_concat(WLine* dst, WLine* src, ull start, ull end)
{
	
	//while( start < end )
	for (ull i = start; i < end; ++i)
	{
		w_line_add_point(dst, src->data[i]);
	}
	
}

WLine* w_line_copy(WLine* old)
{

	if (old == NULL)
	{
		printf("tried to copy a null line.\n");
		return NULL;
	}
	else if (old->data == NULL)
	{
		printf("Tried to copy a line with no data!\n");
		return NULL;
	}

	WLine* new      = w_line_create();
	new->num	= old->num;
	new->reserved   = old->reserved;
	new->data       = malloc((sizeof *new->data) * new->reserved);
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

	//WLineHnd* new_hnd = w_line_hnd_create();
	//new_hnd->src      = new;

	//if (old->brush != NULL) {
	//	new->brush = w_brush_copy(old->brush, new_hnd);
	//}
	//	this will break
	// new->brush = old->brush;
	return new;
}

WLine* w_line_copy_percentage(WLine* old, double v)
{
	if (old == NULL)
	{
		printf("tried to copy a null line.\n");
		return NULL;
	}
	else if (old->data == NULL)
	{
		printf("Tried to copy a line with no data!\n");
		return NULL;
	}

	WLine* new = w_line_create();
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
		w_line_add_point(new, p);
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

	//WLineHnd* new_hnd = w_line_hnd_create();
	//new_hnd->src      = new;

	//if (old->brush != NULL) {
	//	new->brush = w_brush_copy(old->brush, new_hnd);
	//}
	//	this will break
	// new->brush = old->brush;
	//printf("sliced %llu-> %llu\n", old->num, new->num);
	return new;
}

void w_line_copy_attribs(WLine* to, WLine* from)
{
	to->has_stroke = from->has_stroke;
	to->has_fill   = from->has_fill;
	to->stroke     = from->stroke;
	to->fill       = from->fill;
	to->closed     = from->closed;
	//	todo : copy brush here too?  other stuff?
}

void w_line_destroy(WLine* line)
{
	if (!line)
	{
		printf("I refuse to destroy something that is already "
		       "destroyed lol\n");
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

void w_line_find_mins(WLine* line, double* o_x, double* o_y)
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

void w_line_move(WLine* line, double x, double y)
{
	//printf("offset line by %f %f\n", x, y);
	unsigned long long np = line->num;

	for (int j = 0; j < np; ++j)
	{
		WPoint* p = &line->data[j];
		p->x += x;
		p->y += y;
	}
	w_line_calc_bounds(line);

	//w_brush_update(line->brush);
	//if ( line->brush )
	//{
	//	w_line_move(line->brush->stroke, x, y);
	//	}
}

void w_line_scale(WLine* line, double x, double y)
{
	unsigned long long np = line->num;

	for (int j = 0; j < np; ++j)
	{
		WPoint* p = &line->data[j];
		p->x *= x;
		p->y *= y;
	}
	w_line_calc_bounds(line);
}

void w_line_normalize_time(WLine* l)
{
	if (!l)
	{
		printf("Tried to normalize time for a NULL line.\n");
		return;
	}
	double first = l->data[0].time;
	printf("First time is %f\n", first);
	for (int i = 0; i < l->num; i++)
	{
		l->data[i].time -= first;
	}
}

//	todo:	this method copies, maybe have one that does it inplace?
WLine* w_line_normalize(WLine* l, double* o_dx, double* o_dy)
{

	WLine* normal = w_line_create();
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
		WPoint* np = w_point_create();
		np->x      = p->x;
		np->y      = p->y;

		// np->x -= px;
		// np->y -= py;

		np->x -= avgx;
		np->y -= avgy;

		np->x /= dx;
		np->y /= dy;

		w_line_add_point(normal, *np);
	}
	*o_dx = dx;
	*o_dy = dy;

	return normal;
}

void w_line_normalize_inplace(WLine* l, double* o_dx, double* o_dy)
{

	// WLine* normal = w_line_create();
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
		// WPoint* np = w_point_create();
		// np->x = p->x;
		// np->y = p->y;

		// np->x -= px;
		// np->y -= py;

		p->x -= avgx;
		p->y -= avgy;

		p->x /= dx;
		p->y /= dy;

		// w_line_add_point(normal, *np);
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
 int num = obj->num_lines;
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
