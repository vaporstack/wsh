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
}

static void init(void)
{
	WDocumentHnd document;

	document.src = wsh_serial_document_unserialize("data/wash/hatching.wash");
	if (!document.src)
	{
		printf("Load failed!\n");
		return;
	}

	source = wsh_sequence_ops_collapse(document.src->sequence.src);

	wsh_document_destroy(document.src);
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
	//WLine* random = NULL;

	unsigned long num = source->num_lines;
	double	v   = (double)rand() / RAND_MAX;

	unsigned which = v * num;

	//printf("drawing line %lu\n", which);
	WLine*   line = source->lines[which];
	WObject* tmp  = source;
	d_wline(line);

	//unsigned long which = rand
	//if (!document.src)
	//	return;

	static double t = 0;
	t += .05;

	//	do stuff
}

WashDemo mapping =
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
