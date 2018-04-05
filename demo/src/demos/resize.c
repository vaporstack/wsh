//
//  demo.c
//  wash-demo
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef resize_c
#define resize_c

#include "../demo.h"

static void key(int action, int key)
{
}

static void init(void)
{
	printf("Realtime playback init!\n");
}

static void deinit(void)
{
	printf("Realtime playback deinit!\n");
}

static void update(void)
{
}

static void draw(void)
{
}

WashDemo resize =
    {
	"Dynamic Resize",
	1.0 / 60.0,
	init,
	deinit,
	update,
	draw,
	key};

#endif
