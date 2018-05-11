//
//  w_point.h
//  wash
//
//  Created by Andrew Macfarlane on 12/9/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

/** @file w_point.h
 *  @brief Fundamental data unit for wsh (rich content support)
 *
 *  This contains the prototypes for the console
 *  driver and eventually any macros, constants,
 *  or global variables you will need.
 *
 *  @author Andrew Macfarlane (_ruminant on twitter dawt cawm)
 *  @bug All the bugs.
 */

#ifndef w_point_h
#define w_point_h

typedef struct
{
	double x;
	double y;
	double pressure;
	double tilt_x;
	double tilt_y;
	double rotation;
	double time;
} WPoint;

/*
 *
 */
void w_point_zero(WPoint*);

/**
 *
 *@return WPoint
 *
 */
WPoint* w_point_create(void);

/**
 *
 *@return WPoint
 *
 */
WPoint* w_point_create_2f(double, double);

/**
 *
 *
 *
 */
void w_point_rotate(WPoint* p, double cx, double cy, double angle_in_degrees);

#endif /* w_point_h */
