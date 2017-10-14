
//  w_serial_bin.c
//  w_serial_bin
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_serial_bin_h_
#define w_serial_bin_h_

#include "stdlib.h"
#include "stdio.h"

#include "../geo/w_document.h"

//WObject* w_unserialize_object_bin(FILE*);
WDocument* 	w_document_unserialize_bin(const char* path);
int			w_document_serialize_bin(WDocument* doc, const char* path);



#endif
