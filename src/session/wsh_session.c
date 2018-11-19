
//  wsh_session.c
//  wsh_session
//
//  Created by Andrew Macfarlane on 09/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "wsh_session.h"

#include "../geo/wsh_document.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wsh/wsh.h>

#define IDENTIFIER_MAX 256

static const char*  path      = NULL;
static int	  recording = 0;
static void*	data      = NULL; //T B VERY MUCH D
static WDocumentHnd document;
static const char** tool_names       = NULL;
static int	  num_tools	= 0;
const WshToolRec*   current_tool_rec = NULL;

int wsh_session_rec_tool_register(WshToolRec* rec)
{
	if (strlen(rec->identifier) > IDENTIFIER_MAX)
	{
#ifdef DEBUG
		printf("Identifier too long!\n");
#endif
		return false;
	}
	for (int i = 0; i < num_tools; i++)
	{
		if (0 == strcmp(rec->identifier, tool_names[i]))
		{
#ifdef DEBUG
			printf("Already have this tool!\n");
#endif
			return false;
		}
	}
	num_tools++;
	if (tool_names == NULL)
	{
		tool_names = calloc(IDENTIFIER_MAX, sizeof(char*));
	}
	else
	{
		tool_names = realloc(tool_names, IDENTIFIER_MAX * sizeof(char*));
	}
	tool_names[num_tools - 1] = rec->identifier;
#ifdef DEBUG
	printf("Registered tool: %s\n", tool_names[num_tools - 1]);
#endif
	return true;
}

int wsh_session_rec_tool_change(WshToolRec* rec, double ts)
{
	if (current_tool_rec == rec)
	{
		printf("Already using this tool, not changing.\n");
		return false;
	}
	current_tool_rec = rec;
	return true;
}

int wsh_session_rec_tool_activity(WshToolRec* rec, double ts)
{
	return 0;
}

int wsh_session_rec_tool_cease(WshToolRec* rec, double ts)
{
	return 0;
}

int wsh_session_rec_tool_begin(WshToolRec* rec, double ts)
{
	return 0;
}

#pragma mark core

static int check_if_directory_exists(const char* path)
{
	struct stat s;
	int	 err = stat(path, &s);
	if (-1 == err)
	{
		if (ENOENT == errno)
		{
			return 0;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (S_ISDIR(s.st_mode))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

int wsh_session_set_path(const char* _path)
{
	if (_path == NULL)
		return 0;
	if (check_if_directory_exists(_path))
	{
		path = _path;
		return 1;
	}
	return 0;
}

int wsh_session_init()
{
	if (path == NULL)
	{
		printf("Session path was not defined, session cannot start.\n");
		return false;
	}
	printf("Pretending our session was successfully initialized!\n");
	document.src = wsh_document_create();
	return true;
}

int wsh_session_deinit()
{
	//	do stuff

	//	write our document to disk?
	//	keep it single file for simplicity?

	return 1;
}

int wsh_session_start(double ts)
{
	wsh_log("Starting wsh recording session.");
	if (recording)
	{
		printf("Was already recording!\n");
		return false;
	}
	recording = true;

	return true;
}

int wsh_session_stop(double ts)
{
	if (!recording)
	{
		printf("Was already NOT recording!\n");
		return false;
	}
	recording = false;

	wsh_log("Stopping wsh recording session.");
	return true;
}

void wsh_session_print_debug_info(void)
{
	wsh_log("Tools:");
	for (int i = 0; i < num_tools; i++)
	{
		printf("Tool: %s\n", tool_names[i]);
	}
}