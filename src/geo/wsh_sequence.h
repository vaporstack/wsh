
//  wsh_sequence.c
//  wsh_sequence
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef wsh_sequence_h_
#define wsh_sequence_h_

#include "wsh_object.h"

typedef struct WSequence
{
	//	todo: clean this up!

	unsigned reserved;
	unsigned num_frames;
	signed current_frame_index;
	unsigned num_golden_frames;

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

WSequence* wsh_sequence_create(void);
void       wsh_sequence_destroy(WSequence* seq);

WSequenceHnd* wsh_sequence_hnd_create(void);
void	  wsh_sequence_hnd_destroy(WSequenceHnd* hnd);

WSequence* wsh_sequence_copy(WSequence* seq);

void wsh_sequence_normalize_time_continuous(WSequence* seq);
void wsh_sequence_normalize_time_exploded(WSequence* seq);

void wsh_sequence_frame_create(WSequence*, unsigned index);
void wsh_sequence_ensure_frame(WSequence* seq);

void wsh_sequence_frame_set(WSequence*, unsigned index);
void wsh_sequence_frame_next(WSequence* seq);
void wsh_sequence_frame_prev(WSequence* seq);

/*
 *	add a frame after the current frame
 */
void wsh_sequence_frame_add(WSequence* seq);

/*
 *	add a frame at an arbitrary index
 */
void wsh_sequence_frame_insert(WSequence* seq);

/*
 *	add a frame at an arbitrary location
 */
//void wsh_sequence_frame_insert_index(WSequence* seq, unsigned int );

void wsh_sequence_frame_delete(WSequence* seq);
void wsh_sequence_frame_duplicate(WSequence* seq);

void wsh_sequence_calc_bounds(WSequence* seq);
void wsh_sequence_normalize(WSequence* seq);
void wsh_sequence_normalize_all_lines_individually(WSequence* seq);

void wsh_sequence_move(WSequence* seq, double dx, double dy);
void wsh_sequence_scale(WSequence* seq, double modx, double mody);
void wsh_sequence_center(WSequence* seq);
void wsh_sequence_set_closed(WSequence* seq, bool val);

void wsh_sequence_transform_reset(WSequence* seq);

#endif
