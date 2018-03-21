//
//  primitives.c
//  wash-demo
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "primitives.h"


//	this *should* pull in the right opengl header for us? yes.
#include "GLFW/glfw3.h"

static int fill;

void d_transform_apply(WTransform t)
{
	/*
	 d_translate_wvec(t.position);
	d_translate_wvec(t.anchor);
	d_scale_wvec(t.scale);
	d_rotate_wvec(t.rotation);
*/
	
}

void d_color(double r, double g, double b, double a)
{
	glColor4d(r, g, b, a);
}


void d_poly(WLine* line)
{
	int			 i, j;
	const unsigned long long renderLineSize = (line->num * 2);
	
	GLfloat* arr = malloc(sizeof(GLfloat) * renderLineSize);
	
	for (i = 0, j = 0; i < line->num; i++, j += 2) {
		WPoint* p = &line->data[i];
		//  todo: REMOVE THIS HACK
		
		arr[j]     = p->x;
		arr[j + 1] = p->y;
	}
	
	glVertexPointer(2, GL_FLOAT, 0, arr);
	
	if (line->closed) {
		glDrawArrays(GL_TRIANGLE_FAN, 0, (int)line->num);
		free(arr);
		return;
	}
	
	fill ? glDrawArrays(GL_TRIANGLE_FAN, 0, (int)line->num)
	: glDrawArrays(GL_LINE_STRIP, 0, (int)line->num);
	free(arr);
}
void d_rect(float ax, float ay, float bx, float by)
{
	float arr[8];
	arr[0] = ax;
	arr[1] = ay;
	arr[2] = bx;
	arr[3] = ay;
	arr[4] = bx;
	arr[5] = by;
	arr[6] = ax;
	arr[7] = by;
	
	glVertexPointer(2, GL_FLOAT, 0, &arr);
	fill ? glDrawArrays(GL_TRIANGLE_FAN, 0, 4)
	: glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void d_square(float r)
{
	d_rect(r * -.5, r * -.5, r * .5, r * .5);
}

void d_translate2f(float x, float y)
{
	glTranslatef(x, y, 0);
}

void d_translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
}


void d_push()
{
	glPushMatrix();
}

void d_pop()
{
	glPopMatrix();
}

void d_verts(WLine* l)
{
	int i;
	for (i = 0; i < l->num; ++i) {
		WPoint* p = &l->data[i];
		d_push();
		d_translate2f(p->x, p->y);
		double pv = p->pressure;
		pv *= 10;
		d_square(pv);
		d_pop();
	}
}

void d_wobject_verts(WObject* obj)
{
	int i;
	for (i = 0; i < obj->num_lines; i++) {
		WLine* line = obj->lines[i];
		if (!line) {
			printf("Error, bogus line!\n");
			continue;
		}
		d_verts(line);
	}
}

void d_init(void)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	//  todo: figure out why this becomes fucking 5 when toggling fullscreen
	
	//d_get_gl_error();
	glEnable(GL_BLEND);
#ifndef RPLATFORM_WIN
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
	
	//  MISH MASH OF CRAP FROM BEFORE THAT I DON'T FULLY GET
	glAlphaFunc(GL_GREATER, 0.1f);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	
	glEnableClientState(GL_VERTEX_ARRAY);
#ifndef RPLATFORM_WIN
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif
	
#ifndef RPLATFORM_IOS
	glHint(GL_POLYGON_SMOOTH_HINT, GL_FASTEST);
	glEnable(GL_POLYGON_SMOOTH);
#endif


}

void d_setup_projection(int w, int h )
{
	glViewport(0, 0, w, h);

}

void d_rect_w(WRect r)
{
	d_rect(r.pos.x, r.pos.y, r.pos.x + r.size.x, r.pos.y + r.size.y);
}

void d_wobject_normal(WObject* obj)
{
	// d_color(1,1,1,.9);
	d_push();
	d_translate(obj->transform.position.x, obj->transform.position.y,
		    obj->transform.position.z);
	
	//d_scale_2f(obj->transform.scale.x, obj->transform.scale.y);
	int i;
	
	for (i = 0; i < obj->num_lines; ++i) {
		WLine* l = obj->lines[i];
		if (!l) {
			printf("ack!\n");
			return;
		}
		
		d_poly(l);
	}
	
	d_pop();
}

void d_wobject_naive(WObject* obj)
{
	
	d_rect_w(obj->bounds);
	
	if (!obj) {
		printf("Error, tried to render a null obj!\n");
		return;
	}
	if (!obj->lines) {
		printf("no lines either!?\n");
		return;
	}
	
	int i;
	
	for (i = 0; i < obj->num_lines; ++i) {
		WLine* l = obj->lines[i];
		if (!l) {
			printf("ack!\n");
			return;
		}
		
		d_poly(l);
	}
}

