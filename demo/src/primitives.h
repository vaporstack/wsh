//
//  primitives.h
//  wash-demo
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef primitives_h
#define primitives_h

#include <wsh/wsh.h>

//	wash primitives
void d_verts(WLine*);
void d_wobject_verts(WObject* obj);
void d_wline_fill(WLine* line);
void d_wline(WLine* line);
void d_wline_strokeonly(WLine* line);
void d_wobject(WObject*);
void d_wobject_strokeonly_notransform(WObject*);
void d_wobject_strokeonly(WObject*);
void d_wobject_notransform(WObject*);
void d_wobject_e(WObject*);

#endif /* primitives_h */
