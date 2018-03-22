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

void d_color_clear(double r, double g, double b, double a)
{
	glClearColor(r, g, b, a);
}

void d_line(double ax, double ay, double bx, double by)
{
	glBegin(GL_LINES);
	glVertex2f(ax, ay);
	glVertex2f(bx, by);
	glEnd();
}

void d_set_dpiscale(double v)
{
	printf("setting dpi to %f\n", v);
	dpi = v;
}

void d_setup_view_ortho(int w, int h)
{

	glViewport(0, 0, (int)w * dpi, (int)h * dpi);

	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double l = w * -.5;
	double r = w * .5;
	double t = h * -.5;
	double b = h * .5;
	double n = -w;
	double f = w;
	glOrtho(0, w * dpi, h * dpi, 0, n, f);
}

void d_setup(int width, int height)
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

	d_setup_view_ortho(width, height);
}

void d_push()
{
	glPushMatrix();
}

void d_pop()
{
	glPopMatrix();
}

void d_clear(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void d_translate(double x, double y, double z)
{
	glTranslatef(x, y, z);
}

void d_color(double r, double g, double b, double a)
{

	glColor4d(r, g, b, a);
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

void d_verts(WLine* l)
{
	int i;
	for (i = 0; i < l->num; ++i)
	{
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
	for (i = 0; i < obj->num_lines; i++)
	{
		WLine* line = obj->lines[i];
		if (!line)
		{
			printf("Error, bogus line!\n");
			continue;
		}
		d_verts(line);
	}
}


void d_circle(float r)
{
	d_ellipse(r, r);
	/*
	 float* circle = circle_defs[CIRCLE_PRECISION];
	 if (circle == NULL) {
	 printf("calculating circle for %i\n", CIRCLE_PRECISION);
	 calculate_circle(CIRCLE_PRECISION);
	 }
	 circle = circle_defs[CIRCLE_PRECISION];
	 glVertexPointer(2, GL_FLOAT, 0, circle);
	 
	 // cout << "c:" << circleArray[2] << endl;
	 d_scale_u(r);
	 fill ? glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_PRECISION)
	 : glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_PRECISION);
	 
	 //r_ellipse(r, r);
	 */
}

void d_ellipse(float _x, float _y)
{
	/*if ( _x == _y )
	 {
	 d_circle(_x);
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
	for (i = 0; i < renderLineSize; i += 2) {
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
