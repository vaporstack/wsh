//
//  wsh_object.c
//  wash
//
//  Created by Andrew Macfarlane on 12/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#include "wsh_object.h"

#include <math.h>

#include "../util/wsh_line_ops.h"

//#ifdef DEBUG
#include "../io/wsh_log.h"
#include <stdio.h>
//#endif

#include <assert.h>

WObject* wsh_object_create(void)
{
	WObject* obj;
	obj		= calloc(1, sizeof(WObject));
	obj->lines      = NULL;
	obj->normalized = false;
	obj->num	= 0;
	//obj->parent     = parent;
	WRect b;
	b.pos.x = b.pos.y = b.size.x = b.size.y = 0;
	obj->bounds				= b;

	wsh_transform_reset(&obj->transform);

	return obj;
}

void wsh_object_destroy_void(void* obj)
{
#ifdef DEBUG
	wsh_log("Destroying void pointer (from map?\n");
#endif
	wsh_object_destroy((WObject*)obj);
}

void wsh_object_destroy(WObject* obj)
{
	if (!obj)
	{

#ifdef DEBUG
		wsh_log("Trying to free a null\n");
#endif
		return;
	}
	if (!obj->lines)
	{
		wsh_log("lines field was null!");
		return;
	}
	for (unsigned i = 0; i < obj->num; ++i)
	{
		WLine* l = obj->lines[i];
		if (!l)
			continue;
		wsh_line_destroy(l);
	}
	free(obj->lines);
	free(obj);
}

void wsh_object_add_line(WObject* obj, WLine* line)
{
	if (obj == NULL)
	{
#ifdef DEBUG
		wsh_log("Can't add a line to a NULL object.\n");
#endif
		return;
	}

	obj->num++;
	if (obj->lines == NULL)
	{
		obj->lines = calloc(1, sizeof(WLine*));
	}
	else
	{
		obj->lines = realloc(obj->lines, sizeof(WLine*) * obj->num);
	}

#ifdef DEBUG
	if (line)
	{
		if (line->num > 4096)
		{
			wsh_log("abnormally huge line, what happened\n");
		}
	}

#endif

	obj->lines[obj->num - 1] = line;
}

WLine* wsh_object_remove_line(WObject* obj, WLine* line)
{
	int idx = -1;
	for (int i = 0; i < obj->num; i++)
	{
		WLine* test = obj->lines[i];
		if (test == line)
		{
			idx = i;
			break;
		}
	}
	if (idx == -1)
	{
#ifdef DEBUG
		wsh_log("Error, did not find requested line.\n");
#endif
		return NULL;
	}
#ifdef DEBUG
	wsh_log("found line %d\n", idx);
#endif
	WLine* pop = obj->lines[idx];
	for (int i = idx; i < obj->num - 1; i++)
	{
#ifdef DEBUG
		wsh_log("Shuffling %d tp %d.\n", i + 1, i);
#endif
		obj->lines[i] = obj->lines[i+1];
	}
	
	
	obj->num--;
	return pop;
}

/*
 void	wsh_object_frame_next(WObject* obj)
 {

	if ( !obj )
 return;


	if ( obj->num_frames == 0 )
	{
 wsh_log("can't do next frame, no frames!\n");
 return;
	}
	obj->current_frame_index++;
	if ( obj->current_frame_index == obj->num_frames)
	{
 obj->current_frame_index = 0;
	}

	obj->current_frame = obj->frames[obj->current_frame_index];
	wsh_log("Set object frame %d %p\n", obj->current_frame_index,
 obj->current_frame);

 }

 void	wsh_object_frame_prev(WObject* obj)
 {
	if ( !obj )
 return;

	if ( obj->num_frames == 0 )
	{
 wsh_log("can't do next frame, no frames!\n");
 return;
	}

	obj->current_frame_index--;
	if ( obj->current_frame_index < 0 )
	{
 obj->current_frame_index = obj->num_frames-1;
	}
	obj->current_frame = obj->frames[obj->current_frame_index];
	wsh_log("Set object frame %d %p\n", obj->current_frame_index,
 obj->current_frame);
 }

 WObject*	wsh_object_frame_create(WObject* parent, int pos)
 {
	WObject* obj = NULL;

	if ( pos == -1 )
	{
 parent->num_frames++;
 wsh_log("creating frame at %d\n", parent->num_frames);
 parent->frames = realloc(parent->frames, sizeof(WObject*) *
 parent->num_frames);

 WObject* obj = wsh_object_create(parent);
 parent->frames[parent->num_frames-1] = obj;
 parent->current_frame = obj;
 return obj;
	}else{
 wsh_log("creating frame at %d\n", pos);

	}
	return obj;
 }


 void	wsh_object_frame_delete(WObject* obj, int pos)
 {

	wsh_log("deleting frame at %d\n", pos);
	//int npos = obj->

 }
 */

