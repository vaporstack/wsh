//
//  w_sequence_ops.c
//  wsh
//
//  Created by vs on 5/14/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include "w_sequence_ops.h"

//	collapse a sequence to a single frame

WObject* w_sequence_collapse(WSequence* seq )
{
	// only one frame, no need
	if ( seq->num_frames == 1 )
	{
		//	assuming somethinghere
		return w_object_copy(seq->frames[0]);
	}
	WObject* res = w_object_create(NULL);
	//	w_sequence_frame_add(res);
	printf("Collapsing a sequence of %d frames\n", seq->num_frames);
	int total = 0;
	for ( int i =0; i < seq->num_frames; i++ )
	{
		WObject* fr = seq->frames[i];
		for ( int j = 0 ; j < fr->num_lines; j++ )
		{
			WLine* nl = fr->lines[j];
			w_object_add_line(fr, nl);
			total++;
		}
	}
	printf("Collapsed %d lines.\n", total);
	
	return res;
	
}
