//
//  w_serial_json_wsh_tool.h
//  wsh
//
//  Created by vs on 3/15/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef w_serial_json_wsh_tool_h
#define w_serial_json_wsh_tool_h

#ifdef WSH_ENABLE_BACKEND_JSON

#include "../core/wsh_tool.h"

#include <cjson/cJSON.h>

cJSON*      w_serial_json_wsh_tool_serialize(WshToolRec* rec);
WshToolRec* w_serial_json_wsh_tool_unserialize(cJSON* data);

#endif

#endif /* w_serial_json_wsh_tool_h */
