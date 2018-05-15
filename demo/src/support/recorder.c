//
//  recorder.c
//  wash-demo
//
//  Created by vs on 4/5/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "recorder.h"

#include "../wsh_demo_common.h"

#include <stdbool.h>

WLine* sanity_check(void)
{

	WLine* src = work_line.src;
	if (!src)
	{
		return NULL;
	}
	return src;
}

void recorder_init(void)
{
	work_line.src     = wsh_line_create();
	test_geometry.src = wsh_object_create(NULL);
	/*
	WLine* src = wsh_line_create();
	work_line = wsh_line_hnd_create_with_addr(src);
	test_geometry = wsh_object_hnd_create(NULL);
	test_geometry->src = wsh_object_create(NULL);
	*/
}

void recorder_deinit(void)
{
	wsh_line_destroy(work_line.src);
}

void recorder_record_manual_point(WPoint p)
{

	WLine* src = sanity_check();
	if (!src)
	{
		printf("Error\n");
		return;
	}

	wsh_line_add_point(src, p);
}

void recorder_record_point(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{

	WLine* src = sanity_check();
	if (!src)
		return;

	WPoint* point   = wsh_point_create();
	point->x	= x;
	point->y	= y;
	point->pressure = p;
	point->tilt_x   = tx;
	point->tilt_y   = ty;

	printf(".");
	wsh_line_add_point(src, *point);
}

void recorder_endrw_line(double x, double y)
{
	WLine* src = sanity_check();
	if (!src)
		return;

	if (src->num < 1)
	{
		printf("Error, had a line with 0 points!\n");
		return;
	}

	WObject* dst = test_geometry.src;

	if (!dst)
		return;

	wsh_object_addrw_line(dst, wsh_line_copy(src));
	printf("Recorded line with %llu points\n", src->num);

	wsh_line_destroy(src);
	work_line.src = NULL;

	work_line.src = wsh_line_create();
}
WObject* recorder_get_art(void)
{
	return test_geometry.src;
}

void recorder_clear(void)
{

	//if ( ! test_geometry )
	//	return;

	if (!test_geometry.src)
		return;

	wsh_object_destroy(test_geometry.src);

	test_geometry.src = wsh_object_create(NULL);
}
