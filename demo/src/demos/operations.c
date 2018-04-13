//
//  operations.c
//  wash-demo
//
//  Created by vs on 4/5/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef operations_c
#define operations_c

#include "../demo.h"
#include "../wash_demo_common.h"

#define DEMO_NAME "operations"
#define DEMO_NICENAME "Line Ops"

WObject* subject = NULL;

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

static void wipe_canvas_and_scale(void)
{
	WObject* art = recorder_get_art();
	if ( subject )
	{
		w_object_destroy(subject);
	}
	subject = w_object_copy(art);
	recorder_clear();
	
	scale_object_to_window(subject);
}

static void mouse_button(int button, int action, int mods)
{
	if( button > 0 )
		return;
	if ( action )
	{
		printf("mdown\n");
		
	}else{
		printf("mup!\n");
		wipe_canvas_and_scale();
	}
}

static void init(void)
{
	printf("%s init!\n", DEMO_NICENAME);
}

static void deinit(void)
{
	printf("%s deinit!\n", DEMO_NICENAME);
}

static void update(void)
{
}

static void draw(void)
{
	static double d = 1;
	
	d = d * .999;
	if ( d == 0 )
		d = 1;
	//double v = d * 128;
	printf("%f\n", d);
	d_color(0,.25,0,1);
	if (!subject)
		return;
	
	WLine* first = subject->lines[0];
	if ( !first )
		return;
	
	d_wline(first);
	d_verts(first);
	d_push();
	//WLine* mod = w_line_copy(first);
	
	WLine* mod = w_line_ops_douglaspeucker(first, d);
	
	d_color(.5,0,0,1);
	d_translate(0,32,0);
	d_verts(mod);
	d_wline(mod);
	w_line_destroy(mod);
	d_pop();
	
	//d_wobject(subject);
}

static void drop(int num, const char** paths)
{
	
}

WashDemo operations =
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
