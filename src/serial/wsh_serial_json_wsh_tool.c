//
//  wsh_serial_json_wsh_tool.c
//  wsh
//
//  Created by vs on 3/15/18.
//  Copyright © 2018 vaporstack. All rights reserved.
//

#include "wsh_serial_json_wsh_tool.h"

#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON

#include "wsh_serial_json.h"
#include <cjson/cJSON.h>
#include <stdlib.h>

cJSON* wsh_serial_json_wsh_tool_serialize(WshToolRec* rec)
{

	cJSON* root = cJSON_CreateObject();

	cJSON_AddStringToObject(root, "name", rec->name);
	cJSON_AddStringToObject(root, "identifier", rec->identifier);

	cJSON_AddNumberToObject(root, "attack", rec->attack);
	cJSON_AddNumberToObject(root, "decay", rec->decay);
	cJSON_AddNumberToObject(root, "sustain", rec->sustain);
	cJSON_AddNumberToObject(root, "release", rec->release);

	cJSON_AddNumberToObject(root, "size_perim", rec->size_perim);
	cJSON_AddNumberToObject(root, "size_outer", rec->size_outer);
	cJSON_AddNumberToObject(root, "size_inner", rec->size_inner);
	cJSON_AddNumberToObject(root, "size_base", rec->size_base);
	cJSON_AddNumberToObject(root, "size_mod", rec->size_mod);

	cJSON* color = wsh_serial_json_serialize_color16(rec->color);

	int    num    = rec->color_num;
	cJSON* colors = cJSON_CreateArray();

	for (int i = 0; i < num; i++)
	{
		cJSON* v = wsh_serial_json_serialize_color16(rec->colors[i]);
		cJSON_AddItemToArray(colors, v);
	}

	cJSON_AddItemToObject(root, "colors", colors);

	//	todo : figure out if we're doing texture files or what
	return root;
}

WshToolRec* wsh_serial_json_wsh_tool_unserialize(cJSON* data)
{
	WshToolRec* rec = calloc(1, sizeof(WshToolRec));
	cJSON*      v   = NULL;
	v		= cJSON_GetObjectItem(data, "name");
	if (v)
		rec->name = v->valuestring;
	v = cJSON_GetObjectItem(data, "identifier");
	if (v)
		rec->identifier = v->valuestring;

	v = cJSON_GetObjectItem(data, "attack");
	if (v)
		rec->attack = v->valuedouble;
	v = cJSON_GetObjectItem(data, "decay");
	if (v)
		rec->decay = v->valuedouble;
	v = cJSON_GetObjectItem(data, "sustain");
	if (v)
		rec->sustain = v->valuedouble;
	v = cJSON_GetObjectItem(data, "release");
	if (v)
		rec->release = v->valuedouble;
	v = cJSON_GetObjectItem(data, "size_base");
	if (v)
		rec->size_base = v->valuedouble;
	v = cJSON_GetObjectItem(data, "size_inner");
	if (v)
		rec->size_inner = v->valuedouble;

	v = cJSON_GetObjectItem(data, "size_outer");
	if (v)
		rec->size_outer = v->valuedouble;

	v = cJSON_GetObjectItem(data, "size_perim");
	if (v)
		rec->size_perim = v->valuedouble;

	v = cJSON_GetObjectItem(data, "size_mod");
	if (v)
		rec->size_mod = v->valuedouble;

	v = cJSON_GetObjectItem(data, "color");

	if (v)
		rec->color = wsh_serial_json_unserialize_color16(v);

	v = cJSON_GetObjectItem(data, "colors");
	if (v)
	{
		int num     = cJSON_GetArraySize(v);
		rec->colors = calloc(num, sizeof(WColor16));
		for (int i = 0; i < num; i++)
		{
			cJSON* jv      = cJSON_GetArrayItem(v, i);
			rec->colors[i] = wsh_serial_json_unserialize_color16(jv);
		}
	}
	return rec;
}

#endif
