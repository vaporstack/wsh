//
//  wash_demo_common.h
//  wash-demo
//
//  Created by vs on 3/21/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef wash_demo_common_h
#define wash_demo_common_h

#include <stdbool.h>
#include <stdio.h>
#include <wsh/wsh.h>


extern int window_w;
extern int window_h;
extern int framebuffer_w ;
extern int framebuffer_h;

extern WLineHnd work_line;
extern WObjectHnd test_geometry;

extern bool wash_demo_has_pressure_sensitivity_of_any_kind;

#endif /* wash_demo_common_h */
