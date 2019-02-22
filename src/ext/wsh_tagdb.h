//
//  wsh_tagdb.h
//  wsh
//
//  Created by vs on 2/22/19.
//  Copyright © 2019 vaporstack. All rights reserved.
//

#ifndef wsh_tagdb_h
#define wsh_tagdb_h

#include "../../wsh_internal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON

bool	 wsh_tagdb_load(const char* path);
bool	 wsh_tagdb_save(const char* path);
bool	 wsh_tagdb_add(const char* key);
const char** wsh_tagdb_list(int* num);

#endif

#endif /* wsh_tagdb_h */
