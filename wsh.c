//
//  w_includes.h
//  wash
//
//  Created by Andrew Macfarlane on 12/9/16.
//  Copyright © 2016 vaporstack. All rights reserved.
//

#ifndef w_includes_h
#define w_includes_h

#include "wsh.h"

#include <stdio.h>
#include <string.h>

int wsh_check_version_match(const char *header_generated_version)
{

	return (0 ==
		strcmp(wsh_get_version_string(), header_generated_version));
}

char *wsh_get_version_string(void)
{
	char *buf = calloc(256, sizeof(char));
	sprintf(buf, "%d_%d_%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR,
		WSH_VERSION_PATCH);
	return buf;
}

void init_wash(){
    // printf("asdfasdfasdfasdfasdfasfasdf");
};

#endif /* w_includes_h */
