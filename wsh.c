//
//  wsh_includes.h
//  wash
//
//  Created by Andrew Macfarlane on 12/9/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#ifndef wsh_includes_h
#define wsh_includes_h

#include "wsh.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define WSH_LOG_MAX 256

void wsh_log(char* format, ...)
{

	char buf[WSH_LOG_MAX];
	sprintf(buf, "%s", format);
	va_list args;
	va_start(args, format);
	vsprintf(buf, format, args);
	va_end(args);

#ifdef DEBUG
	printf("[wsh ]: %s\n", buf);
#else
	printf("DO NOTHING LATER: %s\n", buf);
#endif
}

int wsh_check_version_match(const char* header_generated_version)
{
	char* vstring = wsh_get_version_string();
	int   res     = (0 == strcmp(vstring, header_generated_version));
	free(vstring);
	return res;
}

char* wsh_get_version_string(void)
{
	char* buf = calloc(256, sizeof(char));
	sprintf(buf, "%d.%d.%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR,
		WSH_VERSION_PATCH);
	return buf;
}

void init_wash(){
    // printf("asdfasdfasdfasdfasdfasfasdf");
};

struct
{
	const char*    string;
	const unsigned major;
	const unsigned minor;
	const unsigned revision;
} wsh_version = {
    WSH_VERSION, WSH_VERSION_MAJOR, WSH_VERSION_MINOR, WSH_VERSION_PATCH};

#endif /* wsh_includes_h */
