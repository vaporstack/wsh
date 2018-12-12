//
//  wsh_tool.h
//  wsh
//
//  Created by vs on 3/15/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef wsh_tool_h
#define wsh_tool_h

#include "../core/wsh_color.h"

typedef struct WshToolRec
{
	const char* name;
	const char* identifier;
	const char* desc;
} WshToolRec;

typedef struct WshToolParams
{
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

} WshToolParams;

typedef struct WshToolParamDelta
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
} WshToolParamDelta;

WshToolRec*	wsh_tool_rec_create(const char* name, const char* ident, const char* desc);
void		   wsh_tool_rec_destroy(WshToolRec* rec);
WshToolParams*     wsh_tool_params_create(void);
void		   wsh_tool_params_destroy(WshToolParams* rec);
WshToolParamDelta* wsh_tool_paramdelta_create(void);
WshToolParamDelta* wsh_tool_params_diff(WshToolParams* a, WshToolParams* b);

#endif /* wsh_tool_h */
