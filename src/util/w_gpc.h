
//  w_gpc.c
//  w_gpc
//
//  Created by Andrew Macfarlane on 19/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_gpc_h_
#define w_gpc_h_

#define WSH_ENABLE_GPC

#ifdef WSH_ENABLE_GPC

#include "../geo/w_line.h"


void w_gpc_tess_create(WLine* line);
void w_gpc_tess_destroy(WLine* line);






#endif

#endif
