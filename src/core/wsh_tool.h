//
//  wsh_tool.h
//  wsh
//
//  Created by vs on 3/15/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef wsh_tool_h
#define wsh_tool_h

#include "../core/w_color.h"

typedef struct WshToolRec
{
	const char* name;
	const char* identifier;
	const char* desc;
	
	double attack;
	double decay;
	double sustain;
	double release;

	double size_base;
	double size_inner;
	double size_outer;
	double size_perim;

	double size_mod;

	WColor16  color;
	WColor16* colors;
	int       color_num;

	void* textures;
	int   texture_num;

} WshToolRec;

typedef struct WshToolRecDelta
{
	double*    attack;
	double*    decay;
	double*    sustain;
	double*    release;
	double *   size_base, size_inner, size_outer, size_perim;
	double*    size_mod;
	WColor16*  color;
	WColor16** colors;
	int*       color_num;
	void*      textures;
	int*       texture_num;
} WshToolRecDelta;

WshToolRecDelta* wsh_tool_rec_delta_create(void);
WshToolRecDelta* wsh_tool_rec_diff(WshToolRec* a, WshToolRec* b);

WshToolRec* wsh_tool_rec_create(void);
void	wsh_tool_rec_destroy(WshToolRec* rec);

#endif /* wsh_tool_h */
