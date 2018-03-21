//
//  main.cpp
//  wash
//
//  Created by Andrew Macfarlane on 8/15/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//


#include <GLFW/glfw3.h>

#include "demos/procedural_brush.h"
#include "demos/dynamic_resize.h"
#include "demos/realtime_playback.h"
#include "demos/cel_animation.h"

#include "primitives.h"

#include <wsh/wsh.h>

GLFWwindow* window = NULL;
WDocumentHnd document;

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 256

#define NUM_DEMOS 4
WashDemo* demos[NUM_DEMOS] = {&cel_animation, &procedural_brush, &dynamic_resize, &realtime_playback };
WashDemo* current_demo = NULL;

static void joystick_callback(int joy, int event)
{
	
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	
	
	
}

static void window_pos_callback(GLFWwindow* window, int x, int y)
{
	
	
}

static void window_size_callback(GLFWwindow* window, int width, int height)
{
	
	
	
}

// static void draw_joysticks(void);

static void scroll_callback(GLFWwindow* window, double x, double y)
{
	
	
}

static void mouse_button_callback(GLFWwindow* window, int button, int action,
				  int mods)
{
	
	
}

static void cursor_enter_callback(GLFWwindow* window, int entered)
{
	
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	
}

static void key_callback(GLFWwindow* window, int key, int scan, int action, int mods)
{
	
	
	
	
}

static void drop_callback(GLFWwindow* window, int num, const char** paths)
{
	
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
	glClear(GL_COLOR_BUFFER_BIT);
	
	d_square(.5);
	d_square(128);
	if ( document.src )
	{
		WSequence* seq = document.src->sequence.src;
		WObject* first = seq->frames[0];
		d_wobject_verts(first);
		d_wobject_e(first);
	}
}

int main(int argc, const char* argv[])
{
	
	
	
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	setup_callbacks();
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	d_init();
	d_setup_projection(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	document.src = w_serial_json_unserialize_document("data/wash/test-square-anim-2018_3_16-23_17_24.wash");
	
	if ( document.src )
		w_sequence_normalize(document.src->sequence.src);
	
	d_color(1,1,1,.5);
	
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
	return 0;
	
	
}

