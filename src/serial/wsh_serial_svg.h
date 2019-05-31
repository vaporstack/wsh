
//  w_serial_svg.c
//  w_serial_svg
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_serial_svg_h_
#define w_serial_svg_h_


//#define WSH_ENABLE_SERIAL_BACKEND_SVG

#include "../wsh_config.h"

#ifdef WSH_ENABLE_SERIAL_BACKEND_SVG

#include <wsh/wsh.h>

const char* wsh_serial_svg_document_serialize(WDocument*);
WDocument*  wsh_serial_svg_document_unserialize(const char* path);
#endif

#endif
