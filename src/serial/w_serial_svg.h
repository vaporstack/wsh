
//  w_serial_svg.c
//  w_serial_svg
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_serial_svg_h_
#define w_serial_svg_h_




#include "../../wsh.h"

#include "../../../r4/src/r4_platform.h"

#ifndef RPLATFORM_IOS
#ifndef RPLATFORM_WIN

//#error foo
const char*		w_serialize_document_svg(WDocument*);
WDocument*		w_document_unserialize_svg(const char* path);

#endif
#endif

#endif
