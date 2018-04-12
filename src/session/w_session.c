
//  w_session.c
//  w_session
//
//  Created by Andrew Macfarlane on 09/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "w_session.h"

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static const char* path      = NULL;
static int	 recording = 0;
void*		   data      = NULL; //T B VERY MUCH D

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
	return true;
}

int w_session_deinit()
{

	//	do stuff
	return 1;
}

int w_session_start(void)
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

int w_session_stop(void)
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
