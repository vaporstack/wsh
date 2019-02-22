//
//  wsh_io.h
//  r4
//
//  Created by vs on 2/17/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef wsh_io_h
#define wsh_io_h

void*       wsh_read_file_as_bin(const char* path, long* len);
const char* wsh_read_file_as_text(const char* path);
char*       wsh_read_file_as_text_nc(const char* path);
int	 wsh_write_text_to_file(const char* path, const char* data);

#endif /* wsh_io_h */
