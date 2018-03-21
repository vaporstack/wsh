//
//  input_tablet.h
//  wash-demo
//
//  Created by vs on 3/21/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef input_tablet_h
#define input_tablet_h
#include <stdbool.h>


int b_tablet_init(void);
void b_tablet_deinit(void);


void	   b_receive_tablet_proximity(bool);

void b_receive_tablet_drag_rich(double, double, int, double, double, double,
				double, double);
void b_receive_tablet_down_rich(double, double, int, double, double, double,
				double, double);
void b_receive_tablet_up_rich(double, double, int, double, double, double,
			      double, double);
void b_receive_tablet_motion_rich(double, double, int, double, double, double,
				  double, double);


#endif /* input_tablet_h */
