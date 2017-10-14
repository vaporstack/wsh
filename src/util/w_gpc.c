
//  w_gpc.c
//  w_gpc
//
//  Created by Andrew Macfarlane on 19/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "w_gpc.h"

#include <deps/gpc/gpc.h>
#include <r4/src/r4_platform.h>


//	this belongs anywhere but here.  the core wsh library shouldn't know anything
// about rendering or tesselation choices, period.
 
 
 void w_gpc_tess_free(WLine* line)
{
#ifndef RPLATFORM_WIN

	gpc_tristrip* st = (gpc_tristrip*)line->tess;

	gpc_free_tristrip(st);

	line->tess = NULL;
#endif


}
void w_gpc_tess_create(WLine* line)
{


	//printf("Creating tesselation!\n");


	gpc_polygon			poly;
	gpc_vertex			*verts;
	verts = calloc( line->num, sizeof(gpc_vertex));
	gpc_vertex_list		contour;

	for ( unsigned long long i = 0; i < line->num; ++i )
	{
		WPoint p = line->data[i];
		verts[i].x = p.x;
		verts[i].y = p.y;
	}

	gpc_tristrip* tstrips = calloc(1, sizeof(gpc_tristrip));
	contour.vertex = verts;
	contour.num_vertices = line->num;
	poly.contour = &contour;

	poly.num_contours = 1;
	poly.hole = NULL;



	//tstrip_num = tstrips.num_strips;
	//r_color(.5,0,0,.5);
	//r_gpc_verts(poly);


	//gpc_tristrip* loc = tstrips;

	gpc_polygon_to_tristrip( &poly, tstrips);

	line->tess = tstrips;
	//line->tess = (void*)tstrips;
	//r_push();


	//r_translate_x(-128);


}


void w_gpc_tess_destroy(WLine* line)
{
#ifndef RPLATFORM_WIN

	if ( line->tess == NULL)
	{
		printf("Tried to destroy a nonexistant tess\n");
		return;
	}
	gpc_tristrip* st = (gpc_tristrip*)line->tess;
	if ( !st )
	{
		printf("Error converting tri strip\n");
		return;
	}
	gpc_free_tristrip(st);
	line->tess = NULL;
	
#endif


}






