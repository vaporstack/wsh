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

#include "support/primitives.h"
#include "support/recorder.h"
#include "support/simulator.h"
#include "support/ops.h"
#include "support/text.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

extern int window_w;
extern int window_h;
extern int frame_w ;
extern int frame_h;

extern WLineHnd work_line;
extern WObjectHnd test_geometry;

extern bool wash_demo_has_pressure_sensitivity_of_any_kind;

#endif /* wash_demo_common_h */
