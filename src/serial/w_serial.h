//
//  w_serial.h
//  wash
//
//  Created by Andrew Macfarlane on 1/3/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef w_serial_h
#define w_serial_h

#include "../../wsh.h"
#include "w_serial_svg.h"
#include "w_serial_json.h"
#include "w_serial_bin.h"

//const char*		w_serialize_object_json(WObject* obj);
//WObject*		w_unserialize_object_json(const char* path);

//const char*		w_serialize_object_svg(WObject* obj);
//WObject*		w_unserialize_object_svg(const char* path);


//void			w_serialize_line(WObject*, FILE* );
//void			w_serialize_point(WPoint*, FILE* );

char*		w_create_version_string(void);

//int				w_document_serialize_bin(WDocument*);
//WDocument 		w_document_unserialize_bin(const char* path);

//int				w_serialize_document_svg(WDocument*);
//WDocument*		w_document_unserialize_svg(const char* path);

#endif /* w_serial_h */
