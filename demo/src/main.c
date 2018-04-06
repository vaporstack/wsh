//
//  main.cpp
//  wash
//
//  Created by Andrew Macfarlane on 8/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "wash_demo_common.h"

#include "demo.h"

extern WashDemo animation;
extern WashDemo resize;
extern WashDemo brush;
extern WashDemo playback;
extern WashDemo operations;
extern WashDemo simulator;
//#include "demos/animation.c"
//#include "demos/resize.h"
//#include "demos/brush.h"
//#include "demos/playback.h"
//#include "demos/operations.h"

#include "primitives.h"
#include "recorder.h"
#include "simulator.h"

#include <wsh/wsh.h>

#include "wcm.h"

#define WIDTH 256
#define HEIGHT 256


static void switch_demo(int i);
static int current_demo_index = 0;

static int window_w = WIDTH;
static int window_h = HEIGHT;

static double mouse_x = 0;
static double mouse_y = 0;

static double dpi	    = 1;
static double display_radius = 1;
static bool   down	   = false;
static bool faking_it = false;
GLFWwindow* window = NULL;

WDocumentHnd document;

#define NUM_DEMOS 6
WashDemo* demos[NUM_DEMOS] = {&animation, &operations, &animation, &brush, &resize, &playback};
WashDemo* current_demo     = NULL;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	window_h = height;
	window_w = width;

	d_setup(window_w, window_h);
}