WObject* wsh_object_copy(WObject* old)
{

	// wsh_log("Copying object with %d lines\n", old->num);
	// WObject* cpy = malloc(sizeof(WObject));
	// cpy = (WObject*)memcpy(cpy, old, sizeof(WObject));

	if (!old)
	{
#ifdef DEBUG
		wsh_log("Error, tried to copy a NULL OBject!\n");
#endif
		return NULL;
	}

	WObject* obj    = wsh_object_create();
	//obj->parent     = old->parent;
	obj->bounds     = old->bounds;
	obj->transform  = old->transform;
	obj->normalized = old->normalized;
	// obj->frames = NULL;
	// obj->num_frames = old->num_frames;
	// obj->num = old->num;

	unsigned long i;
	unsigned long num = old->num;

	obj->num   = num;
	obj->lines = NULL;
	obj->lines = malloc(sizeof(WLine*) * num);

	for (i = 0; i < num; ++i)
	{
		WLine* oldrw_line = old->lines[i];
		WLine* line       = wsh_line_copy(oldrw_line);
		obj->lines[i]     = line;
		// wsh_object_add_line(obj, line);
	}

	return obj;
}

WObject* wsh_object_copy_from_percentage(WObject* old, double t)
{

	if (!old)
	{
#ifdef DEBUG
		wsh_log("Error, tried to copy a NULL OBject!\n");
#endif
		return NULL;
	}

	WObject* obj    = wsh_object_create();
	//obj->parent     = old->parent;
	obj->bounds     = old->bounds;
	obj->transform  = old->transform;
	obj->normalized = old->normalized;

	int	   i;
	unsigned long num = old->num;

	obj->num   = num;
	obj->lines = NULL;
	obj->lines = calloc(num, sizeof(WLine*));

	for (i = 0; i < num; ++i)
	{
		WLine* oldrw_line = old->lines[i];
		WLine* line       = wsh_line_copy_percentage(oldrw_line, t);
		obj->lines[i]     = line;
	}
	return obj;
}

#define WOBJECT_DEBUG true
void wsh_object_douglaspeucker(WObject* obj, double r)
{
#ifdef WOBJECT_DEBUG
	unsigned long long old = wsh_object_sum_points(obj);
#endif

	for (int i = 0; i < obj->num; i++)
	{
		WLine* l   = obj->lines[i];
		WLine* new = wsh_line_ops_douglaspeucker(l, r);
		free(l);
		obj->lines[i] = new;
	}
#ifdef WOBJECT_DEBUG
#ifdef DEBUG
	wsh_log("dp: %llu -> %llu\n", old, wsh_object_sum_points(obj));
#endif
#endif
}

void wsh_object_scale(WObject* obj, double modx, double mody)
{
	for (unsigned long i = 0; i < obj->num; i++)
	{
		WLine* l = obj->lines[i];
		wsh_line_scale(l, modx, mody);
	}
}

void wsh_object_translate(WObject* obj, double dx, double dy)
{
	for (unsigned long i = 0; i < obj->num; i++)
	{
		WLine* l = obj->lines[i];
		wsh_line_move(l, dx, dy);
	}
}

void wsh_object_center(WObject* obj)
{
	wsh_object_calc_bounds(obj);

	double dx = obj->bounds.size.x;
	double dy = obj->bounds.size.y;
	double cx = obj->bounds.pos.x + (dx * .5);
	double cy = obj->bounds.pos.y + (dy * .5);

	for (int i = 0; i < obj->num; i++)
	{
		WLine* l = obj->lines[i];
		for (int j = 0; j < l->num; j++)
		{
			l->data[j].x -= cx;
			l->data[j].y -= cy;
		}
	}
}

void wsh_object_simplify(WObject* obj, double r)
{
	for (int i = 0; i < obj->num; i++)
	{
		WLine* l = obj->lines[i];
		wsh_line_ops_simplify(l, r);
	}
}

void wsh_object_rotate(WObject* obj, double cx, double cy, double r)
{
	for (int i = 0; i < obj->num; i++)
	{
		wsh_line_rotate(obj->lines[i], cx, cy, r);
	}
}

