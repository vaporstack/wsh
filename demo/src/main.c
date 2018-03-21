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
GLFWwindow* window = NULL;
#include <wsh/wsh.h>

#include "input/input_tablet.h"

WDocumentHnd document;

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
	
	if ( document.src )
	{
		
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
	b_tablet_init();
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	document.src = w_serial_json_unserialize_document("data/wash/test-square-anim-2018_3_16-23_17_24.wash");
	
	
	
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
	b_tablet_deinit();
	
	return 0;
	
	
}

