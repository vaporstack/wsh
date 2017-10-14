
//  w_session.c
//  w_session
//
//  Created by Andrew Macfarlane on 09/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#ifndef w_session_h_
#define w_session_h_



typedef struct ToolDesc
{
	char* tool_name;

} ToolDesc;

typedef struct StrokeAttr
{
	char* stroke_name;
	int stroke_type;
} StokeAttr;

int w_session_rec_frame_switch(void);

int w_session_rec_switch_tool(void);
int w_session_rec_tool_activity(ToolDesc* desc);
int w_session_rec_tool_cease(ToolDesc* desc);
int w_session_rec_tool_begin(ToolDesc* desc);
int w_session_init(void);
int w_session_deinit(void);

#endif
