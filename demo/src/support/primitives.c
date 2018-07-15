//
//  primitives.c
//  wash-demo
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "primitives.h"

//	this *should* pull in the right opengl header for us? yes.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#define CIRCLE_PRECISION 16

static int    fill;
static double dpi = 1;

void drw_color_clear(double r, double g, double b, double a)
{
	glClearColor(r, g, b, a);
}

void drw_line(double ax, double ay, double bx, double by)
{
	glBegin(GL_LINES);
	glVertex2f(ax, ay);
	glVertex2f(bx, by);
	glEnd();
}

void drw_set_dpiscale(double v)
{
	printf("setting dpi to %f\n", v);
	dpi = v;
}

void drw_setup_view_ortho(int w, int h)
{

	glViewport(0, 0, (int)w * dpi, (int)h * dpi);

	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double l = w * -.5;
	double r = w * .5;
	double t = h * .5;
	double b = h * -.5;
	double n = -w;
	double f = w;
	glOrtho(0, w * dpi, 0, h * dpi, n, f);
}

void drw_setup(int width, int height)
{
	glEnableClientState(GL_VERTEX_ARRAY);

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

	double x = width;
	double y = height;

	float pixelAspect = 1.f;

	// bool landscape = true;

	// landscape
	if (x > y)
	{
		pixelAspect = (float)x / (float)y;
		// landscape = true;
	}

	// portrait
	if (y > x)
	{
		pixelAspect = (float)y / (float)x;
	}

	drw_setup_view_ortho(width, height);
}

void drw_push()
{
	glPushMatrix();
}

void drw_pop()
{
	glPopMatrix();
}

void drw_clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void drw_translate(double x, double y, double z)
{
	glTranslatef(x, y, z);
}
void drw_scale(double x, double y, double z)
{
	glScaled(x, y, z);
}
void drw_scale_u(double v)
{
	glScaled(v, v, v);
}

void drw_translate2f(double x, double y)
{
	glTranslatef(x, y, 0);
}

void drw_color(double r, double g, double b, double a)
{

	glColor4d(r, g, b, a);
}

void drw_rect(float ax, float ay, float bx, float by)
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

void drw_square(float r)
{
	drw_rect(r * -.5, r * -.5, r * .5, r * .5);
}
/*
void drw_translate2f(double x, double y)
{
	glTranslatef(x, y, 0);
}
*/
void drw_verts(WLine* l)
{
	int i;
	for (i = 0; i < l->num; i++)
	{
		WPoint* p = &l->data[i];
		drw_push();
		drw_translate2f(p->x, p->y);
		double pv = p->pressure;
		pv *= 10;
		drw_square(pv);
		drw_pop();
	}
}

void drw_wobject_verts(WObject* obj)
{
	int i;
	for (i = 0; i < obj->num; i++)
	{
		WLine* line = obj->lines[i];
		if (!line)
		{
			printf("Error, bogus line!\n");
			continue;
		}
		drw_verts(line);
	}
}

void drw_circle(float r)
{
	drw_ellipse(r, r);
	/*
	 float* circle = circle_defs[CIRCLE_PRECISION];
	 if (circle == NULL) {
	 printf("calculating circle for %i\n", CIRCLE_PRECISION);
	 calculate_circle(CIRCLE_PRECISION);
	 }
	 circle = circle_defs[CIRCLE_PRECISION];
	 glVertexPointer(2, GL_FLOAT, 0, circle);

	 // cout << "c:" << circleArray[2] << endl;
	 drw_scale_u(r);
	 fill ? glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_PRECISION)
	 : glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_PRECISION);

	 //r_ellipse(r, r);
	 */
}

