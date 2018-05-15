//
//  wsh_demo_common.c
//  wash-demo
//
//  Created by vs on 3/21/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#include "wsh_demo_common.h"

WLineHnd work_line;
WObjectHnd test_geometry;


int window_w = 0;
int window_h = 0;
int frame_w = 0;
int frame_h = 0;
double dpi = 1;

int mouse_down = false;
int mouse_present = false;
double mouse_x = 0;
double mouse_y = 0;
//double mouse_present = false;

bool wash_demo_has_pressure_sensitivity_of_any_kind = false;
