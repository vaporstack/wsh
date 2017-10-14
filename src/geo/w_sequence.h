
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
	struct WObject* current_frame;
	struct WObject* parent;

	double anim_duration;
	int anim_type;
	WRect bounds;
	WTransform transform;

} WSequence;


typedef struct WSequenceHnd
{
	WSequence* src;
} WSequenceHnd;

WSequence*		w_sequence_create(void);
void			w_sequence_destroy(WSequence* );

	WSequenceHnd*	w_sequence_hnd_create(void);
void			w_sequence_hnd_destroy(WSequenceHnd*);

WSequence*		w_sequence_copy(WSequence* seq);

//old
void 		w_sequence_frame_create(WSequence*,int );

void		w_sequence_frame_set(WSequence *, int);
void		w_sequence_frame_next(WSequence *);
void		w_sequence_frame_prev(WSequence*);
void		w_sequence_frame_add(WSequence* seq);
void		w_sequence_frame_insert(WSequence* seq);
void		w_sequence_frame_delete(WSequence* seq);

void		w_sequence_frame_duplicate(WSequence* seq);

void		w_sequence_normalize(WSequence*);

#endif



