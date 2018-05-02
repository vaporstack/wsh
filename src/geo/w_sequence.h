
//  w_sequence.c
//  w_sequence
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_sequence_h_
#define w_sequence_h_

#include "w_object.h"

typedef struct WSequence
{
	//	todo: clean this up!

	int reserved;
	int num_frames;
	int current_frame_index;
	int num_golden_frames;

	int* golden_frames;

	struct WObject** frames;
	struct WObject*  current_frame;
	struct WObject*  parent;
	
	//double anim_start;
	//double anim_end;
	double     anim_duration;
	int	anim_type;
	WRect      bounds;
	WTransform transform;

} WSequence;

typedef struct WSequenceHnd
{
	WSequence* src;
} WSequenceHnd;

WSequence* w_sequence_create(void);
void       w_sequence_destroy(WSequence* seq );

WSequenceHnd* w_sequence_hnd_create(void);
void	  w_sequence_hnd_destroy(WSequenceHnd* hnd);

WSequence* w_sequence_copy(WSequence* seq);

void w_sequence_normalize_time_continuous(WSequence* seq);
void w_sequence_normalize_time_exploded(WSequence* seq);

void w_sequence_frame_create(WSequence*, int index);
void w_sequence_ensure_frame(WSequence* seq);

void w_sequence_frame_set(WSequence*, int);
void w_sequence_frame_next(WSequence* seq);
void w_sequence_frame_prev(WSequence* seq);
void w_sequence_frame_add(WSequence* seq);
void w_sequence_frame_insert(WSequence* seq);
void w_sequence_frame_delete(WSequence* seq);

void w_sequence_frame_duplicate(WSequence* seq);

void w_sequence_calc_bounds(WSequence* seq);
void w_sequence_normalize(WSequence* seq);;

void w_sequence_move(WSequence* seq, double dx, double dy);
void w_sequence_scale(WSequence* seq, double modx, double mody);
void w_sequence_center(WSequence* seq);
void w_sequence_set_closed(WSequence* seq, bool val);

void w_sequence_transform_reset(WSequence* seq);

#endif
