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

void drw_color_clear(double r, double g, double b, double a);
void drw_clear(void);
void drw_setup(int width, int height);
void drw_setup_view_ortho(int w, int h);

void drw_set_dpiscale(double v);

void drw_push(void);
void drw_pop(void);
void drw_scale(double x, double y, double z);
void drw_scale_u(double v);

void drw_translate(double x, double y, double z);
void drw_translate2f(double x, double y);
void drw_color(double r, double g, double b, double a);

void drw_line(double ax, double ay, double bx, double by);
void drw_circle(float);
void drw_ellipse(float, float);
void drw_poly(WLine*);

//	wash primitives
void drw_verts(WLine*);
void drw_wobject_verts(WObject* obj);
void drw_wline_fill(WLine* line);
void drw_wline(WLine* line);
void drw_wline_strokeonly(WLine* line);
void drw_wobject(WObject*);
void drw_wobject_strokeonly_notransform(WObject*);
void drw_wobject_strokeonly(WObject*);
void drw_wobject_notransform(WObject*);
void drw_wobject_e(WObject*);

void drw_rect(float, float, float, float);

#endif /* primitives_h */