void drw_ellipse(float _x, float _y)
{
	/*if ( _x == _y )
	 {
	 drw_circle(_x);
	 return;
	 }*/

	// glEnableClientState( GL_VERTEX_ARRAY );

	// glEnable(GL_BLEND);
	// glBlendEquation(GL_FUNC_ADD);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float deg2rad = (M_PI / CIRCLE_PRECISION);

	const int renderLineSize = (CIRCLE_PRECISION * 2);

	GLfloat* arr = malloc(sizeof(GLfloat) * renderLineSize);
	// GLfloat circleArray[ renderLineSize ];
	int i;
	for (i = 0; i < renderLineSize; i += 2)
	{
		float degInRad = deg2rad * (float)i;
		float x	= cos(degInRad + M_PI * .5) * (_x);
		float y	= sin(degInRad + M_PI * .5) * (_y);
		arr[i]	 = x;
		arr[i + 1]     = y;
	}

	// cout << '+';
	glVertexPointer(2, GL_FLOAT, 0, arr);

	// cout << "c:" << circleArray[2] << endl;
	fill ? glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_PRECISION)
	     : glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_PRECISION);

	free(arr);

	// fill ?
	// glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_PRECISION ):
	// glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_PRECISION );
}

void drw_wobject(WObject* obj)
{

	// drw_rect_w(obj->bounds);

	if (!obj)
	{
		printf("Error, tried to render a null obj!\n");
		return;
	}

	if (!obj->lines)
	{
		// printf("no lines either!?\n");
		return;
	}

	drw_push();
	//drw_transform_apply(obj->transform);
	int i;
	for (i = 0; i < obj->num; ++i)
	{

		WLine* l = obj->lines[i];
		if (!l)
			continue;

		if (!l)
		{
			printf("ack!\n");
			continue;
		}
		if (!l->data)
		{
			printf("AAACK\n");
			continue;
		}
		drw_wline(l);
	}
	drw_pop();
}

void drw_wline(WLine* l)
{
	if (l == NULL)
	{
		printf("Tried to render a null line!\n");
		return;
	}

	//if (!color_bypass)
	//{
	if (l->has_stroke)
	{
		//WColor16 c = l->stroke;
		//drw_color(c.r, c.g, c.b, c.a * alpha_mult);
		/// dirty hack to have color and also transparent onion
		/// skins oops
		//r_alpha(c.a * alpha_mult);
	}
	if (l->closed)
	{
		//drw_set_fill(l->closed);
		drw_poly(l);
		//drw_fill_pop();
	}
	if (l->has_stroke)
	{
		//r_alpha_pop();
	}
//}
//else
//{
//}
#ifdef DISABLE_UNTIL_WORKLINE_REFACTOR_COMPLETE

	if (l->brush)
	{
		if (l->tess)
		{
			drw_gpc_tristrip(l->tess);
			return;
		}

		if (l->brush->stroke)
		{
			if (l->brush->stroke->tess)
			{
				drw_gpc_tristrip(l->brush->stroke->tess);
			}
			else
			{

				drw_triangle_strip(l->brush->stroke);
			}
		}
		// else{

		//  drw_poly(l->brush->stroke);
		//}
	}
	else
	{

		if (l->tess)
		{
			drw_gpc_tristrip(l->tess);
		}
		else
		{
			drw_poly(l);
		}
	}
#else
	//drw_color(0,0,0,1);
	drw_poly(l);
#endif
	//}
	//  TODO color pop?
}

void drw_poly(WLine* line)
{
	int			 i, j;
	const unsigned long long renderLineSize = (line->num * 2);

	GLfloat* arr = malloc(sizeof(GLfloat) * renderLineSize);

	for (i = 0, j = 0; i < line->num; i++, j += 2)
	{
		WPoint* p = &line->data[i];
		//  todo: REMOVE THIS HACK

		arr[j]     = p->x;
		arr[j + 1] = p->y;
	}

	glVertexPointer(2, GL_FLOAT, 0, arr);

	if (line->closed)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, (int)line->num);
		free(arr);
		return;
	}

	fill ? glDrawArrays(GL_TRIANGLE_FAN, 0, (int)line->num)
	     : glDrawArrays(GL_LINE_STRIP, 0, (int)line->num);
	free(arr);
}
