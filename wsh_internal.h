//
//  wsh_internal.h
//  wsh-ios
//
//  Created by vs on 4/17/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#ifndef wsh_internal_h
#define wsh_internal_h


//hack / todo
#define R4_PRESENT

#ifdef R4_PRESENT
#ifndef WSH_ENABLE_SERIAL_BACKEND_JSON
#define WSH_ENABLE_SERIAL_BACKEND_JSON
#endif
#endif

#define WSH_ENABLE_SERIAL_BACKEND_BIN
#define WSH_ENABLE_SERIAL_BACKEND_OBF

#endif /* wsh_internal_h */
