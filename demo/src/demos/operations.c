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

#define DEMO_NAME "operations"
#define DEMO_NICENAME "Line Ops"

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

WashDemo operations =
    {
	DEMO_NICENAME,
	1.0 / 60.0,
	init,
	deinit,
	update,
	draw,
	key};

#endif
