//
//  wsh_serial_json_wsh_tool.h
//  wsh
//
//  Created by vs on 3/15/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef wsh_serial_json_wsh_tool_h
#define wsh_serial_json_wsh_tool_h

#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON

#include "../core/wsh_tool.h"

#include <cjson/cJSON.h>

cJSON*      wsh_serial_json_wsh_tool_serialize(WshToolRec* rec);
WshToolRec* wsh_serial_json_wsh_tool_unserialize(cJSON* data);

#endif

#endif /* wsh_serial_json_wsh_tool_h */
