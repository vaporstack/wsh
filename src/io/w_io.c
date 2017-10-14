//
//  r_io.c
//  r4
//
//  Created by vs on 2/17/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "w_io.h"

#include <stdlib.h>

#include <r4/r4.h>
#include <stdio.h>


#include <string.h>


//	TODO unify the various stupid file reading functions






void* w_read_file_as_bin(const char* path, long* len)
{
	FILE *fileptr;
	//char *buffer;
	//long filelen;
	long l;
	
	fileptr = fopen(path, "rb");  // Open the file in binary mode
	if ( !fileptr )
	{
		return NULL;
	}
	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	l = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file
	
	printf("%lu\n", *len);
	long sz =(l+1)*sizeof(char);
	void* buf = malloc(sz); // Enough memory for file + \0
	memset(buf, 0, sz);
	fread(buf, l, 1, fileptr); // Read in the entire file
	fclose(fileptr); // Close the file
	*len = l;
	return 0;
}






const char* w_read_file_as_text(const char*path)
{
	FILE* f;

	f = fopen(path, "r");
	if ( !f )
	{
		char buf[256];
		sprintf(buf, "Failed to open file: %s\n", path );
		printf("%s\n", buf);
		return NULL;

	}
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);

	char *data = malloc(fsize + 1);
	fread(data, fsize, 1, f);
	fclose(f);

	data[fsize] = 0;

	return data;
	
}

char* w_read_file_as_text_nc(const char*path)
{
	FILE* f;

	f = fopen(path, "r");
	if ( !f )
	{
		char buf[256];
		sprintf(buf, "Failed to open file: %s\n", path );
		printf("%s\n", buf);
		return NULL;

	}
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  //same as rewind(f);

	char *data = malloc(fsize + 1);
	fread(data, fsize, 1, f);
	fclose(f);

	data[fsize] = 0;

	return data;
	
}


int w_write_text_to_file(const char* path, const char*data)
{
	FILE* f;
	f = fopen(path, "w");
	if(!data)
	{
		printf("Data was null!\n");
		return 1;
	}
	if ( !f )
	{
		char buf[256];
		sprintf(buf, "Failed to open file: %s\n", path );
		printf("%s\n", buf);
		//printf("Failed to open file: %s\n", path);
		return 1;

	}

	fprintf(f, "%s", data);
	fclose(f);

	return 0;
}
