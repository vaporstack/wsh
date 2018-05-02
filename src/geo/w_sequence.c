
//  w_sequence.c
//  w_sequence
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "w_sequence.h"

#include <assert.h>
#include <math.h>

void w_sequence_ensure_frame(WSequence* seq)
{

	int pos = seq->current_frame_index;
	int adj = pos;
	if (pos == seq->num_frames) {
		adj = 0;
	}
	if (pos < 0) {
		adj = seq->num_frames - 1;
	}
	if (adj != pos) {
		seq->current_frame_index = adj;
#ifdef DEBUG

		printf("Adjusted bad frame!\n");
#endif
		
	}
	seq->current_frame = seq->frames[seq->current_frame_index];

	/*
	 if (seq->current_frame_index < 0) {
	 seq->current_frame_index = seq->num_frames - 1;
	 }
	 seq->current_frame = seq->frames[seq->current_frame_index];
	 */
	/*
	 from calling function
	 if (seq->current_frame_index == seq->num_frames) {
	 seq->current_frame_index = 0;
	 }

	 seq->current_frame = seq->frames[seq->current_frame_index];
	 printf("Set object frame %d %p\n", seq->current_frame_index,
	 seq->current_frame);
	 */
}

static void _check_realloc(WSequence* seq)
{

	if (seq->num_frames == seq->reserved) {
		seq->reserved *= 2;
		seq->frames =
		    realloc(seq->frames, sizeof(WObject*) * seq->reserved);

		for (int i = seq->current_frame_index; i < seq->reserved; ++i) {
			seq->frames[i] = NULL;
		}
#ifdef DEBUG
printf("Frame realloc! %d\n", seq->reserved);
#endif
		
	}
}

WSequence* w_sequence_create()
{
	WSequence* seq = malloc(sizeof(WSequence));

	// seq->frames = calloc(seq->reserved, sizeof(WObject));
	seq->num_frames		 = 0;
	seq->anim_type		 = -1;
	seq->reserved		 = 24;
	//seq->anim_start = 0;
	//seq->anim_end = 0;
	seq->anim_duration       = 1;
	seq->current_frame       = NULL;
	seq->current_frame_index = 0;
	seq->golden_frames       = NULL;
	seq->num_golden_frames   = 0;
	seq->bounds.pos.x = seq->bounds.size.x = 0;
	seq->bounds.pos.y = seq->bounds.size.y = 0;

	seq->frames = calloc(seq->reserved, sizeof(WObject*));

	/*
	seq->num_golden_frames = 3;
	seq->golden_frames = malloc(sizeof(int) * 4);

	seq->golden_frames[0] = 2;
	seq->golden_frames[1] = 8;
	seq->golden_frames[2] = 221345;
	 */

	w_sequence_frame_create(seq, -1);

	return seq;
}

WSequence* w_sequence_copy(WSequence* old)
{
	WSequence* seq = calloc(1, sizeof(WSequence));

	// seq->frames = calloc(seq->reserved, sizeof(WObject));
	seq->num_frames		 = old->num_frames;
	seq->anim_type		 = old->anim_type;
	seq->reserved		 = old->reserved;
	seq->anim_duration       = old->anim_duration;
	seq->current_frame       = NULL;
	seq->current_frame_index = old->current_frame_index;
	seq->golden_frames       = NULL;
	seq->num_golden_frames   = old->num_golden_frames;
	seq->bounds.pos.x = seq->bounds.size.x = 0;
	seq->bounds.pos.y = seq->bounds.size.y = 0;

	seq->frames = calloc(seq->reserved, sizeof(WObject*));
	for (int i = 0; i < seq->num_frames; i++) {
		seq->frames[i] = w_object_copy(old->frames[i]);
	}
	seq->current_frame = seq->frames[seq->current_frame_index];
	/*
	 seq->num_golden_frames = 3;
	 seq->golden_frames = malloc(sizeof(int) * 4);

	 seq->golden_frames[0] = 2;
	 seq->golden_frames[1] = 8;
	 seq->golden_frames[2] = 221345;
	 */

	// w_sequence_frame_create(seq, -1);

	return seq;
}

void w_sequence_frame_create(WSequence* seq, int pos)
{
	// WObject* seq = NULL;
	// OLD AND BAD BUT IT FUCKING WORKED!?
	if (pos == -1) {
		seq->num_frames++;

		_check_realloc(seq);

		// printf("creating frame at %d\n", seq->num_frames);

		WObject* obj			 = w_object_create(NULL);
		seq->frames[seq->num_frames - 1] = obj;
		seq->current_frame_index	 = seq->num_frames - 1;

		//
		seq->current_frame = seq->frames[seq->current_frame_index];

	} else {
		// printf("creating frame at %d\n", pos);

		assert(false);
#ifdef DEBUG
	printf("IMPLEMENT THIS!\n");

#endif
		
	}
}

