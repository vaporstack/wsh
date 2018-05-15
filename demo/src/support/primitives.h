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

void d_color_clear(double r, double g, double b, double a);
void d_clear(void);
void d_setup(int width, int height);
void d_setup_view_ortho(int w, int h);

void d_set_dpiscale(double v);

void drw_push(void);
void d_pop(void);
void d_translate(double x, double y, double z);
void d_color(double r, double g, double b, double a);

void drw_line(double ax, double ay, double bx, double by);
void d_circle(float);
void d_ellipse(float, float);
void d_poly(WLine*);

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

void d_rect(float, float, float, float);

#endif /* primitives_h */
