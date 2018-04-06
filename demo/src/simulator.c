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

WPoint simulator_simulate_point(double x, double y)
{
	
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
