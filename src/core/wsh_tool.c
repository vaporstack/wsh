//
//  wsh_tool.c
//  wsh
//
//  Created by vs on 3/15/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include "wsh_tool.h"

#include <stdlib.h>
#define NUM_FIELDS 4
#include <stdio.h>

WshToolRecDelta* wsh_tool_rec_diff(WshToolRec* a, WshToolRec* b)
{
	WshToolRec* result		 = wsh_tool_rec_create();
	double*     fields_a[NUM_FIELDS] = {&(a->attack), &(a->sustain), &(a->decay), &(a->release)};
	double*     fields_b[NUM_FIELDS] = {&(b->attack), &(b->sustain), &(b->decay), &(b->release)};
	for (int i = 0; i < NUM_FIELDS; i++)
	{
		double* a = fields_a[i];
		double* b = fields_b[i];
		//if ( )
		double diff = *b - *a;
		printf("%f\n", diff);
	}

	return NULL;
}

WshToolRec* wsh_tool_rec_create(void)
{
	WshToolRec* rec = calloc(1, sizeof(WshToolRec));
	//rec->textures = NULL;
	//rec->colors = NULL;

	rec->size_base  = 0;
	rec->size_inner = .5;
	rec->size_outer = .75;
	rec->size_perim = 1.;

	return rec;
}

void wsh_tool_rec_destroy(WshToolRec* rec)
{
	if (rec->textures)
	{
		free(rec->textures);
	}
	if (rec->colors)
	{
		free(rec->colors);
	}
	free(rec);
}
