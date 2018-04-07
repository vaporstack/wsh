//
//  text_ftgl.c
//  wash-demo
//
//  Created by vs on 4/7/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "text_ftgl.h"

#include <stdio.h>
#include <stdbool.h>

#include <GLFW/glfw3.h>

#include <FTGL/ftgl.h>

FTGLfont *font = NULL;
static bool initted = false;


void text_ftgl_deinit(void)
{
	ftglDestroyFont(font);

}
static int init(void)
{
	/* Create a pixmap font from a TrueType file. */
	font = ftglCreateTextureFont("data/ttf/ruminant-2.ttf");
	
	/* If something went wrong, bail out. */
	if(!font)
		return -1;
	
	/* Set the font size and render a small text. */
	ftglSetFontFaceSize(font, 72, 72);
	
	/* Destroy the font object. */
	return 0;
}
void text_ftgl_draw_text(const char* text, double x, double y)
{
	if ( !initted)
	{
		int res = init();
		if ( res == -1 )
		{
			printf("Failed, bail!\n");
			return;
		}
	}
	if ( !font )
	{
		printf("No font, bail!\n");
		return;
	}
	
	ftglRenderFont(font, text, FTGL_RENDER_ALL);


	
}
