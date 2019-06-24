//
//  wsh_tagdb.cx`
//  wsh
//
//  Created by vs on 2/22/19.
//  Copyright © 2019 vaporstack. All rights reserved.
//

#include "wsh_tagdb.h"


#include "../io/wsh_io.h"
#include "../io/wsh_log.h"
#include <cjson/cJSON.h>
#include <string.h>

#define kWshTagName_EN_US "tags"
#define MAX_TAG_LENGTH 256

static cJSON* json = NULL;

bool wsh_tagdb_load(const char* path)
{
//	FILE* f = fopen(path, "r");
//	if (!f)
//	{
//		wsh_log("file does not exist.");
//	}
	printf("Loading json\n");
	const char* data = wsh_read_file_as_text(path);
	if ( !data )
		return false;
	
	if ( 0 == strcmp("", data))
	{
		json = cJSON_CreateObject();
	}else{
		json = cJSON_Parse(data);
		
	}
	return true;
}

static void reduce_duplicates(void)
{
	cJSON* arr = cJSON_GetObjectItem(json, kWshTagName_EN_US);
	
	int num = cJSON_GetArraySize(arr);
	
	char** uniq = calloc(num, sizeof(char*) * MAX_TAG_LENGTH);
	int uniqnum = 0;
	
	for( int i = 0; i < num; i++ )
	{
		cJSON* v = cJSON_GetArrayItem(arr, i);
		char* s = v->valuestring;
		bool matches_any = false;
		for ( int j = 0 ; j < uniqnum; j++)
		{
			char* cmp = uniq[j];
			if ( 0 == strcmp(cmp, s ))
				matches_any = true;
		}
		if ( !matches_any )
		{
			uniq[uniqnum] = s;
			uniqnum++;
			
		}
	}
	
	cJSON* narr = cJSON_CreateArray();
	for ( int i  = 0; i < uniqnum; i++)
	{
		cJSON_AddItemToArray(narr, cJSON_CreateString(uniq[i]));
	}
	
	cJSON_ReplaceItemInObject(json, kWshTagName_EN_US, narr);
	free(uniq);
}

bool wsh_tagdb_save(const char* path)
{
	reduce_duplicates();
	char* data = cJSON_Print(json);
	wsh_write_text_to_file(path, data);
	free(data);
	return true;
}

bool wsh_tagdb_add(const char* key)
{
	if ( strlen(key) > MAX_TAG_LENGTH )
	{
		wsh_log("Key exceeds maximum length: %d (this can be changed at compile time)", MAX_TAG_LENGTH);
		return false;
	}
	
	cJSON* tags = cJSON_GetObjectItem(json, kWshTagName_EN_US);
	if ( !tags)
	{
		tags = cJSON_CreateArray();
	}
	
	cJSON* v = cJSON_CreateString(key);
	cJSON_AddItemToArray(tags, v);
	cJSON_ReplaceItemInObject(json, kWshTagName_EN_US, tags);
	return true;
}

const char** wsh_tagdb_list(int* num)
{
	if ( !json )
	{
		wsh_log("Can't list tags, no json loaded.");
		return NULL;
	}
	
	cJSON* tags = cJSON_GetObjectItem(json, kWshTagName_EN_US);
	if ( !tags)
	{
		wsh_log("Unable to retrieve tags from json");
		return NULL;
	}
	
	int len = cJSON_GetArraySize(tags);
	const char** res = calloc(len, sizeof(char*) * MAX_TAG_LENGTH);
	
	for ( int i  = 0, n = len; i < n; i++ )
	{
		cJSON* tag = cJSON_GetArrayItem(tags, i);
		res[i] = tag->valuestring;
	}
	
	*num = len;
	return res;
}
