//
//  w_serial.h
//  wash
//
//  Created by Andrew Macfarlane on 1/3/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef w_serial_h
#define w_serial_h

#include "../geo/w_document.h"

WDocument* w_serial_document_unserialize(const char* path);
const char*	w_serial_document_serialize(WDocument* doc);


#endif /* w_serial_h */
