//
//  w_brush_ops.c
//  wsh
//
//  Created by vs on 9/16/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "w_brush_ops.h"

static void w_brush_ops_line_brushwidth(WLine* line, double size);

void	w_brush_ops_object_brushfunc(WObject* obj, brush_update_func func)
{
	for ( int i = 0 ; i < obj->num_lines; i++ )
	{
		WLine* l = obj->lines[i];
		if ( l->brush )
		{
			func(l->brush);
		}
	}
}

void w_brush_ops_object_brushwidth(WObject* obj, double size)
{
	for ( int i = 0; i < obj->num_lines; i++  )
	{
		WLine* l = obj->lines[i];
		w_brush_ops_line_brushwidth(l, size);
	}
}


static void w_brush_ops_line_brushwidth(WLine* line, double size)
{
	if ( !line )
		return;
	
	line->brush->width = size;
	//w_brush_update(line->brush);
}

