//
//  input_tablet.c
//  wash-demo
//
//  Created by vs on 3/21/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "input_tablet.h"

#include <stdbool.h>

#include <stdio.h>

#ifdef __APPLE__
	#include "../contrib/macos/r_input_tablet_cocoa.h"
#else
	#define EASYTAB_IMPLEMENTATION
	#include "../contrib/other/easytab.h"
#endif


int b_tablet_init(void)
{
	
#ifdef __APPLE__
	r_input_tablet_cocoa_init();
	//dumb, but cocoa will certainly tell us if this errors
	return 0;
#else
	return r_input_tablet_ez_init();
#endif
	return -1;
}

void b_tablet_deinit(void)
{
	
}

void b_receive_tablet_proximity(bool v)
{
}


void b_receive_tablet_down(double x, double y)
{

}

void b_receive_tablet_up(double x, double y)
{

}

void b_receive_tablet_motion(double x, double y)
{

}

void b_receive_tablet_drag(double x, double y)
{

}

void b_receive_tablet_motion_rich(double x, double y, int button,
				  double pressure, double rotation,
				  double tilt_x, double tilt_y,
				  double tangential)
{

}
void b_receive_tablet_drag_rich(double x, double y, int button, double pressure,
				double rotation, double tilt_x, double tilt_y,
				double tangential)
{
	
}
void b_receive_tablet_down_rich(double x, double y, int button, double pressure,
				double rotation, double tilt_x, double tilt_y,
				double tangential)
{
	
	
}

void b_receive_tablet_up_rich(double x, double y, int button, double pressure,
			      double rotation, double tilt_x, double tilt_y,
			      double tangential)
{
	
	
}
