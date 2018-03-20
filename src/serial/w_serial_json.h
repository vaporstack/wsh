
//  w_serial_json.c
//  w_serial_json
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_serial_json_h_
#define w_serial_json_h_

#include <wsh/wsh.h>

//#ifndef RPLATFORM_IOS
#include <cjson/cJSON.h>

cJSON*      w_serial_json_serialize_color(WColor col);
cJSON*      w_serial_json_serialize_color16(WColor16 col);
WColor      w_serial_json_unserialize_color(cJSON* data);
WColor16    w_serial_json_unserialize_color16(cJSON* data);
WObject*    w_serial_json_unserialize_object(cJSON* data);
WSequence*  w_serial_json_unserialize_sequence(cJSON* data);
const char* w_serial_json_serialize_document(WDocument*);
WDocument*  w_serial_json_unserialize_document(const char* path);

//void* w_serial_json_unserialize_document_generic(const char* path);

//#endif

#endif
