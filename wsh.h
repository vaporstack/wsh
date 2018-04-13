//
//  wsh.h
//  wsh
//
//  Created by Andrew Macfarlane on 12/9/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#ifndef wsh_h_
#define wsh_h_

#include <stdio.h>
#include <stdlib.h>

#define WSH_VERSION_MAJOR 0
#define WSH_VERSION_MINOR 0
#define WSH_VERSION_PATCH 2

#define WSH_COMPAT

int		    wsh_check_version_match(const char* str);
int		    wsh_check_compat_match(const char* str);
char*		    wsh_get_version_string(void);
char*		    wsh_get_compat_string(void);
static inline char* wsh_get_compat_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d_%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR);
	return buf;
}

static inline char* wsh_get_version_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d_%d_%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR,
		WSH_VERSION_PATCH);
	return buf;
}

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
#include "src/util/w_math.h"

#include "src/core/wsh_tool.h"

#include "src/io/w_io.h"
#include "src/serial/w_serial.h"
#include "src/session/w_session.h"
#include "src/util/w_line_ops.h"

//	hack / todo
//#define R4_PRESENT

#ifdef R4_PRESENT
#define WSH_ENABLE_SERIAL_BACKEND_JSON
#endif

#define WSH_ENABLE_SERIAL_BACKEND_BIN
#define WSH_ENABLE_SERIAL_BACKEND_OBF

//#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON
//	#include "wsrc/serial/w_serial_json.h"
//#endif

#endif /* w_includes_h */
