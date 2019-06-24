//
//  mapping.c
//  wash-demo
//
//  Created by vs on 5/14/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "../demo.h"
#include "../wsh_demo_common.h"

#define DEMO_NAME "mapping"
#define DEMO_NICENAME "Stroke Mapping"

static WObject* source = NULL;
static WLine*   line   = NULL;

static void choose_random_line(void);

static void tablet_prox(int v)
{
	printf("got tablet prox? %d\n", v);
}

static void tablet_up(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	printf("got rich up? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

static void tablet_down(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	printf("got rich down? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

static void tablet_drag(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	printf("got rich drag? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

static void tablet_motion(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	printf("got rich motion? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

static void key(int key, int action, int mods)
{
}

static void mouse_move(double x, double y)
{
}

static void mouse_button(int button, int action, int mods)
{
	if (button > 0 || action == 1)
		return;

	//WLine* random = NULL;
	if (!source)
	{
		printf("No source, can't pick random line!\n");
		return;
	}
	choose_random_line();
}

static void choose_random_line(void)
{
	unsigned long num = source->num;
	double	v   = (double)rand() / RAND_MAX;

	unsigned which = v * num;

	//printf("drawing line %lu\n", which);
	line = source->lines[which];

	//WObject* tmp  = source;
}

static void init(void)
{
	//WDocumentHnd document;
	wsh_demo_load_document("data/wash/hatching.wash");

	//document.src = wsh_serial_document_unserialize_file("data/wash/hatching.wash");
	//if (!document.src)
	//{
	//	printf("Load failed!\n");
	//	return;
	//}

	source = wsh_sequence_ops_collapse(document.src->sequence.src);

	//wsh_document_destroy(document.src);
	printf("%s init!\n", DEMO_NICENAME);
	//WObject* tmp = source;

	//scale_sequence_to_window(source);

	//wsh_sequence_normalize(document.src->sequence.src);
	//WSequence* seq = document.src->sequence.src;
}

static void deinit(void)
{
	if (source)
	{
		wsh_object_destroy(source);
		source = NULL;
	}
}

static void drop(int num, const char** paths)
{
}

static void update(void)
{
}

static void draw(void)
{

	double cx = window_w * .5 * dpi;
	double cy = window_h * .5 * dpi;

	drw_line(mouse_x, mouse_y, cx, cy);

	drw_push();
	drw_translate(0, 32, 0);

	drw_pop();

	//unsigned long which = rand
	//if (!document.src)
	//	return;

	if (line)
	{

		WPoint first = line->data[0];
		WPoint last  = line->data[line->num - 1];

		WLine* cpy = NULL;
		//if ( last.x <first.x || last.y < first.y )
		//{
		//	cpy = wsh_line_reverse(line);
		//}else{
		cpy = wsh_line_copy(line);

		//}
		WLine* refcpy = wsh_line_copy(line);
		if (!cpy)
		{
			free(cpy);
		}

		if (!refcpy)
		{
			free(refcpy);
			return;
		}

		//wsh_line_translate(cpy)
		//printf("ang: %f\n", ang);

		//WPoint last = cpy->data[cpy->num-1];

		//wsh_line_translate(cpy, last.x, last.y);

		//	move the line to 0, 0, for ease of operations
		wsh_line_translate(cpy, -first.x, -first.y);
		wsh_line_translate(refcpy, -first.x, -first.y);

		double ang = wsh_line_ops_angle(cpy);

		//printf("%f\n", ang);
		//double ang_r = radians
		wsh_line_rotate(cpy, 0, 0, -ang);

		//	printf("cpy first: %f %f\n", cpy->data[0].x, cpy->data[0].y);
		//wsh_line_translate(cpy, first.x, first.y);
		drw_push();

		drw_translate(cx, cy, 0);
		drw_line(0, 0, cos(ang) * 512, sin(ang) * 512);

		//drw_wline(line);
		drw_color(1, 0, 0, 1);
		drw_wline(refcpy);
		drw_verts(refcpy);

		double dx = mouse_x - cx;
		double dy = mouse_y - cy;
		double r  = wsh_angle_from_points(mouse_x, mouse_y, cx, cy);

		drw_color(0, 1, 0, 1);
		drw_wline(cpy);
		drw_verts(cpy);
		drw_pop();

		WLine* out = wsh_line_normalize(cpy, 0, 0);
		wsh_line_scale(out, dx, dy);
		wsh_line_rotate(out, cx, cy, -r);

		drw_color(0, 0, 0, 1);

		drw_wline(out);
		drw_verts(out);

		wsh_line_destroy(cpy);
		wsh_line_destroy(refcpy);
		wsh_line_destroy(out);
	}

	static double t = 0;
	t += .05;

	//	do stuff
}

WshDemo mapping =
    {
	DEMO_NICENAME,
	1.0 / 60.0,
	init,
	deinit,
	update,
	draw,
	key,
	mouse_move,
	mouse_button,
	tablet_up,
	tablet_down,
	tablet_motion,
	tablet_drag,
	drop};
