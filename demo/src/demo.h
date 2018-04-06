//
//  demo.h
//  wash-demo
//
//  Created by vs on 3/20/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef demo_h
#define demo_h

#include <stdio.h>


typedef void(*demo_fn)(void);
typedef void(*key_fn)(int key, int action, int mods);
typedef void(*tablet_fn)(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk);
typedef void(*mouse_move_fn)(double x, double y);
typedef void(*mouse_click_fn)(int btn, int action, int mods);

typedef struct WashDemo
{
	const char* name;
	double fps;
	demo_fn init;
	demo_fn deinit;
	demo_fn update;
	demo_fn draw;
	key_fn key;
	mouse_move_fn mouse_move;
	mouse_click_fn mouse_click;
	tablet_fn up;
	tablet_fn down;
	tablet_fn motion;
	tablet_fn drag;
} WashDemo;

#endif /* demo_h */