void wsh_object_time_trim_head(WObject* obj)
{
	double earliest = INFINITY;
	for (unsigned long i = 0; i < obj->num; i++)
	{
		WLine* l = obj->lines[i];
		for (unsigned long j = 0; j < l->num; j++)
		{
			double t = l->data[j].time;
			if (t < earliest)
			{
				earliest = t;
			}
		}
	}
	//wsh_log("earliest point is at %f\n", earliest);
	for (unsigned long i = 0; i < obj->num; i++)
	{
		WLine* l = obj->lines[i];
		for (unsigned long j = 0; j < l->num; j++)
		{
			l->data[j].time -= earliest;
		}
	}
}

void wsh_object_time_normalize_continuous(WObject* obj)
{
	double first = INFINITY;
	double last  = -INFINITY;
	for (int j = 0; j < obj->num; j++)
	{
		WLine* l = obj->lines[j];
		for (int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			double  t = p->time;
			if (t < first)
				first = t;
			if (t > last)
				last = t;
		}
	}

	if (first == INFINITY)
	{
#ifdef DEBUG
		wsh_log("no geometry? time was still INF\n");
#endif
		return;
	}

	//wsh_log("Normalizing frame to %f->%f\n", first, last);
	double delta = last - first;
	//wsh_log("delta %f\n", delta);
	for (int j = 0; j < obj->num; j++)
	{
		WLine* l = obj->lines[j];
		for (int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			p->time -= first;
			p->time /= delta;
			//wsh_log("%f\n", p->time);
		}
	}
}

void wsh_object_time_normalize_exploded(WObject* obj)
{

	//double first = INFINITY;
	//double last = -INFINITY;
	//double delta = -INFINITY;

	//unsigned long long longest = 0;
	double longest_duration = -INFINITY;
	//double longest_start    = -INFINITY;
	//double longest_end = -INFINITY;
	//double leader = -INFINITY;
	for (int j = 0; j < obj->num; j++)
	{
		WLine* l = obj->lines[j];

		double first = INFINITY;
		double last  = -INFINITY;
		for (int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			double  t = p->time;
			if (t < first)
				first = t;
			if (t > last)
				last = t;
		}
		double delta = last - first;
		//wsh_log("linedelta %f\n", delta);
		if (delta > longest_duration)
		{
			//longest_start = first;
			longest_duration = delta;
			//longest = j;
		}
	}

	//wsh_log("longest for obj is %llu with %f\n", longest, longest_duration);
	//double scale = 1 / longest_duration;
	//wsh_log("timescale is %f\n", scale);

	for (int j = 0; j < obj->num; j++)
	{
		WLine* l     = obj->lines[j];
		double first = INFINITY;
		double last  = -INFINITY;
		for (int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			double  t = p->time;
			if (t < first)
				first = t;
			if (t > last)
				last = t;
		}
		double delta = last - first;
		//double doff =  longest_start - first;

		//wsh_log("line %d %.02f %.02f \n", j, first, last);
		//wsh_log("Offseting line %d by %f\n", j, doff);
		//wsh_log("Scaling line %d by %f\n", j, duration);
		for (int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			p->time -= first;
			p->time *= 1 / delta;
			//p->time -= doff;

			//p->time /= longest_duration;
			//p->time *= scale;
		}
	}

	/*
	 //for ( int j = 0; j < obj->num; j++ )
	 //{
	 WLine* l = obj->lines[longest];
	 for ( int k = 0; k < l->num; k++)
	 {
	 WPoint* p = &l->data[k];
	 double t = p->time;
	 if ( t < first )
	 first = t;
	 if ( t > last )
	 last = t;
	 }

	 wsh_log("Longest line goes from %f %f\n", first, last);
	 double delta = last - first;

	 wsh_log("delta %f seconds\n", delta);
	 */
	//}

	/*
	 if ( first == INFINITY)
	 {
	 wsh_log("no geometry? time was still INF\n");
	 continue;
	 }

	 wsh_log("Normalizing frame %d to %f->%f\n", i, first, last);
	 double delta = last - first;
	 wsh_log("delta %f\n", delta);
	 for ( int j = 0; j < obj->num; j++ )
	 {
	 WLine* l = obj->lines[j];
	 for ( int k = 0; k < l->num; k++)
	 {
	 WPoint* p = &l->data[k];
	 p->time -= first;
	 p->time /= delta;
	 wsh_log("%f\n", p->time);
	 }
	 }*/
}

