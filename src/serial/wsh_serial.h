//
//  wsh_serial.h
//  wash
//
//  Created by Andrew Macfarlane on 1/3/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef wsh_serial_h
#define wsh_serial_h

#include "../geo/wsh_document.h"

WDocument*  wsh_serial_document_unserialize_file(const char* path);
WDocument*  wsh_serial_document_unserialize_text(const char* text);
const char* wsh_serial_document_serialize(WDocument* doc);
#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON
//	this marks a bit of a paradigm shift, we are passing cjson as a void*
//	so that I can add the plugin info on the application level.
void*		wsh_serial_document_serialize_cjson(WDocument* doc);
#endif

#endif /* wsh_serial_h */
