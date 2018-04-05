//
//  animation.c
//  wash-demo
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef animation_c
#define animation_c

#include "../demo.h"

#define DEMO_NAME "animation"
#define DEMO_NICENAME "Cel Animation"

static void key(int action, int key)
{
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
}

WashDemo animation =
    {
	DEMO_NICENAME,
	1.0 / 60.0,
	init,
	deinit,
	update,
	draw,
	key};

#endif
