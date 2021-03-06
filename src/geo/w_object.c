//
//  w_object.c
//  wash
//
//  Created by Andrew Macfarlane on 12/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#include "w_object.h"

#include <math.h>

#include "../util/w_line_ops.h"

WObject* w_object_create(WObject* parent)
{
	WObject* obj;
	obj		= calloc(1, sizeof(WObject));
	obj->lines      = NULL;
	obj->normalized = false;
	obj->num_lines  = 0;
	obj->parent     = parent;
	WRect b;
	b.pos.x = b.pos.y = b.size.x = b.size.y = 0;
	obj->bounds				= b;

	w_transform_reset(&obj->transform);

	return obj;
}

void w_object_destroy_void(void* obj)
{
	printf("Destroying void pointer (from map?\n");
	w_object_destroy((WObject*)obj);
}

void w_object_destroy(WObject* obj)
{
	if (!obj) {

		printf("Trying to free a null\n");
		return;
	}
	/*
	 for ( int i = 0; i < obj->num_frames; ++i )
	 {
		free(obj->frames[i]);
	 }
	 */

	for (int i = 0; i < obj->num_lines; ++i) {
		WLine* l = obj->lines[i];

		w_line_destroy(l);
	}

	free(obj);
}

void w_object_add_line(WObject* obj, WLine* line)
{
	if (obj == NULL) {
		printf("Can't add a line to a NULL object.\n");
		return;
	}

	obj->num_lines++;
	if (obj->lines == NULL) {
		// printf("malloc\n");
		obj->lines = calloc(1, sizeof(WLine**));
	} else {
		// printf("realloc %d\n", obj->num_lines);
		obj->lines =
		    realloc(obj->lines, sizeof(WLine*) * obj->num_lines);
	}

	obj->lines[obj->num_lines - 1] = line;
}

void w_object_remove_line(WObject* obj, WLine* line )
{
	int idx = -1;
	for ( int i=0; i < obj->num_lines; i++ )
	{
		WLine* test = obj->lines[i];
		if ( test == line )
		{
			idx = i;
			break;
		}
	}
	if ( idx == -1 )
	{
		printf("Error, did not find requested line.\n");
		return;
	}
	printf("found line %d\n", idx);
	
	for ( int i = idx; i < obj->num_lines -1; i++ )
	{
		printf("Shuffling %d tp %d.\n", i+1, i);
		
		
	}
	obj->num_lines--;

	
	
}

/*
 void	w_object_frame_next(WObject* obj)
 {

	if ( !obj )
 return;


	if ( obj->num_frames == 0 )
	{
 printf("can't do next frame, no frames!\n");
 return;
	}
	obj->current_frame_index++;
	if ( obj->current_frame_index == obj->num_frames)
	{
 obj->current_frame_index = 0;
	}

	obj->current_frame = obj->frames[obj->current_frame_index];
	printf("Set object frame %d %p\n", obj->current_frame_index,
 obj->current_frame);

 }

 void	w_object_frame_prev(WObject* obj)
 {
	if ( !obj )
 return;

	if ( obj->num_frames == 0 )
	{
 printf("can't do next frame, no frames!\n");
 return;
	}

	obj->current_frame_index--;
	if ( obj->current_frame_index < 0 )
	{
 obj->current_frame_index = obj->num_frames-1;
	}
	obj->current_frame = obj->frames[obj->current_frame_index];
	printf("Set object frame %d %p\n", obj->current_frame_index,
 obj->current_frame);
 }

 WObject*	w_object_frame_create(WObject* parent, int pos)
 {
	WObject* obj = NULL;

	if ( pos == -1 )
	{
 parent->num_frames++;
 printf("creating frame at %d\n", parent->num_frames);
 parent->frames = realloc(parent->frames, sizeof(WObject*) *
 parent->num_frames);

 WObject* obj = w_object_create(parent);
 parent->frames[parent->num_frames-1] = obj;
 parent->current_frame = obj;
 return obj;
	}else{
 printf("creating frame at %d\n", pos);

	}
	return obj;
 }


 void	w_object_frame_delete(WObject* obj, int pos)
 {

	printf("deleting frame at %d\n", pos);
	//int npos = obj->

 }
 */

