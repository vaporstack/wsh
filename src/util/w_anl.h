
//  w_anl.c
//  w_anl
//
//  Created by Andrew Macfarlane on 07/06/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_anl_h_
#define w_anl_h_

#include "../geo/w_line.h"


typedef struct WLineAnalysis
{
	double* angles;
	double* deltas;

}	WLineAnalysis;

WLineAnalysis*	w_anl_create(WLine* l);
void			w_anl_destroy(WLineAnalysis* anl);

#endif
