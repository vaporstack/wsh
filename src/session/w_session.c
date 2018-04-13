
//  w_session.c
//  w_session
//
//  Created by Andrew Macfarlane on 09/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "w_session.h"

#include "../geo/w_document.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define IDENTIFIER_MAX 256

static const char*  path      = NULL;
static int	  recording = 0;
static void*	data      = NULL; //T B VERY MUCH D
static WDocumentHnd document;
static const char** tool_names = NULL;
static int	  num_tools  = 0;
const WshToolRec* current_tool_rec = NULL;

int w_session_rec_tool_register(WshToolRec* rec)
{
	if (strlen(rec->identifier) > IDENTIFIER_MAX)
	{
		printf("Identifier too long!\n");
		return false;
	}
	for (int i = 0; i < num_tools; i++)
	{
		if (0 == strcmp(rec->identifier, tool_names[i]))
		{
			printf("Already have this tool!\n");
			return false;
		}
	}
	num_tools++;
	if (tool_names == NULL)
	{
		tool_names = calloc(IDENTIFIER_MAX, sizeof(char));
	}
	else
	{
		tool_names = realloc(tool_names, IDENTIFIER_MAX * sizeof(char));
	}
	tool_names[num_tools - 1] = rec->identifier;
	printf("Registered tool: %s\n", tool_names[num_tools - 1]);
	return true;
}

int w_session_rec_tool_change(WshToolRec* rec, double ts)
{
	if (current_tool_rec == rec )
	{
		printf("Already using this tool, not changing.\n");
		return false;
	}
	current_tool_rec = rec;
	return true;
}

int w_session_rec_tool_activity(WshToolRec* rec, double ts)
{
	return 0;
}

int w_session_rec_tool_cease(WshToolRec* rec, double ts)
{
	return 0;
}

int w_session_rec_tool_begin(WshToolRec* rec, double ts)
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

int w_session_set_path(const char* _path)
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

int w_session_init()
{
	if (path == NULL)
	{
		printf("Session path was not defined, session cannot start.\n");
		return false;
	}
	printf("Pretending our session was successfully initialized!\n");
	document.src = w_document_create();
	return true;
}

int w_session_deinit()
{
	//	do stuff

	//	write our document to disk?
	//	keep it single file for simplicity?

	return 1;
}

int w_session_start(double ts)
{
	printf("Starting wsh recording session.\n");
	if (recording)
	{
		printf("Was already recording!\n");
		return false;
	}
	recording = true;

	return true;
}

int w_session_stop(double ts)
{
	if (!recording)
	{
		printf("Was already NOT recording!\n");
		return false;
	}
	recording = false;

	printf("Stopping wsh recording session.\n");
	return true;
}

void w_session_print_debug_info(void)
{
	printf("Tools:\n");
	for (int i = 0; i < num_tools; i++)
	{
		printf("Tool: %s\n", tool_names[i]);
	}
}
