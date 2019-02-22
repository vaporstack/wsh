//
//  wsh_log.c
//  wsh
//
//  Created by vs on 2/22/19.
//  Copyright © 2019 vaporstack. All rights reserved.
//

#include "wsh_log.h"


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