static void window_pos_callback(GLFWwindow* window, int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{

	window_h = height;
	window_w = width;

	d_setup(window_w, window_h);
}

// static void draw_joysticks(void);

static void scroll_callback(GLFWwindow* window, double x, double y)
{
}

static void start_faking_it(void)
{
	printf("Starting to fake it.\n");
	faking_it = true;
}

static void stop_faking_it(double x, double y)
{
	recorder_end_line(x, y);

	faking_it = false;
	printf("No longer faking it.\n");
}

static void normalize_coordinates(double* x, double* y)
{
	*x *= dpi;
	*y *= dpi;
	
	//*y *= -1;
	//	wacoms upside down? wooo
	//mouse_y = window_h - mouse_y;
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	down = action;
	if (button > 0)
		return;

	static int once = 0;
	if (once == 0)
	{
		once = 1;
		wcm_init(window_w, window_h);
	}
	
	if ( action == 1 )
	{
		if( !faking_it )
		{
			if ( !wash_demo_has_pressure_sensitivity_of_any_kind)
			{
				start_faking_it();
			};
		}
	}else{
		if ( faking_it )
		{
			stop_faking_it(mouse_x, mouse_y);
		}
	}
}

static void cursor_enter_callback(GLFWwindow* window, int entered)
{
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouse_x = xpos;
	mouse_y = ypos;
	
	normalize_coordinates(&mouse_x, &mouse_y);
	
	if ( faking_it ) {
		WPoint p = simulator_simulate_point(mouse_x, mouse_y);
		recorder_record_manual_point(p);
	}
	
}

static void key_callback(GLFWwindow* window, int key, int scan, int action, int mods)
{
	if ( action == 0 )
	{
		return;
	}
	
	if ( key >= GLFW_KEY_1 && key < GLFW_KEY_9 )
	{
		int v = key - GLFW_KEY_1;
		if ( v != current_demo_index )
		{
			switch_demo(v);
			return;
		}
		
	}
	
	if ( current_demo )
	{
		current_demo->key(key, action, mods);
	}
}

static void drop_callback(GLFWwindow* window, int num, const char** paths)
{
}

void my_tablet_prox(int v)
{
	printf("got tablet prox? %d\n", v);
}

void my_tablet_up(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	
	mouse_x = x;
	mouse_y = y;
	
	normalize_coordinates(&mouse_x, &mouse_y);
	
	printf("got rich up? %f %f %f %f %f %f\n", mouse_x, mouse_y, p, r, tx, ty);
	recorder_end_line(mouse_x, mouse_y);
}

static void have_pressure(void)
{
	
	wash_demo_has_pressure_sensitivity_of_any_kind = true;
	printf("Have pressure! Should probably tell the user that we're disabling the mouse...\n");
	
}


void my_tablet_down(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	if( !wash_demo_has_pressure_sensitivity_of_any_kind)
	{
		have_pressure();
	}
	
	mouse_x = x;
	mouse_y = y;
	normalize_coordinates(&mouse_x, &mouse_y);
	
	printf("got rich down? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
	recorder_record_point(mouse_x, mouse_y, button, p, r, tx, ty, altitude, azimuth, idk);
}

void my_tablet_motion(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	mouse_x = x;
	mouse_y = y;
	normalize_coordinates(&mouse_x, &mouse_y);
	
	printf("got rich motion? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
	
}

void my_tablet_drag(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	printf("got rich drag? %f %f %f %f %f %f\n", mouse_x, mouse_y, p, r, tx, ty);

	mouse_x = x;
	mouse_y = y;
	normalize_coordinates(&mouse_x, &mouse_y);
	
	
	recorder_record_point(mouse_x, mouse_y, button, p, r, tx, ty, altitude, azimuth, idk);

}

static void setup_callbacks()
{
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetWindowPosCallback(window, window_pos_callback);

	glfwSetWindowSizeCallback(window, window_size_callback);



	glfwSetScrollCallback(window, scroll_callback);
	glfwSetDropCallback(window, drop_callback);
}

static void update(void)
{
	if ( current_demo )
	{
		current_demo->update();
	}
	
}

static void draw(void)
{
	d_clear();
	
	
	if ( test_geometry.src )
	{
		d_wobject(test_geometry.src);
	}
	if ( work_line.src )
	{
		d_wline(work_line.src);
	}
	
	
	if ( current_demo )
	{
		current_demo->draw();
	}
	
	d_line(0, 0, mouse_x, mouse_y);
	d_push();

	d_translate(mouse_x, mouse_y, 0);

	d_line(0, 0, 32, 32);
	if (down)
	{
		d_color(0, 0, 0, 1);
	}
	else
	{
		d_color(0, 0, 0, .33333);
	}
	d_circle(display_radius);
	d_pop();
}


static void switch_demo(int i)
{
	printf("Switching demo: %d\n", i );
	
	if ( current_demo )
	{
		current_demo->deinit();
	}
	
	
	current_demo_index = i;
	if ( current_demo_index >= NUM_DEMOS )
	{
		printf("Asked for a demo beyond our range.\n");
		return;
		
	}
	current_demo = demos[current_demo_index];
	
	if ( !current_demo )
	{
		printf("Error, got a NULL demo at position %d\n", i);
		return;
	}
	
	current_demo->init();
}

int main(int argc, const char* argv[])
{

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(window_w, window_h, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	setup_callbacks();

	wcm_set_tablet_proximity_func(my_tablet_prox);
	wcm_set_tablet_up_func(my_tablet_up);
	wcm_set_tablet_down_func(my_tablet_down);
	wcm_set_tablet_motion_func(my_tablet_motion);
	wcm_set_tablet_drag_func(my_tablet_drag);

	wcm_init(window_w, window_h);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	int ww, wh;
	glfwGetWindowSize(window, &ww, &wh);
	int fw, fh;
	glfwGetFramebufferSize(window, &fw, &fh);

	dpi = (double)fw / ww;
	
	recorder_init();
	
	d_set_dpiscale(dpi);
	printf("dpi: %f\n", dpi);

	document.src = w_serial_json_unserialize_document("data/wash/test-square-anim-2018_3_16-23_17_24.wash");
	d_setup(window_w, window_h);

	d_color_clear(1, 1, 1, 1);
	d_color(0, 0, 0, 1);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		update();
		/* Render here */
		draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	wcm_deinit();
	recorder_deinit();
	
	
	return 0;
}
