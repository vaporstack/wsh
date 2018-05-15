//
//  w_io.h
//  r4
//
//  Created by vs on 2/17/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef w_io_h
#define w_io_h


void*       w_read_file_as_bin(const char* path, long* len);
const char* w_read_file_as_text(const char*);
char*       w_read_file_as_text_nc(const char*);
int	 w_write_text_to_file(const char*, const char*);

#endif /* w_io_h */