WObject* w_object_copy(WObject* old)
{

	// printf("Copying object with %d lines\n", old->num_lines);
	// WObject* cpy = malloc(sizeof(WObject));
	// cpy = (WObject*)memcpy(cpy, old, sizeof(WObject));

	if (!old) {
		printf("Error, tried to copy a NULL OBject!\n");
		return NULL;
	}

	WObject* obj    = w_object_create(NULL);
	obj->parent     = old->parent;
	obj->bounds     = old->bounds;
	obj->transform  = old->transform;
	obj->normalized = old->normalized;
	// obj->frames = NULL;
	// obj->num_frames = old->num_frames;
	// obj->num_lines = old->num_lines;

	int i;
	int num = old->num_lines;

	obj->num_lines = num;
	obj->lines     = NULL;
	obj->lines     = malloc(sizeof(WLine*) * num);

	for (i = 0; i < num; ++i) {
		WLine* old_line = old->lines[i];
		WLine* line     = w_line_copy(old_line);
		obj->lines[i]   = line;
		// w_object_add_line(obj, line);
	}

	return obj;
}

WObject* w_object_copy_from_percentage(WObject* old, double t)
{

	if (!old) {
		printf("Error, tried to copy a NULL OBject!\n");
		return NULL;
	}

	WObject* obj    = w_object_create(NULL);
	obj->parent     = old->parent;
	obj->bounds     = old->bounds;
	obj->transform  = old->transform;
	obj->normalized = old->normalized;

	int i;
	int num = old->num_lines;

	obj->num_lines = num;
	obj->lines     = NULL;
	obj->lines     = malloc(sizeof(WLine*) * num);

	for (i = 0; i < num; ++i) {
		WLine* old_line = old->lines[i];
		WLine* line     = w_line_copy_percentage(old_line, t);
		obj->lines[i]   = line;
	}
	return obj;
}

#define WOBJECT_DEBUG true
void w_object_douglaspeucker(WObject* obj, double r)
{
#ifdef WOBJECT_DEBUG
	unsigned long long old = w_object_sum_points(obj);
#endif

	for (int i = 0; i < obj->num_lines; i++) {
		WLine* l   = obj->lines[i];
		WLine* new = w_line_ops_douglaspeucker(l, r);
		free(l);
		obj->lines[i] = new;
	}
#ifdef WOBJECT_DEBUG
	printf("dp: %llu -> %llu\n", old, w_object_sum_points(obj));
#endif
}

void w_object_center(WObject* obj)
{
	w_object_calc_bounds(obj);

	double dx = obj->bounds.size.x;
	double dy = obj->bounds.size.y;
	double cx = obj->bounds.pos.x + (dx * .5);
	double cy = obj->bounds.pos.y + (dy * .5);

	for (int i = 0; i < obj->num_lines; i++) {
		WLine* l = obj->lines[i];
		for (int j = 0; j < l->num; j++) {
			l->data[j].x -= cx;
			l->data[j].y -= cy;
		}
	}
}

void w_object_simplify(WObject* obj, double r)
{
	for (int i = 0; i < obj->num_lines; i++) {
		WLine* l = obj->lines[i];
		w_line_ops_simplify(l, r);
	}
}


void w_object_normalize_time_continuous(WObject* obj)
{
	double first = INFINITY;
	double last = -INFINITY;
	for ( int j = 0; j < obj->num_lines; j++ )
	{
		WLine* l = obj->lines[j];
		for ( int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			double t = p->time;
			if ( t < first )
				first = t;
			if ( t > last )
				last = t;
		}
	}
	
	if ( first == INFINITY)
	{
		printf("no geometry? time was still INF\n");
		return;
	}
	
	printf("Normalizing frame to %f->%f\n", first, last);
	double delta = last - first;
	printf("delta %f\n", delta);
	for ( int j = 0; j < obj->num_lines; j++ )
	{
		WLine* l = obj->lines[j];
		for ( int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			p->time -= first;
			p->time /= delta;
			printf("%f\n", p->time);
		}
	}
	
	
	
	
}


