//
//  playback.c
//  wash-demo
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef playback_c
#define playback_c

#include "../demo.h"
#include <wsh/wsh.h>
#include "../primitives.h"

#define DEMO_NAME "playback"
#define DEMO_NICENAME "Playback"

static WDocumentHnd document;

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
	printf("Realtime playback init!\n");
	if ( !document.src)
	{
		document.src = w_serial_document_unserialize("data/wash/crab.wash");
		if ( !document.src )
		{
			printf("Load failed!\n");
			return;
		}
	}
	printf("%s init!\n", DEMO_NICENAME);
	//w_sequence_normalize(document.src->sequence.src);
}

static void deinit(void)
{
	printf("Realtime playback deinit!\n");
}

static void update(void)
{
}

static void draw(void)
{
	if ( !document.src)
		return;
	
	WSequence* seq = document.src->sequence.src;
	
	if ( !seq )
		return;
	
	WObject* frame = seq->frames[4];
	
	if ( frame)
	{
		d_wobject(frame);
	}
}

WashDemo playback =
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
