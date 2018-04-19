
//  w_session.c
//  w_session
//
//  Created by Andrew Macfarlane on 09/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_session_h_
#define w_session_h_

#include "../core/wsh_tool.h"

int w_session_rec_frame_switch(void);

int w_session_rec_tool_register(WshToolRec* rec);
int w_session_rec_tool_change(WshToolRec* rec, double ts);
int w_session_rec_tool_activity(WshToolRec* rec, double ts);
int w_session_rec_tool_cease(WshToolRec* rec, double ts);
int w_session_rec_tool_begin(WshToolRec* rec, double ts);

int w_session_init(void);
int w_session_deinit(void);
int w_session_set_path(const char* path);
int w_session_set_name(void);
int w_session_start(double ts);
int w_session_stop(double ts);

void w_session_print_debug_info(void);

#endif
