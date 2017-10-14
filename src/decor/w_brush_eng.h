
//  w_brush_eng.c
//  w_brush_eng
//
//  Created by Andrew Macfarlane on 04/04/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_brush_eng_h_
#define w_brush_eng_h_


#include "../geo/w_line.h"

void	w_brush_line_add(WLineHnd*);
void	w_brush_line_remove(WLineHnd*);

void	w_brush_eng_update(void);
void	w_brush_eng_draw(void);

int		w_brush_eng_init(void);
void	w_brush_eng_deinit(void);

#endif
