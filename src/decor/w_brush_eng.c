
//  w_brush_eng.c
//  w_brush_eng
//
//  Created by Andrew Macfarlane on 04/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "w_brush_eng.h"

static WLineHnd** brushes = NULL;
static long num_brushes = 0;

#include <stdio.h>

void	w_brush_line_add(WLineHnd* hnd)
{


}

void	w_brush_line_remove(WLineHnd* hnd)
{


}

void	w_brush_eng_draw()
{


}

void	w_brush_eng_update()
{
	for ( int i = 0 ;i < num_brushes; ++i )
	{
		WLineHnd* hn = brushes[i];

	}
}

int		w_brush_eng_init()
{
	printf("Initializing brush engine.\n");

	return 0;
}

void	w_brush_eng_deinit()
{


}
