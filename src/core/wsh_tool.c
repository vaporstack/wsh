//
//  wsh_tool.c
//  wsh
//
//  Created by vs on 3/15/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include "wsh_tool.h"

#include <stdlib.h>

WshToolRec* wsh_tool_rec_create(void)
{
	WshToolRec* rec = calloc(1, sizeof(WshToolRec));
	//rec->textures = NULL;
	//rec->colors = NULL;
	
	rec->size_base = 0;
	rec->size_inner = .5;
	rec->size_outer = .75;
	rec->size_perim = 1.;
	
	return rec;
}

void	wsh_tool_rec_destroy(WshToolRec* rec)
{
	if ( rec->textures )
	{
		free(rec->textures);
	}
	if ( rec->colors )
	{
		free(rec->colors);
	}
	free(rec);
	
}
