//
//  recorder.h
//  wash-demo
//
//  Created by vs on 4/5/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef recorder_h
#define recorder_h


#include <wsh/wsh.h>

void recorder_init(void);
void recorder_deinit(void);

void recorder_record_manual_point(WPoint p);
void recorder_record_point(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk);
void recorder_end_line(double x, double y);
void recorder_clear(void);

#endif /* recorder_h */
