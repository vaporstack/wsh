//
//  w_sequence_ops.c
//  wsh
//
//  Created by vs on 5/14/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include "w_sequence_ops.h"

//	collapse (copy)  sequence to a single frame

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
		printf("Collapsing %d lines.\n", fr->num_lines );
		
		for ( int j = 0 ; j < fr->num_lines; j++ )
		{
			WLine* nl = fr->lines[j];
			if ( !nl )
				continue;
			if ( !nl->data)
				continue;
			
			printf("Line %d : %llu\n", j, nl->num);
			w_object_add_line(res, w_line_copy(nl));
			total++;
		}
	}
	printf("Collapsed %d lines.\n", total);
	
	return res;
	
}