void wsh_object_normalize(WObject* obj)
{
	double minx, miny, maxx, maxy;
	double avgx, avgy;
	//	todo: fetch the first one instead of this cuz this is
	//	error prone as fuck!
	//minx = maxx = miny = maxy = -77777;
	minx = miny = -INFINITY;
	maxx = maxy = INFINITY;

	avgx = avgy	 = 0;
	unsigned long num   = obj->num;
	int	   total = 0;

	for (unsigned long i = 0; i < num; ++i)
	{
		WLine* l = obj->lines[i];

		unsigned long long np = l->num;

		for (int j = 0; j < np; ++j)
		{

			WPoint p = l->data[j];
			double x = p.x;
			double y = p.y;
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
			total++;
		}
	}

	avgx /= total;
	avgy /= total;

	double dx = fabs(maxx - minx);
	double dy = fabs(maxy - miny);

	obj->bounds.pos.x  = minx;
	obj->bounds.pos.y  = miny;
	obj->bounds.size.x = dx;
	obj->bounds.size.y = dy;

	//	scale != size.  scale is from 0-1, normalized
	//	size belongs to bounds and is a record of the original size?
	obj->transform.scale.x    = dx;
	obj->transform.scale.y    = dy;
	obj->transform.position.x = avgx;
	obj->transform.position.y = avgy;

	double offx = dx * .5 - avgx * .5;
	double offy = dy * .5 - avgy * .5;

	obj->transform.anchor.x = offx;
	obj->transform.anchor.y = offy;

	for (int i = 0; i < num; ++i)
	{
		WLine* l = obj->lines[i];

		unsigned long long np = l->num;
		for (unsigned long long j = 0; j < np; ++j)
		{
			//	shift all geometry to the average
			//	No, DON'T do that, average is a terrible
			//	metric for where the center should be..tsk.

			WPoint* p = &l->data[j];

			p->x -= dx * .5;
			p->y -= dy * .5;

			p->x /= dx;
			p->y /= dy;
		}
	}

	//double ar = fabs(dy / dx);

	/*
	 //	these are normalized coords.  THey no longer apply. Normalized
	stuff
	 //	goes into the transform.  This is our record of how big the
	art was originally.
	 //	see below.
	obj->bounds.size.x = 1;
	obj->bounds.size.y = ar;
	obj->bounds.pos.x = -.5 * dx;
	obj->bounds.pos.y = -.5 * dx;
	*/

	obj->bounds.size.x = dx;
	obj->bounds.size.y = dy;
	obj->bounds.pos.x  = minx - (.5 * dx);
	obj->bounds.pos.y  = miny - (.5 * dx);

	wsh_object_calc_bounds(obj);

	obj->normalized = true;
}
#include "../io/wsh_log.h"

void wsh_object_calc_bounds(WObject* obj)
{
#ifdef DEBUG
	if (!obj)
	{
		wsh_log("wsh was passed a null object: %s", __func__);
		return;
		//assert(obj != NULL);
	}
#else
	if (!obj)
		return;
#endif
	double minx, miny, maxx, maxy;
	double avgx, avgy;
	minx = miny = INFINITY;
	maxx = maxy = -INFINITY;

	avgx = avgy	 = 0;
	unsigned long num   = obj->num;
	int	   total = 0;

	for (int i = 0; i < num; ++i)
	{
		WLine* l = obj->lines[i];
		if (!l)
		{
#ifdef DEBUG
			wsh_log("Something went wrong!a\n");
#endif
			continue;
		}
		wsh_line_calc_bounds(l);
		unsigned long long np = l->num;

		for (int j = 0; j < np; ++j)
		{

			WPoint p = l->data[j];

			double x = p.x;
			double y = p.y;
			//if (j == 0 && i == 0) {
			//	minx = maxx = x;
			//	miny = maxy = y;
			//}

			avgx += x;
			avgy += y;

			if (x < minx)
				minx = x;
			if (x > maxx)
				maxx = x;
			if (y < miny)
				miny = y;
			if (y > maxy)
				maxy = y;
			total++;
		}
		l->bounds.pos.x = minx;
		l->bounds.pos.y = miny;

		double ldx       = maxx - minx;
		double ldy       = maxy - miny;
		l->bounds.size.x = ldx;
		l->bounds.size.y = ldy;
		//wsh_log("bnd %f %f %f %f\n", minx, miny, ldx, ldy);
	}

	// avgx /= total;
	// avgy /= total;

	double dx = (maxx - minx);
	double dy = (maxy - miny);

	obj->bounds.pos.x  = minx;
	obj->bounds.pos.y  = miny;
	obj->bounds.size.x = dx;
	obj->bounds.size.y = dy;

	// double offx = dx * .5 - avgx * .5;
	// double offy = dy * .5 - avgy * .5;
}

unsigned long long wsh_object_sum_points(WObject* obj)
{
	unsigned long long sum = 0;
	for (int i = 0; i < obj->num; i++)
	{
		sum += obj->lines[i]->num;
	}
	return sum;
}

void wsh_object_set_closed(WObject* obj, bool val)
{
	for (int i = 0; i < obj->num; i++)
	{
		obj->lines[i]->closed = val;
	}
}