void w_sequence_frame_set(WSequence* seq, int ind)
{
	if (!seq) {
#ifdef DEBUG
printf("I can't do that dave\n");
#endif
		return;
	}
	if (ind >= seq->num_frames) {
#ifdef DEBUG
printf("I _really_ can't do that dave\n");
#endif
		return;
	}

	seq->current_frame_index = ind;
	seq->current_frame       = seq->frames[ind];

	w_sequence_ensure_frame(seq);
}

void w_sequence_frame_add(WSequence* seq)
{

	// seq->current_frame_index;
	seq->num_frames++;

	_check_realloc(seq);

	WObject* fr = w_object_create(NULL);

	if (seq->current_frame_index < seq->num_frames - 1)
		seq->current_frame_index++;

	seq->frames[seq->current_frame_index] = fr;
	
#ifdef DEBUG
//printf("added frame %d (%d)\n", seq->current_frame_index, seq->num_frames);
#endif

	// seq->current_frame_index = cfi;
	seq->current_frame = seq->frames[seq->current_frame_index];
	
	
	
	// seq->num_frames = num;
}

void w_sequence_frame_duplicate(WSequence* seq)
{

	// int num = seq->num_frames;
	int pos = seq->current_frame_index;

	seq->num_frames++;
#ifdef DEBUG

	printf("duplicate frame at %d\n", pos);
#endif
	_check_realloc(seq);

	WObject* orig = seq->frames[pos];
	//	new thingy
	WObject* cpy = w_object_copy(orig);

	// move everything after n up
	for (int i = seq->num_frames; i > pos; --i) {
		seq->frames[i] = seq->frames[i - 1];
	}

	seq->frames[pos] = cpy;
	pos++;
	seq->current_frame_index = pos;
	seq->current_frame       = seq->frames[seq->current_frame_index];
	w_sequence_ensure_frame(seq);
}

void w_sequence_frame_insert(WSequence* seq)
{

	// int num = seq->num_frames;
	int pos = seq->current_frame_index;

	seq->num_frames++;
#ifdef DEBUG

	printf("insert frame at %d\n", pos);
#endif
	seq->frames = realloc(seq->frames, sizeof(WObject*) * seq->num_frames);

	// move everything after n up
	for (int i = seq->num_frames; i > pos; --i) {
		seq->frames[i] = seq->frames[i - 1];
	}

	seq->frames[pos] = w_object_create(NULL);
	pos++;
	seq->current_frame_index = pos - 1;
	seq->current_frame       = seq->frames[seq->current_frame_index];
	w_sequence_ensure_frame(seq);
}

void w_sequence_frame_delete(WSequence* seq)
{

	int pos = seq->current_frame_index;

	int num = seq->num_frames;
	if (num <= 1) {
#ifdef DEBUG
	printf("Can't delete last frame :O\n");
#endif
		return;
	}
	WObject* fr = seq->frames[pos];
	free(fr);
	for (int i = pos; i < num - 1; ++i) {
		seq->frames[i] = seq->frames[i + 1];
	}
	seq->current_frame_index--;
	if (seq->current_frame_index < 0)
		seq->current_frame_index = 0;
	seq->current_frame = seq->frames[seq->current_frame_index];
	seq->num_frames--;
	w_sequence_ensure_frame(seq);
}

void w_sequence_destroy(WSequence* seq)
{
	for ( int i = 0 ; i < seq->num_frames; i++ )
	{
		WObject* frame = seq->frames[i];
		
		if ( frame )
			w_object_destroy(frame);
	}
}

void w_sequence_frame_next(WSequence* seq)
{

	if (!seq)
		return;

	if (seq->num_frames == 0) {
#ifdef DEBUG
	printf("can't do next frame, no frames!\n");
#endif
		return;
	}
	seq->current_frame_index++;

	w_sequence_ensure_frame(seq);
}

void w_sequence_frame_prev(WSequence* seq)
{
	if (!seq)
		return;

	if (seq->num_frames == 0) {
#ifdef DEBUG
	printf("can't do next frame, no frames!\n");
#endif
		return;
	}

	seq->current_frame_index--;

	w_sequence_ensure_frame(seq);
}

void w_sequence_normalize_time_continuous(WSequence* seq)
{
	
	for (int i = 0; i < seq->num_frames; ++i)
	{
		WObject* fr = seq->frames[i];
		w_object_normalize_time_continuous(fr);
	}

}


void w_sequence_normalize_time_exploded(WSequence* seq)
{
	
	for (int i = 0; i < seq->num_frames; ++i) {
		WObject* fr = seq->frames[i];
		w_object_normalize_time_exploded(fr);
		
		// SHOW HACKS HAX
		//return;
	}
	
}

