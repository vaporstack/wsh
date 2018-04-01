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


typedef void(*draw_fn)(void);

typedef struct WashDemo
{
	draw_fn draw;
} WashDemo;

int demos_init(void);
int demos_deinit(void);

#endif /* demo_h */
