//
//  wsh_gpc.h
//  wsh
//
//  Created by vs on 12/10/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef wsh_gpc_h
#define wsh_gpc_h

//	do not uncomment this unless you have purchased a gpc license or are just testing
//	legally unsuitable for release.
	#define WSH_ENABLE_EXT_GPC


#ifdef WSH_ENABLE_EXT_GPC

#include "../geo/wsh_line.h"

typedef struct WGPCRec
{
	void* polygon;
	void* tess;
	int   num;
} WGPCRec;

void  wsh_ext_gpc_tesselate(WGPCRec* rec);
void* wsh_ext_gpc_tess_create(WLine* line);
void  wsh_ext_gpc_tess_destroy(void* tess);
void* wsh_ext_gpc_tess_create_wline(WLine* line);
//void* r_gpc_tess_create_rline(RLine* line);

//GPCRec* r_gpc_polygon_create(RLine* line);
void    wsh_ext_gpc_polygon_destroy(WGPCRec* rec);
double  wsh_ext_gpc_polygon_area(WGPCRec* rec);

//RLine** r_gpc_polygon_boolean_rlines(RLine* a, RLine* b, int op, int* rnum);
//GPCRec* r_gpc_polygon_boolean(RLine* a, RLine* b, int op);
WGPCRec* wsh_ext_gpc_polygon_boolean_raw(WGPCRec* a, WGPCRec* b, int op);
//RLine** r_gpc_rlines_from_gpc(GPCRec* rec, int* rnum);

//	unified method that takes N polygons and a single op polygon,
//
//RLine** r_gpc_slice_rline(RLine* input, RLine* op, int* onum);
//RLine** r_gpc_slice_rline_multiple(RLine** inputs, int inum, RLine* op, int* onum);

//	this one needs a full rewrite
//int	r_gpc_polygon_boolean(RLine* la, RLine* lb, RLine** res_addr, int *num);


#endif

#endif /* wsh_gpc_h */
