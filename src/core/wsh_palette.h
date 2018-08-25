//
//  wsh_palette.h
//  wsh
//
//  Created by vs on 8/24/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef wsh_palette_h
#define wsh_palette_h
#include "wsh_color.h"

typedef struct WshPalette
{
	WColor* data;
	int num;
	
}WshPalette;

WshPalette* wsh_palette_create(void);
void 	wsh_palette_add(WshPalette* pal, WColor16* col);
void	wsh_palette_del(WshPalette* pal, WColor16* col);
void	wsh_palette_del_index(WshPalette* pal, int index);
void wsh_palette_destroy(WshPalette* pal);
WColor16* wsh_palette_color_get(WshPalette* pal, int index);
WColor16** wsh_palette_color_get_all(WshPalette* pal, int* num);

#endif /* wsh_palette_h */
