
//  w_serial_json.c
//  w_serial_json
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_serial_json_h_
#define w_serial_json_h_

//#include <r4/src/r4_config.h>
#include <wsh/wsh.h>

//#ifndef RPLATFORM_IOS
#include <include/cJSON.h>

WObject*		w_unserialize_object_json(cJSON* data);
WSequence*		w_unserialize_sequence_json(cJSON* data );

const char*		w_document_serialize_json(WDocument*);
WDocument*		w_document_unserialize_json(const char* path);

//#endif

#endif
