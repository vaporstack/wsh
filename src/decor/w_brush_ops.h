//
//  w_brush_ops.h
//  wsh
//
//  Created by vs on 9/16/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef w_brush_ops_h
#define w_brush_ops_h

#include <stdio.h>
#include "../geo/w_object.h"

void	w_brush_ops_object_brushfunc(WObject* obj, brush_update_func func);

void	w_brush_ops_object_brushwidth(WObject* obj, double size);

#endif /* w_brush_ops_h */
