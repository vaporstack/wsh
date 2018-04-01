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

#include "demos/cel_animation.h"
#include "demos/dynamic_resize.h"
#include "demos/procedural_brush.h"
#include "demos/realtime_playback.h"

#include "primitives.h"
#include <wsh/wsh.h>

#include "wcm.h"

#define WIDTH 256
#define HEIGHT 256

static int window_w = WIDTH;
static int window_h = HEIGHT;

static double mouse_x = 0;
static double mouse_y = 0;

static double dpi	    = 1;
static double display_radius = 1;
static bool   down	   = false;

GLFWwindow* window = NULL;

WDocumentHnd document;

#define NUM_DEMOS 4
WashDemo* demos[NUM_DEMOS] = {&cel_animation, &procedural_brush, &dynamic_resize, &realtime_playback};
WashDemo* current_demo     = NULL;

static void joystick_callback(int joy, int event)
{
}

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

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	down		= action;
	if (button > 0)
		return;
	
	static int once = 0;
	if (once == 0)
	{
		once = 1;
		wcm_init(window_w, window_h);
	}

}

static void cursor_enter_callback(GLFWwindow* window, int entered)
{
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mouse_x = xpos * dpi;
	mouse_y = ypos * dpi;
}

static void key_callback(GLFWwindow* window, int key, int scan, int action, int mods)
{
}

static void drop_callback(GLFWwindow* window, int num, const char** paths)
{
}

void my_tablet_prox(int v)
{
	printf("got tablet prox? %d\n", v);
}

void my_tablet_motion(double x, double y, double p, double r, double tx, double ty, double altitude, double azimuth)
{
	printf("got rich motion? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

void my_tablet_drag(double x, double y, double p, double r, double tx, double ty, double altitude, double azimuth)
{
	printf("got rich drag? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

void my_tablet_up(double x, double y, double p, double r, double tx, double ty, double altitude, double azimuth)
{
	printf("got rich up? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

void my_tablet_down(double x, double y, double p, double r, double tx, double ty, double altitude, double azimuth)
{
	printf("got rich down? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
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

	//#ifndef R4_COMPAT_OPENFRAMEWORKS
	glfwSetJoystickCallback(joystick_callback);
	//#endif

	glfwSetScrollCallback(window, scroll_callback);
	glfwSetDropCallback(window, drop_callback);
}

static void draw(void)
{
	d_clear();
	
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

	d_set_dpiscale(dpi);
	printf("dpi: %f\n", dpi);

	document.src = w_serial_json_unserialize_document("data/wash/test-square-anim-2018_3_16-23_17_24.wash");
	d_setup(window_w, window_h);
	demos_init();
	d_color_clear(1, 1, 1, 1);
	d_color(0, 0, 0, 1);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	wcm_deinit();
	demos_deinit();
	return 0;
}
