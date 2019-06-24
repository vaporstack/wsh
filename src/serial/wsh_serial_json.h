
//  wsh_serial_json.c
//  wsh_serial_json
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef wsh_serial_json_h_
#define wsh_serial_json_h_

#include <wsh/wsh_config.h>

#include <wsh/wsh.h>

#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON

#include <cjson/cJSON.h>

cJSON*      wsh_serial_json_serialize_color(WColor col);
cJSON*      wsh_serial_json_serialize_color16(WColor16 col);
WColor      wsh_serial_json_unserialize_color(cJSON* data);
WColor16    wsh_serial_json_unserialize_color16(cJSON* data);
WObject*    wsh_serial_json_unserialize_object(cJSON* data);
WSequence*  wsh_serial_json_unserialize_sequence(cJSON* data);
const char* wsh_serial_json_document_serialize(WDocument*);
WDocument* wsh_serial_json_document_unserialize_text(const char* text);
WDocument*  wsh_serial_json_document_unserialize_file(const char* path);
void*	wsh_serial_json_document_unserialize_cjson(const char* path);

#endif

#endif