#define SWAP(T, a, b) do { T tmp = a; a = b; b = tmp; } while (0)
static void _calc_subobjects(WSequence* seq )
{
	for (int i = 0; i < seq->num_frames; ++i) {
		WObject* o = seq->frames[i];
		w_object_calc_bounds(o);
	}

	
}

void w_sequence_calc_bounds(WSequence* seq)
{
	if (!seq) {
#ifdef DEBUG

		printf("tried to calc bounds for a null sequence.\n");
#endif
		return;
	}
	
	for (int i = 0; i < seq->num_frames; ++i) {
		WObject* o = seq->frames[i];
		w_object_calc_bounds(o);
	}
	
	double minx, miny, maxx, maxy;
	
	minx = miny = INFINITY;
	maxx = maxy = -INFINITY;

	for (int i = 0; i < seq->num_frames; ++i) {
		WObject* fr = seq->frames[i];
		double   x1 = fr->bounds.pos.x;
		double   y1 = fr->bounds.pos.y;
		double   x2 = fr->bounds.pos.x + fr->bounds.size.x;
		double   y2 = fr->bounds.pos.y + fr->bounds.size.y;
		
		if ( x1 < minx )
			minx = x1;
		if ( x2 > maxx)
			maxx = x2;
		if ( y1 < miny)
			miny = y1;
		if ( y2 > maxy)
			maxy = y2;
	}
	
	seq->bounds.pos.x  = minx;
	seq->bounds.pos.y  = miny;
	seq->bounds.size.x = maxx - minx;
	seq->bounds.size.y = maxy - miny;
	
}

void w_sequence_normalize(WSequence* seq)
{
	if (!seq) {
#ifdef DEBUG
	printf("tried to normalize a null sequence.\n");
#endif
		return;
	}
	
	_calc_subobjects(seq);
	
	double minx, miny, maxx, maxy;
	
	minx = miny = INFINITY;
	maxx = maxy = -INFINITY;

	for (int i = 0; i < seq->num_frames; ++i) {
	
		WObject* fr = seq->frames[i];
		
		//	you have no geo, you don't get to vote!
		if ( fr->num_lines == 0 )
			continue;
		
		double   x1 = fr->bounds.pos.x;
		double   y1 = fr->bounds.pos.y;
		double   x2 = fr->bounds.pos.x + fr->bounds.size.x;
		double   y2 = fr->bounds.pos.y + fr->bounds.size.y;

		if ( x1 < minx )
			minx = x1;
		if ( x2 > maxx)
			maxx = x2;
		if ( y1 < miny)
			miny = y1;
		if ( y2 > maxy)
			maxy = y2;
	}

	seq->bounds.pos.x  = minx;
	seq->bounds.pos.y  = miny;
	seq->bounds.size.x = maxx - minx;
	seq->bounds.size.y = maxy - miny;

	double dx = maxx - minx;
	double dy = maxy - miny;
	
	seq->transform.scale.x = dx;
	seq->transform.scale.y = dy;
	for (int i = 0; i < seq->num_frames; ++i) {
		WObject* fr = seq->frames[i];

		for (int j = 0; j < fr->num_lines; ++j) {
			WLine* l = fr->lines[j];
			for (unsigned long long k = 0; k < l->num; ++k) {
				WPoint* p = &l->data[k];
				p->x /= dx;
				p->y /= dy;
			}
		}
		fr->normalized	= true;
		fr->transform.scale.x = seq->transform.scale.x;
		fr->transform.scale.y = seq->transform.scale.y;
	}
	
	_calc_subobjects(seq);

	
}

void w_sequence_move(WSequence* seq, double dx, double dy)
{
	for ( unsigned int i = 0 ;i < seq->num_frames; i++ )
	{
		WObject* frame = seq->frames[i];
		w_object_move(frame, dx, dy);
	}
}

void w_sequence_scale(WSequence* seq, double modx, double mody)
{
	for ( unsigned int i = 0 ;i < seq->num_frames; i++ )
	{
		WObject* frame = seq->frames[i];
		w_object_scale(frame, modx, mody);
	}
}


void w_sequence_center(WSequence* seq)
{

	//	todo: collapse this into a single call
	
	//double dx = seq->bounds.pos.x + (seq->bounds.size.x * .5);
	//double dy = seq->bounds.pos.y + (seq->bounds.size.y * .5);
	//printf("Centering to %f %f\n", dx, dy );
	for ( unsigned int i = 0 ;i < seq->num_frames; i++ )
	{
		WObject* frame = seq->frames[i];
		w_object_move(frame, -seq->bounds.pos.x, -seq->bounds.pos.y);
		w_object_move(frame, -seq->bounds.size.x * .5, -seq->bounds.size.y * .5);
	}
	
}

void w_sequence_set_closed(WSequence* seq, bool val)
{
	for ( unsigned int i = 0 ;i < seq->num_frames; i++ )
	{
		WObject* frame = seq->frames[i];
		w_object_set_closed(frame, val);
	}
	
}
