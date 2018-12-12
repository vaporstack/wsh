//
//  wsh_gpc.c
//  wsh
//
//  Created by vs on 12/10/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include "wsh_gpc.h"

#ifdef WSH_ENABLE_EXT_GPC

#include <deps/gpc/gpc.h>

void* wsh_ext_gpc_tess_create_wline(WLine* line)
{
	
	// printf("Creating tesselation!\n");
	
	gpc_polygon poly;
	gpc_vertex* verts;
	verts = calloc(line->num, sizeof(gpc_vertex));
	gpc_vertex_list contour;
	
	//WLine* line = brush->hnd.src;
	
	for (unsigned long long i = 0; i < line->num; ++i)
	{
		WPoint p   = line->data[i];
		verts[i].x = p.x;
		verts[i].y = p.y;
	}
	
	gpc_tristrip* tstrips = calloc(1, sizeof(gpc_tristrip));
	contour.vertex	= verts;
	contour.num_vertices  = line->num;
	poly.contour	  = &contour;
	
	poly.num_contours = 1;
	poly.hole	 = NULL;
	
	// tstrip_num = tstrips.num_strips;
	// r_color(.5,0,0,.5);
	// drw_gpc_verts(poly);
	
	// gpc_tristrip* loc = tstrips;
	
	gpc_polygon_tr_tristrip(&poly, tstrips);
	return tstrips;
	//line->tess = tstrips;
	// line->tess = (void*)tstrips;
	// r_push();
	
	// r_translate_x(-128);
}




#endif

