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
#include "../wash_demo_common.h"
#include <wsh/wsh.h>

const char* path = "wash_session.wshs";

#define DEMO_NAME "session"
#define DEMO_NICENAME "Recording Session"

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

static void setup_tools(void)
{
	WshToolRec* pencil = wsh_tool_rec_create();
	pencil->identifier = "space.ruminant.wsh.demo_pencil";
	pencil->name = "My awesome pencil";
	
	
	w_session_rec_tool_register(pencil);
	w_session_rec_tool_register(pencil);
	w_session_rec_tool_register(pencil);


}

static void init(void)
{
	int err = 0;
	printf("%s init!\n", DEMO_NICENAME);
	err = w_session_set_path(".");
	if ( !err )
	{
		printf("Error setting path!\n");
	}
	err = w_session_init();
	if ( !err )
	{
		printf("Something went wrong!\n");
		
	}
	
	setup_tools();
	
	
	
	w_session_start(glfwGetTime());
	
}

static void deinit(void)
{
	printf("%s deinit!\n", DEMO_NICENAME);
	w_session_stop(glfwGetTime());
	w_session_deinit();
	
	w_session_print_debug_info();
	
}

static void update(void)
{
}

static void draw(void)
{
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
	drop
};

#endif


//	demonsstration of using the wash session recording functionality



