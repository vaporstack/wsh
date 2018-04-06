//
//  w_serial.c
//  wash
//
//  Created by Andrew Macfarlane on 1/3/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "w_serial.h"

#include "w_serial_bin.h"
#include <wsh/wsh.h>

#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON
#include "w_serial_json.h"
#endif

#include "../io/w_io.h"

#include <string.h>

char* w_create_version_string()
{
	char* buf = malloc(sizeof(char) * 16);
	sprintf(buf, "%d_%d_%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR,
		WSH_VERSION_PATCH);
	return buf;
}

WDocument* w_serial_document_unserialize(const char* path)
{
#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON
	return w_serial_json_document_unserialize(path);
#else
	printf("Bottleneck interface not yet connected to anything! returning NULL\n");
	return NULL;
#endif
}

int w_serial_document_serialize(WDocument* doc)
{
#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON
	return w_serial_json_document_serialize(doc);
#else
	printf("Bottleneck interface not yet connected to anything! doing nothing\n");
	return -88;
#endif
}
