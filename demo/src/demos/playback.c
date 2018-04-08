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
#include "../wash_demo_common.h"

#define DEMO_NAME "playback"
#define DEMO_NICENAME "Playback"

static int current_frame;
WObject*   timeslice = NULL;

static WDocumentHnd document;
static double       playhead = 0.;
static double       start    = 0.;

static void draw_points_until_given_time(WObject* obj, double t);
static void reset_playback(void);

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

static void switch_art(int v)
{
	current_frame += v;
	int num = document.src->sequence.src->num_frames;
	if (current_frame >= num)
	{
		current_frame = 0;
	}
	if (current_frame < 0)
	{
		current_frame = num - 1;
	}

	reset_playback();
}

static void key(int key, int action, int mods)
{

	switch (key)
	{
	case GLFW_KEY_LEFT:

		switch_art(-1);
		break;
	case GLFW_KEY_RIGHT:

		switch_art(1);
		break;
	case GLFW_KEY_UP:

		switch_art(-1);
		break;
	case GLFW_KEY_DOWN:

		switch_art(1);
		break;
	default:
		break;
	}
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
	if (!document.src)
	{
		document.src = w_serial_document_unserialize("data/wash/crab.wash");
		if (!document.src)
		{
			printf("Load failed!\n");
			return;
		}
	}
	printf("%s init!\n", DEMO_NICENAME);
	//w_object_normalize_time_exploded(document.src);

	scale_sequence_to_window(document.src->sequence.src);
}

static void deinit(void)
{
	printf("Realtime playback deinit!\n");
	w_document_destroy(document.src);

	document.src = NULL;
}

static void update(void)
{
	playhead = glfwGetTime();
}

static void reset_playback(void)
{
	start = glfwGetTime();
}

static void draw_points_until_given_time(WObject* obj, double t)
{
	//being a bit dirty here, doing logic in a drawing function,
	// maybe better than doing all this iteration twice/
	bool all_complete = true;

	//printf("Drawing lines that happen until %f\n", t);
	int num = obj->num_lines;

	for (unsigned long i = 0; i < num; i++)
	{
		WLine* src = obj->lines[i];
		WLine* dst = w_line_create();

		for (unsigned long long j = 0; j < src->num; j++)
		{
			WPoint p = src->data[j];
			if (p.time < t)
			{
				w_line_add_point(dst, p);
			}
		}

		if (src->num != dst->num)
			all_complete = false;
		d_wline(dst);
		w_line_destroy(dst);
	}
	if (all_complete)
	{
		reset_playback();
	}
}

static void draw(void)
{
	if (!document.src)
		return;

	WSequence* seq = document.src->sequence.src;

	if (!seq)
		return;

	WObject* frame = seq->frames[current_frame];
	if (!frame)
	{
		printf("Error, no frame at asked for position.\n");
		return;
	}

	timeslice = w_object_copy(frame);

	w_object_normalize_time_exploded(timeslice);

	draw_points_until_given_time(timeslice, playhead - start);
	
	wash_demo_text("space - toggle modes", frame_w * .125, frame_h * (1-.125));
	wash_demo_text("left/right - switch art", frame_w * .125, frame_h * (1-.125*2));
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
