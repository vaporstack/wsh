//
//  wsh.h
//  wsh
//
//  Created by Andrew Macfarlane on 12/9/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#ifndef wsh_h_
#define wsh_h_

#define WSH_V_MAJOR 0
#define WSH_V_MINOR 0
#define WSH_V_PATCH 1

/*
#define STR1(x) #x
#define STR2(x) STR1(x)
#define THE_ANSWER 42
#define THE ANSWER_STR STR2(THE_ANSWER)
*/

//#error W_LIBWASH_SVER(WASH_V_MAJOR, WASH_V_MINOR, WASH_V_PATCH)

#include "src/geo/w_document.h"
#include "src/geo/w_line.h"
#include "src/geo/w_object.h"
#include "src/geo/w_point.h"
#include "src/geo/w_sequence.h"
#include "src/geo/w_transform.h"

#include "src/decor/w_brush.h"
#include "src/decor/w_brush_ops.h"
#include "src/io/w_io.h"
#include "src/serial/w_serial.h"
#include "src/util/w_line_ops.h"

char *wsh_get_version_string(void);

#endif /* w_includes_h */
