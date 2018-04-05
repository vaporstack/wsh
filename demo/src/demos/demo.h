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
typedef void(*key_fn)(int key, int action);

typedef struct WashDemo
{
	const char* name;
	double fps;
	demo_fn init;
	demo_fn deinit;
	demo_fn update;
	demo_fn draw;
	key_fn key;
} WashDemo;

#endif /* demo_h */
