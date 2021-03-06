//
//  w_serial.c
//  wash
//
//  Created by Andrew Macfarlane on 1/3/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "w_serial.h"

#include "w_serial_json.h"

#include "../io/w_io.h"
#include <string.h>

char* w_create_version_string()
{
	char* buf = malloc(sizeof(char) * 16);
	sprintf(buf, "%d_%d_%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR,
		WSH_VERSION_PATCH);
	return buf;
}