void w_object_normalize_time_exploded(WObject* obj)
{
	
	//double first = INFINITY;
	//double last = -INFINITY;
	//double delta = -INFINITY;
	
	unsigned long long longest = 0;
	double longest_duration = -INFINITY;
	double longest_start = -INFINITY;
	double longest_end = -INFINITY;
	double leader = -INFINITY;
	for ( int j = 0; j < obj->num_lines; j++ )
	{
		WLine* l = obj->lines[j];
		

		double first = INFINITY;
		double last = -INFINITY;
		for ( int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			double t = p->time;
			if ( t < first )
				first = t;
			if ( t > last )
				last = t;
		}
		double delta = last - first;
		//printf("linedelta %f\n", delta);
		if( delta > longest_duration)
		{
			longest_start = first;
			longest_duration = delta;
			longest = j;
		}
	}
	
	printf("longest for obj is %llu with %f\n", longest, longest_duration);
	double scale = 1 / longest_duration;
	//printf("timescale is %f\n", scale);
	
	for ( int j = 0; j < obj->num_lines; j++ )
	{
		WLine* l = obj->lines[j];
		double first = INFINITY;
		double last = -INFINITY;
		for ( int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			double t = p->time;
			if ( t < first )
				first = t;
			if ( t > last )
				last = t;
		}
		double delta = last - first;
		double doff =  longest_start - first;
		
		//printf("line %d %.02f %.02f \n", j, first, last);
		//printf("Offseting line %d by %f\n", j, doff);
		//printf("Scaling line %d by %f\n", j, duration);
		for ( int k = 0; k < l->num; k++)
		{
			WPoint* p = &l->data[k];
			p->time -= first;
			p->time *= 1/delta;
			//p->time -= doff;
			
			//p->time /= longest_duration;
			//p->time *= scale;

		}
	}
	
	
	/*
	 //for ( int j = 0; j < obj->num_lines; j++ )
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
	 
	 printf("Longest line goes from %f %f\n", first, last);
	 double delta = last - first;
	 
	 printf("delta %f seconds\n", delta);
	 */
	//}
	
	
	/*
	 if ( first == INFINITY)
	 {
	 printf("no geometry? time was still INF\n");
	 continue;
	 }
	 
	 printf("Normalizing frame %d to %f->%f\n", i, first, last);
	 double delta = last - first;
	 printf("delta %f\n", delta);
	 for ( int j = 0; j < obj->num_lines; j++ )
	 {
	 WLine* l = obj->lines[j];
	 for ( int k = 0; k < l->num; k++)
	 {
	 WPoint* p = &l->data[k];
	 p->time -= first;
	 p->time /= delta;
	 printf("%f\n", p->time);
	 }
	 }*/
}

void w_object_normalize(WObject* obj)
{
	double minx, miny, maxx, maxy;
	double avgx, avgy;
	//	todo: fetch the first one instead of this cuz this is
	//	error prone as fuck!
	//minx = maxx = miny = maxy = -77777;
	minx = miny = -INFINITY;
	maxx = maxy = INFINITY;

	avgx = avgy = 0;
	int num     = obj->num_lines;
	int total   = 0;

	for (int i = 0; i < num; ++i) {
		WLine* l = obj->lines[i];

		unsigned long long np = l->num;

		for (int j = 0; j < np; ++j) {

			WPoint p = l->data[j];
			double x = p.x;
			double y = p.y;
			if (j == 0 && i == 0) {
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

	for (int i = 0; i < num; ++i) {
		WLine* l = obj->lines[i];

		unsigned long long np = l->num;
		for (unsigned long long j = 0; j < np; ++j) {
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

	double ar = fabs(dy / dx);

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

	
	
	w_object_calc_bounds(obj);

	obj->normalized = true;
}

void w_object_calc_bounds(WObject* obj)
{
	double minx, miny, maxx, maxy;
	double avgx, avgy;
	minx = miny = INFINITY;
	maxx = maxy = -INFINITY;

	avgx = avgy = 0;
	int num     = obj->num_lines;
	int total   = 0;

	for (int i = 0; i < num; ++i) {
		WLine* l = obj->lines[i];
		w_line_calc_bounds(l);
		unsigned long long np = l->num;

		for (int j = 0; j < np; ++j) {

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
		
		double ldx = maxx - minx;
		double ldy = maxy - miny;
		l->bounds.size.x = ldx;
		l->bounds.size.y = ldy;
		//printf("bnd %f %f %f %f\n", minx, miny, ldx, ldy);
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

unsigned long long w_object_sum_points(WObject* obj)
{
	unsigned long long sum = 0;
	for (int i = 0; i < obj->num_lines; i++) {
		sum += obj->lines[i]->num;
	}
	return sum;
}
