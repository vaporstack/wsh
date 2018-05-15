
//  wsh_session.c
//  wsh_session
//
//  Created by Andrew Macfarlane on 09/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef wsh_session_h_
#define wsh_session_h_

#include "../core/wsh_tool.h"

int wsh_session_rec_frame_switch(void);

int wsh_session_rec_tool_register(WshToolRec* rec);
int wsh_session_rec_tool_change(WshToolRec* rec, double ts);
int wsh_session_rec_tool_activity(WshToolRec* rec, double ts);
int wsh_session_rec_tool_cease(WshToolRec* rec, double ts);
int wsh_session_rec_tool_begin(WshToolRec* rec, double ts);

int wsh_session_init(void);
int wsh_session_deinit(void);
int wsh_session_set_path(const char* path);
int wsh_session_set_name(void);
int wsh_session_start(double ts);
int wsh_session_stop(double ts);

void wsh_session_print_debug_info(void);

#endif
