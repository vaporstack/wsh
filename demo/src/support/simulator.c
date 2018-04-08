//
//  simulator.c
//  wash-demo
//
//  Created by vs on 4/5/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "simulator.h"


static double fake_pressure = 0.0f;
static double fake_rotation = 0.0f;
static double fake_tilt = 0;
static double fake_tilt_v = 0;

void simulator_reset_sims(void)
{
	fake_pressure = 0;
	fake_rotation = 0;
	fake_tilt_v = 0;
}

WPoint simulator_simulate_point(double x, double y)
{
	
	double v = (double)rand() / RAND_MAX;
	fake_tilt_v += -.5 + v * .1;
	if ( fake_tilt_v < -1 )
		fake_tilt_v = -1;
	if ( fake_tilt_v > 1 )
		fake_tilt_v = 1;
	
	fake_tilt += fake_tilt_v;

	
	fake_pressure += .01;
	fake_pressure *= .9999;
	fake_rotation += 3;
	WPoint p;
	p.x = x;
	p.y = y;
	p.pressure = fake_pressure;
	p.rotation = fake_rotation;
	
	return p;
	
}
