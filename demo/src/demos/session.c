//
//  session.c
//  wash-demo
//
//  Created by vs on 3/31/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef session_c
#define session_c

#include "../demo.h"
#include "../wsh_demo_common.h"
#include <wsh/wsh.h>

#define DEMO_NAME "session"
#define DEMO_NICENAME "Recording Session"

static void switch_tool(WshToolRec* rec);

const char* path = "wash_session.wshs";

static WshToolRec* pencil  = NULL;
static WshToolRec* brush   = NULL;
static WshToolRec* eraser  = NULL;
static WshToolRec* current = NULL;

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
	switch (key)
	{
	case GLFW_KEY_Q:
		switch_tool(pencil);
		break;
	case GLFW_KEY_W:
		switch_tool(brush);
		break;
	case GLFW_KEY_E:
		switch_tool(eraser);
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

static void switch_tool(WshToolRec* rec)
{
	wsh_session_rec_tool_change(rec, glfwGetTime());
	current = rec;
}

static void setup_tools(void)
{
	pencil		   = wsh_tool_rec_create();
	pencil->identifier = "space.ruminant.wsh.demo_pencil";
	pencil->name       = "My awesome pencil";

	brush		  = wsh_tool_rec_create();
	brush->identifier = "space.ruminant.wsh.demo_brush";
	brush->name       = "My awesome brush";

	eraser		   = wsh_tool_rec_create();
	eraser->identifier = "space.ruminant.wsh.demo_eraser";
	eraser->name       = "My awesome brush";

	wsh_session_rec_tool_register(pencil);
	wsh_session_rec_tool_register(brush);
	wsh_session_rec_tool_register(eraser);
}

static void init(void)
{
	int err = 0;
	printf("%s init!\n", DEMO_NICENAME);
	err = wsh_session_set_path(".");
	if (!err)
	{
		printf("Error setting path!\n");
	}
	err = wsh_session_init();
	if (!err)
	{
		printf("Something went wrong!\n");
	}

	setup_tools();

	wsh_session_start(glfwGetTime());
}

static void deinit(void)
{
	printf("%s deinit!\n", DEMO_NICENAME);
	wsh_session_stop(glfwGetTime());
	wsh_session_deinit();

	wsh_session_print_debug_info();
}

static void update(void)
{
}

static void draw_cursor(void)
{
	drw_push();
	d_translate(mouse_x, mouse_y, 0);
	drw_line(0, 0, 33, -33);
	d_pop();
}

static void draw(void)
{
	draw_cursor();
}

static void drop(int num, const char** paths)
{
}

WashDemo session =
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

#endif

//	demonsstration of using the wash session recording functionality
