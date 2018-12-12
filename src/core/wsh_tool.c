//
//  wsh_tool.c
//  wsh
//
//  Created by vs on 3/15/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include "wsh_tool.h"

#include <wsh/wsh.h>

#include <stdlib.h>
#define NUM_FIELDS 4

#ifdef DEBUG
#include <stdio.h>
#endif

WshToolRec* wsh_tool_rec_create(const char* name, const char* ident, const char* desc)
{

	WshToolRec* rec = calloc(1, sizeof(WshToolRec));
	rec->name       = (name);
	rec->identifier = (ident);
	rec->desc       = (desc);
	return rec;
}

void wsh_tool_rec_destroy(WshToolRec* rec)
{
	free(rec);
}

WshToolParams* wsh_tool_params_create(void)
{
	WshToolParams* rec = calloc(1, sizeof(WshToolRec));
	//rec->textures = NULL;
	//rec->colors = NULL;

	rec->size_base  = 0;
	rec->size_inner = .5;
	rec->size_outer = .75;
	rec->size_perim = 1.;

	rec->attack  = .25;
	rec->decay   = .125;
	rec->sustain = 3;
	rec->release = .125;

	rec->size_mod = 1.;

	return rec;
}

void wsh_tool_params_destroy(WshToolParams* rec)
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

WshToolParamDelta* wsh_tool_paramdelta_create(void)
{
	WshToolParamDelta* delta = calloc(1, sizeof(WshToolParamDelta));

	return delta;
}

WshToolParamDelta* wsh_tool_params_diff(WshToolParams* a, WshToolParams* b)
{
	WshToolParamDelta* r			= wsh_tool_paramdelta_create();
	double*		   fields_a[NUM_FIELDS] = {&(a->attack), &(a->decay), &(a->sustain), &(a->release)};
	double*		   fields_b[NUM_FIELDS] = {&(b->attack), &(b->decay), &(b->sustain), &(b->release)};
	double*		   fields_r[NUM_FIELDS] = {(r->attack), (r->decay), (r->sustain), (r->release)};
	for (int i = 0; i < NUM_FIELDS; i++)
	{
		double* a = fields_a[i];
		double* b = fields_b[i];
		if (*a != *b)
		{
			fields_r[i]  = calloc(1, sizeof(double));
			*fields_r[i] = *b;
		}
		//double diff = *b - *a;
		//printf("%f\n", diff);
	}

	if (r->attack)
	{
#ifdef DEBUG

		printf("A: %f\n", *r->attack);
#endif
	}

	if (r->decay)
	{
#ifdef DEBUG

		wsh_log("D: %f", *r->decay);
#endif
	}

	//	todo: fill out the rest of these fields in the diff

	return r;
}
