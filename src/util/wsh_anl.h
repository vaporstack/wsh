
//  wsh_anl.c
//  wsh_anl
//
//  Created by Andrew Macfarlane on 07/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef wsh_anl_h_
#define wsh_anl_h_

#include "../geo/wsh_line.h"

typedef struct WLineAnalysis
{
	double* angles;
	double* deltas;

} WLineAnalysis;

WLineAnalysis* wsh_anl_create(WLine* l);
void	   wsh_anl_destroy(WLineAnalysis* anl);

#endif
