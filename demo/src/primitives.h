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

void d_color(double r, double g, double b, double a);


//	wash primitives

void d_init(void);
void d_setup_projection(int w, int h);

void d_rect_w(WRect);
void d_rect(float, float, float, float);
void d_rect_wp(WPoint a, WPoint b);
void d_square(float);
void d_square_at(float, float, float);
void d_circle(float);

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
