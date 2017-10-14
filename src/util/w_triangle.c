//
//  w_triangle.c
//  wsh
//
//  Created by Andrew Macfarlane on 4/19/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "w_triangle.h"

#include <stdlib.h>

//#define TRILIBRARY
//#define ANSI_DECLARATORS

#ifdef SINGLE
#define REAL float
#else /* not SINGLE */
#define REAL double
#endif /* not SINGLE */



#include <deps/triangle/triangle.h>


void w_triangle_test()
{

	//triangulate();
}
