//
//  wsh_sequence_ops.c
//  wsh
//
//  Created by vs on 5/14/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include <wsh/wsh.h>
#include "wsh_sequence_ops.h"

//	collapse (copy)  sequence to a single frame

WObject* wsh_sequence_ops_collapse(WSequence* seq)
{
	// only one frame, no need
	if (seq->num_frames == 1)
	{
		//	assuming somethinghere
		return wsh_object_copy(seq->frames[0]);
	}
	WObject* res = wsh_object_create(NULL);
	//	wsh_sequence_frame_add(res);
#ifdef DEBUG
	wsh_log("Collapsing a sequence of %d frames", seq->num_frames);
#endif
	int total = 0;
	for (int i = 0; i < seq->num_frames; i++)
	{
		WObject* fr = seq->frames[i];
#ifdef DEBUG
		wsh_log("Collapsing %d lines.", fr->num);
#endif

		for (int j = 0; j < fr->num; j++)
		{
			WLine* nl = fr->lines[j];
			if (!nl)
				continue;
			if (!nl->data)
				continue;

#ifdef DEBUG
				//printf("Line %d : %llu\n", j, nl->num);
#endif
			wsh_object_add_line(res, wsh_line_copy(nl));
			total++;
		}
	}
#ifdef DEBUG
	printf("Collapsed %d lines.\n", total);
#endif

	return res;
}