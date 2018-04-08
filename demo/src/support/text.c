
//  text.c
//  text
//
//  Created by Andrew Macfarlane on 04/07/18.
//  Copyright © 2018 vaporstack. All rights reserved.

#include "text.h"


#include "text_ftgl.h"

void wash_demo_text(const char* text, double x, double y)
{
	text_ftgl_draw_text(text, x, y);
}

