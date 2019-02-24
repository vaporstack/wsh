//
//  wsh.h
//  wsh
//
//  Created by Andrew Macfarlane on 12/9/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#ifndef wsh_h_
#define wsh_h_

//	https://stackoverflow.com/questions/1638207/how-to-store-a-version-number-in-a-static-library

#include <stdio.h>
#include <stdlib.h>


#define WSH_VERSION "0.0.2"
#define WSH_VERSION_MAJOR 0
#define WSH_VERSION_MINOR 0
#define WSH_VERSION_PATCH 2

#define WSH_VERSION_CHECK(maj, min) ((maj == WSH_VERSION_MAJOR) && (min <= WSH_VERSION_MINOR))

#define WSH_PRESENT

#include "src/io/wsh_log.h"

int   wsh_check_version_match(const char* str);
int   wsh_check_version_match222(const char* str);
int   wsh_check_compat_match(const char* str);
char* wsh_get_version_string(void);
char* wsh_get_compat_string(void);

static inline void wsh_version_check(int major, int minor)
{
	if (!WSH_VERSION_CHECK(major, minor))
	{
		fprintf(stderr, "ERROR: incompatible library version\n");
		exit(-1);
	}
	wsh_log("libwsh is compatible (%s)", WSH_VERSION);
}

static inline char* wsh_get_compat_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d_%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR);
	return buf;
}

static inline char* wsh_get_version_string_header(void)
{
	char* buf = (char*)calloc(256, sizeof(char));
	sprintf(buf, "%d.%d.%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR,
		WSH_VERSION_PATCH);
	return buf;
}

/*
#define STR1(x) #x
#define STR2(x) STR1(x)
#define THE_ANSWER 42
#define THE ANSWER_STR STR2(THE_ANSWER)
*/

//#error W_LIBWSH_SVER(WSH_V_MAJOR, WSH_V_MINOR, WSH_V_PATCH)

#include "src/geo/wsh_document.h"
#include "src/geo/wsh_line.h"
#include "src/geo/wsh_object.h"
#include "src/geo/wsh_point.h"
#include "src/geo/wsh_sequence.h"
#include "src/geo/wsh_transform.h"
#include "src/util/wsh_math.h"
//#include "src/util/w_util_selection.h"

#include "src/core/wsh_tool.h"

#include "src/io/wsh_io.h"
#include "src/serial/wsh_serial.h"
#include "src/session/wsh_session.h"
#include "src/util/wsh_line_ops.h"
#include "src/util/wsh_sequence_ops.h"

//	hack / todo
//#define RUMINANT4_PRESENT

//#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON
//	#include "wsrc/serial/wsh_serial_json.h"
//#endif

#endif /* wsh_includes_h */
