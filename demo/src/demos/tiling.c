//
//  tiling.c
//  wsh-demo
//
//  Created by vs on 6/12/18.
//  Copyright © 2018 ruminant. All rights reserved.
//

#ifndef tiling_c
#define tiling_c

#include "../demo.h"
#include "../wsh_demo_common.h"

#define DEMO_NAME "tiling"
#define DEMO_NICENAME "Tiling"
static WDocumentHnd document;


static void tablet_prox(int v)
{
	printf("got tablet prox? %d\n", v);
}

static void tablet_up(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	printf("got rich up? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

static void tablet_down(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	printf("got rich down? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

static void tablet_drag(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	printf("got rich drag? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

static void tablet_motion(double x, double y, int button, double p, double r, double tx, double ty, double altitude, double azimuth, double idk)
{
	printf("got rich motion? %f %f %f %f %f %f\n", x, y, p, r, tx, ty);
}

static void key(int key, int action, int mods)
{
}

static void mouse_move(double x, double y)
{
}

static void mouse_button(int button, int action, int mods)
{
}

static void init(void)
{
	printf("%s  init!\n", DEMO_NICENAME);
}

static void deinit(void)
{
	printf("%s  deinit!\n", DEMO_NICENAME);
}

static void update(void)
{
}

#define TMP_ROWS 2
#define TMP_COLS 2

static void draw(void)
{
	int w = frame_w;
	int h = frame_h;
	int sx = w / TMP_ROWS;
	int sy = h / TMP_COLS;
	if ( !document.src )
		return;
	WSequence* seq = document.src->sequence.src;
	int num = seq->num_frames;
	int idx = 0;
	for ( int y = 0; y < TMP_ROWS; y++)
	{
		for(int x = 0; x < TMP_COLS; x++)
		{
			if ( idx > num )
				continue;
			int px = x * sx;
			int py = y * sy;
			drw_push();
			drw_translate2f(px,py);
			WObject* frame = seq->frames[idx];
			drw_scale_u(sx);
			
			drw_wobject(frame);
			drw_color(1,0,0,1);
			drw_rect(frame->bounds.pos.x, frame->bounds.pos.y, frame->bounds.pos.x + frame->bounds.size.x, frame->bounds.pos.y + frame->bounds.size.y);
			
			drw_pop();
			
			idx++;
			
		}
	}
}

static void drop(int num, const char** paths)
{
	const char* first = paths[0];
	if (first)
	{
		printf("first is %s\n", first);
	}else{
		return;
	}
	printf("Drop sorta thing? %s\n", first);
	
	if(document.src)
	{
		wsh_document_destroy(document.src);
		document.src = NULL;
	}
	document.src = wsh_serial_document_unserialize(first);
	
	if ( !document.src->sequence.src)
	{
		printf("Load failed!\n");
		return;
	}
	wsh_sequence_normalize(document.src->sequence.src);
	
	
	
}


WashDemo tiling =
{
	DEMO_NICENAME,
	1.0 / 60.0,
	init,
	deinit,
	update,
	draw,
	key,
	mouse_move,
	mouse_button,
	tablet_up,
	tablet_down,
	tablet_motion,
	tablet_drag,
	drop
};

#endif