void d_wobject_e(WObject* obj)
{
	
	if (obj->normalized) {
		d_wobject_normal(obj);
		
	} else {
		d_wobject_naive(obj);
	}
}

void d_wline_fill(WLine* l)
{
	//d_set_fill(true);
	d_poly(l);
	//d_pop_fill();
}

static void _wlinepoly(WLine* line)
{
}

void d_wline_strokeonly(WLine* l)
{
	if (l == NULL) {
		printf("Tried to render a null line!\n");
		return;
	}
	
	d_poly(l);
}

void d_wline(WLine* l)
{
	if (l == NULL) {
		printf("Tried to render a null line!\n");
		return;
	}
	
	/*if (!color_bypass) {
		if (l->has_stroke) {
			WColor16 c = l->stroke;
			d_color(c.r, c.g, c.b, c.a * alpha_mult);
			/// dirty hack to have color and also transparent onion
			/// skins oops
			//r_alpha(c.a * alpha_mult);
		}
		if (l->closed) {
			d_set_fill(l->closed);
			d_poly(l);
			d_pop_fill();
		}
		if (l->has_stroke) {
			//r_alpha_pop();
		}
	} else {
	}*/
	
#ifdef DISABLE_UNTIL_WORKLINE_REFACTOR_COMPLETE
	
	if (l->brush) {
		if (l->tess) {
			d_gpc_tristrip(l->tess);
			return;
		}
		
		if (l->brush->stroke) {
			if (l->brush->stroke->tess) {
				d_gpc_tristrip(l->brush->stroke->tess);
				
			} else {
				
				d_triangle_strip(l->brush->stroke);
			}
		}
		// else{
		
		//  d_poly(l->brush->stroke);
		//}
	} else {
		
		if (l->tess) {
			d_gpc_tristrip(l->tess);
		} else {
			d_poly(l);
		}
	}
#else
	d_poly(l);
#endif
	//  TODO color pop?
}

void d_wobject(WObject* obj)
{
	
	// d_rect_w(obj->bounds);
	
	if (!obj) {
		printf("Error, tried to render a null obj!\n");
		return;
	}
	if (!obj->lines) {
		// printf("no lines either!?\n");
		return;
	}
	
	d_push();
	d_transform_apply(obj->transform);
	int i;
	for (i = 0; i < obj->num_lines; ++i) {
		
		WLine* l = obj->lines[i];
		if (!l)
			continue;
		
		if (!l) {
			printf("ack!\n");
			continue;
		}
		if ( !l->data)
		{
			printf("AAACK\n");
			continue;
		}
		d_wline(l);
	}
	d_pop();
}

void d_wobject_notransform(WObject* obj)
{
	
	// d_rect_w(obj->bounds);
	
	if (!obj) {
		printf("Error, tried to render a null obj!\n");
		return;
	}
	if (!obj->lines) {
		// printf("no lines either!?\n");
		return;
	}
	
	d_push();
	//d_transform_apply(obj->transform);
	int i;
	for (i = 0; i < obj->num_lines; ++i) {
		
		WLine* l = obj->lines[i];
		if (!l)
			continue;
		
		if (!l) {
			printf("ack!\n");
			return;
		}
		
		d_wline(l);
	}
	d_pop();
}

void d_wobject_strokeonly(WObject* obj)
{
	
	// d_rect_w(obj->bounds);
	
	if (!obj) {
		printf("Error, tried to render a null obj!\n");
		return;
	}
	if (!obj->lines) {
		// printf("no lines either!?\n");
		return;
	}
	
	d_push();
	d_transform_apply(obj->transform);
	int i;
	for (i = 0; i < obj->num_lines; ++i) {
		
		WLine* l = obj->lines[i];
		if (!l)
			continue;
		
		if (!l) {
			printf("ack!\n");
			return;
		}
		
		d_wline_strokeonly(l);
	}
	d_pop();
}

void d_wobject_strokeonly_notransform(WObject* obj)
{
	
	// d_rect_w(obj->bounds);
	
	if (!obj) {
		printf("Error, tried to render a null obj!\n");
		return;
	}
	if (!obj->lines) {
		// printf("no lines either!?\n");
		return;
	}
	
	d_push();
	//d_transform_apply(obj->transform);
	int i;
	for (i = 0; i < obj->num_lines; ++i) {
		
		WLine* l = obj->lines[i];
		if (!l)
			continue;
		
		if (!l) {
			printf("ack!\n");
			return;
		}
		
		d_wline_strokeonly(l);
	}
	d_pop();
}

