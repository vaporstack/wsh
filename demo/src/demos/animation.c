//
//  animation.c
//  wash-demo
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef animation_c
#define animation_c

#include "../demo.h"
#include "../primitives.h"

#include <wsh/wsh.h>

#define DEMO_NAME "animation"
#define DEMO_NICENAME "Cel Animation"

static WDocumentHnd document;

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

static void key(int action, int key, int mods)
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
	if ( !document.src)
	{
		document.src = w_serial_document_unserialize("data/wash/squares-anim.wash");
		if ( !document.src )
		{
			printf("Load failed!\n");
			return;
		}
	}
	printf("%s init!\n", DEMO_NICENAME);
	//w_sequence_normalize(document.src->sequence.src);
	WSequence* seq = document.src->sequence.src;
	w_sequence_calc_bounds(seq);
	
}

static void deinit(void)
{
	printf("%s deinit!\n", DEMO_NICENAME);
	if(document.src)
	{
		w_document_destroy(document.src);
		
	}
	
}

static void update(void)
{
}

static void draw(void)
{
	if ( !document.src )
		return;
	
	static double t = 0;
	t += .05;
	
	WSequence* seq = document.src->sequence.src;
	int num = seq->num_frames;
	
	double tmp = fmod(t, 1);
	int which = tmp * num;
	//printf("Which: %d\n", which);
	WRect bounds = seq->bounds;
	WRect bnd = bounds;

	d_color(1,0,0,1);
	d_rect(bnd.pos.x, bnd.pos.y, bnd.pos.x + bnd.size.x, bnd.pos.y + bnd.size.y);
	
	WObject* frame = seq->frames[which];
	
	if ( !frame )
		return;
	
	d_wobject(frame);
	
}

WashDemo animation =
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
	tablet_drag};

#endif
