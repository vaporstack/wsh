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

static int fill;

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
