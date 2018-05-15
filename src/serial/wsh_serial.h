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

WDocument*  wsh_serial_document_unserialize(const char* path);
const char* wsh_serial_document_serialize(WDocument* doc);

#endif /* wsh_serial_h */
