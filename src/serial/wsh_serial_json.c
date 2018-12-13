
//  wsh_serial_json.c
//  wsh_serial_json
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "wsh_serial_json.h"

#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON

#include <cjson/cJSON.h>
#include <string.h>

#include <stdio.h>
/*
 #define REGISTER(ns, id, type)                                          \
 inline Inst* type##Activate() { return new type(); }                 \
 extern bool type##temp
 
 #define INSTANTIATE(ns, id, type)                                       \
 Inst* type##Activate();                                              \
 bool type##temp = RegisterType(ns << 8 | id, &type##Activate)
 */

// http://stackoverflow.com/questions/860273/macro-producing-macros-in-c

//#define make_macro(name,...)  name##_fn(name##_info, __VA_ARGS__)

char* working_version = NULL;

#define DEBUG_SERIAL false


static void fixup_old_style_version_string(char* buf)
{
	int  index = 0;
	do
	{
		char c     = buf[index];
		
		if (c == '\0')
			return;
		
		if (c == '_')
			buf[index] = '.';
		index++;
	}while(true);
	
}

cJSON* wsh_serialize_object_json(WObject* obj);
cJSON* wsh_serialize_sequence_json(WSequence* seq);
cJSON* wsh_serialize_line_json(WLine* line);
cJSON* wsh_serialize_color_json(WColor col);

cJSON* wsh_serialize_object_json_v_0_0_1(WObject* obj);
cJSON* wsh_serialize_sequence_json_v_0_0_1(WSequence* seq);
cJSON* wsh_serialize_line_json_v_0_0_1(WLine* line);
cJSON* wsh_serialize_color_json_v_0_0_1(WColor col);

cJSON* wsh_serial_json_serialize_color(WColor col)
{
	cJSON* ret = cJSON_CreateObject();
	cJSON_AddNumberToObject(ret, "r", col.r);
	cJSON_AddNumberToObject(ret, "g", col.g);
	cJSON_AddNumberToObject(ret, "b", col.b);
	cJSON_AddNumberToObject(ret, "a", col.a);
	return ret;
}

cJSON* wsh_serial_json_serialize_color16(WColor16 col)
{
	cJSON* ret = cJSON_CreateObject();
	cJSON_AddNumberToObject(ret, "r", col.r);
	cJSON_AddNumberToObject(ret, "g", col.g);
	cJSON_AddNumberToObject(ret, "b", col.b);
	cJSON_AddNumberToObject(ret, "a", col.a);
	return ret;
}

WColor wsh_serial_json_unserialize_color(cJSON* data)
{
	WColor c;
	c.a = 1.;
	c.r = 1.;
	c.g = 1.;
	c.b = 1.;
	return c;
}

WColor16 wsh_serial_json_unserialize_color16(cJSON* data)
{
	WColor16 c;
	wsh_color_16_clear(&c);
	
	cJSON* v = NULL;
	v	= cJSON_GetObjectItem(data, "r");
	if (v)
		c.r = v->valuedouble;
	v = cJSON_GetObjectItem(data, "g");
	if (v)
		c.g = v->valuedouble;
	v = cJSON_GetObjectItem(data, "b");
	if (v)
		c.b = v->valuedouble;
	v = cJSON_GetObjectItem(data, "a");
	if (v)
		c.a = v->valuedouble;
	
	return c;
}

static void set_working_version(void)
{
	char* buf = calloc(16, sizeof(char));
	
	sprintf(buf, "%d.%d.%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR, WSH_VERSION_PATCH);
	working_version = strdup(buf);
	free(buf);
}

static bool check_any_valid(float* vals, int num)
{
	for (int i = 0; i < num; ++i)
	{
		if (vals[i] != -1)
			return true;
	}
	return false;
}

cJSON* wsh_serialize_line_json_v_0_0_1(WLine* line)
{
	
	unsigned long num_points = line->num;
	float*	vx	 = malloc(sizeof(float) * num_points);
	float*	vy	 = malloc(sizeof(float) * num_points);
	float*	pressure   = malloc(sizeof(float) * num_points);
	float*	tiltx      = malloc(sizeof(float) * num_points);
	float*	tilty      = malloc(sizeof(float) * num_points);
	float*	rots       = malloc(sizeof(float) * num_points);
	float*	times      = malloc(sizeof(float) * num_points);
	
	for (int k = 0; k < num_points; k++)
	{
		WPoint p    = line->data[k];
		vx[k]       = p.x;
		vy[k]       = p.y;
		pressure[k] = p.pressure;
		rots[k]     = p.rotation;
		tiltx[k]    = p.tilt_x;
		tilty[k]    = p.tilt_y;
		times[k]    = p.time;
	}
	
	cJSON* line_rec = cJSON_CreateObject();
	
	cJSON_AddBoolToObject(line_rec, "closed", line->closed);
	if (line->has_fill)
		cJSON_AddItemToObject(line_rec, "fill",
				      wsh_serial_json_serialize_color16(line->fill));
	if (line->has_stroke)
		cJSON_AddItemToObject(line_rec, "stroke",
				      wsh_serial_json_serialize_color16(line->stroke));
	
	int num = (int)num_points;
	cJSON_AddItemToObject(line_rec, "points_x",
			      cJSON_CreateFloatArray(vx, num));
	cJSON_AddItemToObject(line_rec, "points_y",
			      cJSON_CreateFloatArray(vy, num));
	if (check_any_valid(pressure, num))
		cJSON_AddItemToObject(line_rec, "pressure",
				      cJSON_CreateFloatArray(pressure, num));
	if (check_any_valid(rots, num))
		cJSON_AddItemToObject(line_rec, "rotation",
				      cJSON_CreateFloatArray(rots, num));
	if (check_any_valid(tiltx, num))
		cJSON_AddItemToObject(line_rec, "tilt_x",
				      cJSON_CreateFloatArray(tiltx, num));
	if (check_any_valid(tilty, num))
		cJSON_AddItemToObject(line_rec, "tilt_y",
				      cJSON_CreateFloatArray(tilty, num));
	if (check_any_valid(times, num))
		cJSON_AddItemToObject(line_rec, "time",
				      cJSON_CreateFloatArray(times, num));
	
	free(vx);
	free(vy);
	free(pressure);
	free(tiltx);
	free(tilty);
	free(rots);
	free(times);
	return line_rec;
}

cJSON* wsh_serialize_color_json_v_0_0_1(WColor col)
{
	float vals[4];
	vals[0] = col.r;
	vals[1] = col.g;
	vals[2] = col.b;
	vals[3] = col.a;
	
	cJSON* jv = cJSON_CreateFloatArray(vals, 4);
	return jv;
}

cJSON* wsh_serialize_color_json(WColor c)
{
	return wsh_serialize_color_json_v_0_0_1(c);
}

cJSON* wsh_serialize_line_json(WLine* line)
{
	return wsh_serialize_line_json_v_0_0_1(line);
}

cJSON* wsh_serialize_vec3_v_0_0_1(WVec3d* v)
{
	cJSON* r = cJSON_CreateObject();
	cJSON_AddNumberToObject(r, "x", v->x);
	cJSON_AddNumberToObject(r, "y", v->y);
	cJSON_AddNumberToObject(r, "z", v->z);
	return r;
}

cJSON* wsh_serialize_vec3(WVec3d* v)
{
	return wsh_serialize_vec3_v_0_0_1(v);
}

cJSON* wsh_serialize_transform_json_v_0_0_1(WTransform* trs)
{
	cJSON* root = cJSON_CreateObject();
	
	cJSON_AddItemToObject(root, "anchor", wsh_serialize_vec3(&trs->anchor));
	cJSON_AddItemToObject(root, "position",
			      wsh_serialize_vec3(&trs->position));
	cJSON_AddItemToObject(root, "rotation",
			      wsh_serialize_vec3(&trs->rotation));
	cJSON_AddItemToObject(root, "scale", wsh_serialize_vec3(&trs->scale));
	cJSON_AddNumberToObject(root, "opacity", trs->opacity);
	return root;
}

cJSON* wsh_serialize_transform_json(WTransform* trs)
{
	return wsh_serialize_transform_json_v_0_0_1(trs);
}

cJSON* wsh_serialize_object_json_v_0_0_1(WObject* obj)
{
	if (!obj)
		return NULL;
	if (DEBUG_SERIAL)
		wsh_log("Serialization test: %p", obj);
	cJSON* root = cJSON_CreateObject();
	
	// cJSON_AddItemToObject(root, "name", cJSON_CreateString("WObject"));
	cJSON_AddBoolToObject(root, "normalized", obj->normalized);
	cJSON_AddItemToObject(root, "transform",
			      wsh_serialize_transform_json(&obj->transform));
	
	// cJSON *line_records = malloc(num * sizeof(cJSON));
	// //cJSON_CreateArray();  cJSON *prev;

		unsigned long num = obj->num;
	if (DEBUG_SERIAL)
		wsh_log("Serializing %d lines.", num);
	cJSON* jlines = cJSON_CreateArray();
	
	for (int i = 0; i < num; ++i)
	{
		if (DEBUG_SERIAL)
			wsh_log("Serializing line %d", i);
		WLine* line = obj->lines[i];
		if (line)
		{
			
			cJSON* jline = wsh_serialize_line_json(line);
			cJSON_AddItemToArray(jlines, jline);
		}
	}
	
	cJSON_AddItemToObject(root, "lines", jlines);
	
	return root;
}

cJSON* wsh_serialize_sequence_json_v_0_0_1(WSequence* seq)
{
	
	cJSON* jseq    = cJSON_CreateObject();
	cJSON* jframes = cJSON_CreateArray();
	
	//int num = seq->num_frames;
	if (DEBUG_SERIAL)
		wsh_log("Have %d frames to serialize.", seq->num_frames);
	for (int i = 0; i < seq->num_frames; ++i)
	{
		WObject* fr    = seq->frames[i];
		cJSON*   fr_js = wsh_serialize_object_json(fr);
		cJSON_AddItemToArray(jframes, fr_js);
	}
	
	//	we are minimalists are we not?
	// cJSON_AddNumberToObject(jseq, "num_frames", seq->num_frames );
	
	if (seq->golden_frames)
	{
		if (seq->num_golden_frames != 0)
		{
			cJSON* jgf = cJSON_CreateArray();
			for (int i = 0; i < seq->num_golden_frames; ++i)
			{
				cJSON* n =
				cJSON_CreateNumber(seq->golden_frames[i]);
				cJSON_AddItemToArray(jgf, n);
			}
			
			cJSON_AddItemToObject(jseq, "golden_frames", jgf);
		}
	}
	
	cJSON_AddNumberToObject(jseq, "current_frame_index",
				seq->current_frame_index);
	cJSON_AddNumberToObject(jseq, "anim_duration", seq->anim_duration);
	cJSON_AddNumberToObject(jseq, "anim_type", seq->anim_type);
	cJSON_AddItemToObject(jseq, "frames", jframes);
	return jseq;
}

WSequence* wsh_serial_json_unserialize_sequence_v_0_0_1(cJSON* data)
{
	WSequence* seq = wsh_sequence_create();
	
	int    num;
	cJSON* jframes = cJSON_GetObjectItem(data, "frames");
	
	num = cJSON_GetArraySize(jframes);
	
	seq->num_frames		 = num;
	seq->current_frame_index = 0;  // TODO read this back in properly?
	seq->num_golden_frames   = 20; // don't care right now
	seq->golden_frames       = NULL;
	struct WObject** frames;
	
	frames		   = calloc(num, sizeof(struct WObject*));
	seq->current_frame = NULL;
	seq->parent	= NULL;
	
	seq->anim_duration = 1;
	cJSON* v	   = cJSON_GetObjectItem(data, "anim_duration");
	if (v)
	{
		seq->anim_duration = v->valuedouble;
		//cJSON_GetObjectItem(data, "anim_duration")->valuedouble;
	}
	seq->anim_type = 1;
	v	      = cJSON_GetObjectItem(data, "anim_type");
	
	if (v)
	{
		seq->anim_type = v->valueint;
	}
	
	// seq->frames = malloc(sizeof(WObject) * num
	if (DEBUG_SERIAL)
		wsh_log("%d frames to read.", num);
	for (int i = 0; i < num; ++i)
	{
		cJSON* jframe = cJSON_GetArrayItem(jframes, i);
		frames[i]     = wsh_serial_json_unserialize_object(jframe);
	}
	
	seq->frames	= frames;
	seq->current_frame = seq->frames[seq->current_frame_index];
	
	return seq;
}

WSequence* wsh_serial_json_unserialize_sequence_v_0_0_2(cJSON* data)
{
	return wsh_serial_json_unserialize_sequence_v_0_0_1(data);
}

WSequence* wsh_serial_json_unserialize_sequence(cJSON* data)
{
	if (0 == strcmp(working_version, "0.0.1"))
	{
		
		return wsh_serial_json_unserialize_sequence_v_0_0_1(data);
	}
	else if (0 == strcmp(working_version, "0.0.2"))
	{
		return wsh_serial_json_unserialize_sequence_v_0_0_2(data);
	}
	else
	{
		wsh_log("No code to handle this version or unable to read "
		       "version.\n");
		return NULL;
	}
	
	//we haven't revised sequence yet
	/*
	 if (0 == strcmp(working_version, "0.0.1")) {
	 } else {
	 printf("No code to handle this version or unable to read "
	 "version.\n");
	 return NULL;
	 }
	 */
}

cJSON* wsh_serialize_sequence_json(WSequence* seq)
{
	return wsh_serialize_sequence_json_v_0_0_1(seq);
}

cJSON* wsh_serialize_object_json(WObject* obj)
{
	return wsh_serialize_object_json_v_0_0_1(obj);
}

int wsh_serial_json_unserialize_meta_v0_0_1(cJSON* info, WDocumentMeta* meta)
{
	wsh_log("Unserializing meta!? 01");
	if (!info)
	{
		wsh_log("INFO weas null");
		return false;
	}
	//cJSON* info = cJSON_GetObjectItem(data, "info");
	cJSON* v = NULL;
	//if (info) {
	v = cJSON_GetObjectItem(info, "version");
	if (v)
		meta->version_string = v->valuestring;
	
	v = cJSON_GetObjectItem(info, "uuid");
	if (v)
		meta->uuid = v->valuestring;
	//}
	// else {
	//	printf("Error, no INFO found! is this a valid v0_0_1 object?\n");
	//	printf("//------------------\n%s//---------------\n", cJSON_Print(info));
	//	return false;
	//}
	
	return true;
}

cJSON* wsh_serial_json_serialize_meta_v0_0_1(WDocumentMeta* meta)
{
	cJSON* ret = cJSON_CreateObject();
	
	return ret;
}

const char* fps_to_string(double v)
{
	int vi = (int)v;
	
	char* buf = calloc(16, sizeof(char));
	
	if (v != vi)
	{
		double frac = v - vi;
		sprintf(buf, "%d.%f\n", vi, frac);
		//we got a floater
		wsh_log("floating point.");
	}
	else
	{
		printf("Integer.\n");
		wsh_log(buf, "%d", vi);
	}
	
	wsh_log("buf:[%s]", buf);
	
	return buf;
}

cJSON* wsh_serial_json_serialize_meta_v0_0_2(WDocumentMeta* meta)
{
	
	cJSON* jmeta = cJSON_CreateObject();
	
	//	canvas
	cJSON* canvas = cJSON_CreateObject();
	cJSON_AddNumberToObject(canvas, "width", meta->canvas_width);
	cJSON_AddNumberToObject(canvas, "height", meta->canvas_height);
	cJSON_AddItemToObject(jmeta, "canvas", canvas);
	
	//	info
	cJSON* info = cJSON_CreateObject();
	if (working_version == NULL)
		set_working_version();
	
	cJSON_AddStringToObject(info, "version", working_version);
	cJSON_AddStringToObject(info, "path", meta->path);
	cJSON_AddStringToObject(info, "uuid", meta->uuid);
	cJSON_AddStringToObject(info, "ref", meta->ref);
	
	if (!meta->fps_repr)
	{
		meta->fps_repr = fps_to_string(meta->fps);
	}
	cJSON_AddStringToObject(info, "fps", meta->fps_repr);
	
	//	todo: add fps
	cJSON_AddItemToObject(jmeta, "info", info);
	//cJSON_AddItemToObject(ret, t, )
	
	return jmeta;
}



int wsh_serial_json_unserialize_meta_v0_0_2(cJSON* data, WDocumentMeta* meta)
{
	wsh_log("Unserializing meta!? 02");
	cJSON* session = cJSON_GetObjectItem(data, "session");
	cJSON* plugins = cJSON_GetObjectItem(data, "plugins");
	cJSON* canvas  = cJSON_GetObjectItem(data, "canvas");
	cJSON* info    = cJSON_GetObjectItem(data, "info");
	
	cJSON* v = NULL;
	if (canvas)
	{
		v = cJSON_GetObjectItem(canvas, "width");
		if (v)
			meta->canvas_width = v->valueint;
		
		v = cJSON_GetObjectItem(canvas, "height");
		if (v)
			meta->canvas_height = v->valueint;
	}
	if (info)
	{
		v = cJSON_GetObjectItem(info, "fps");
		if (v)
		{
			meta->fps_repr = v->valuestring;
		}
		else
		{
			meta->fps_repr = "29.97";
		}
		
		v = cJSON_GetObjectItem(info, "version");
		if (v)
			meta->version_string = v->valuestring;
		v = cJSON_GetObjectItem(info, "path");
		if (v)
			meta->path = v->valuestring;
		v = cJSON_GetObjectItem(info, "uuid");
		if (v)
			meta->uuid = v->valuestring;
	}
	
	//	todo: add plugin and event decoding coder
	return true;
}

const char* wsh_serial_json_document_serialize_v002(WDocument* doc, const char* version_string)
{
	
	cJSON* root = cJSON_CreateObject();
	cJSON* data = cJSON_CreateObject();
	
	cJSON* meta = wsh_serial_json_serialize_meta_v0_0_2(&doc->meta);
	cJSON_AddItemToObject(root, "meta", meta);
	
	cJSON* sequence = wsh_serialize_sequence_json(doc->sequence.src);
	cJSON_AddItemToObject(data, "sequence", sequence);
	cJSON_AddItemToObject(root, "data", data);
	
	//cJSON* meta = cJSON_CreateObject();
	
	//cJSON_AddItemToObject(root, "meta", doc->meta);
	//cJSON* info = cJSON_CreateObject();
	/*
	 cJSON_AddStringToObject(info, "version", strdup(version_string));
	 
	 if (doc->path)
	 cJSON_AddStringToObject(info, "path", strdup(doc->path));
	 
	 if (doc->ref)
	 cJSON_AddStringToObject(info, "ref", strdup(doc->ref));
	 if (doc->uuid)
	 cJSON_AddStringToObject(info, "uuid", doc->uuid);
	 
	 if (doc->sequence.src) {
	 cJSON* jseq = wsh_serialize_sequence_json(doc->sequence.src);
	 cJSON_AddItemToObject(data, "sequence", jseq);
	 }
	 cJSON_AddItemToObject(meta, "info", info);
	 */
	
	return cJSON_Print(root);
}

const char* wsh_serial_json_document_serialize_v001(WDocument* doc, const char* version_string)
{
	
	if (DEBUG_SERIAL)
		wsh_log("Serialization doc: %p", doc);
	
	// printf("//------------------------\n\n\n\n %s",
	// W_LIBWSH_SVER(ASDF));
	
	cJSON* root = cJSON_CreateObject();
	
	cJSON* info = cJSON_CreateObject();
	
	// printf("buf : %s\n", buf );
	
	cJSON_AddStringToObject(info, "version", version_string);
	
	/*if (doc->path)
	 cJSON_AddStringToObject(info, "path", strdup(doc->path));
	 
	 if (doc->ref)
	 cJSON_AddStringToObject(info, "ref", strdup(doc->ref));
	 */
	
	cJSON* jmeta = wsh_serial_json_serialize_meta_v0_0_1(&doc->meta);
	cJSON_AddItemToObject(root, "meta", jmeta);
	
	/*
	 if (doc->meta)
	 cJSON_AddItemToObject(root, "meta", doc->meta);
	 
	 if (doc->uuid == NULL) {
	 printf("hack to add a UUID now, dumb, should always add when doc created\n");
	 //doc->uuid
	 }
	 cJSON_AddStringToObject(info, "uuid", doc->uuid);
	 
	 cJSON_AddItemToObject(root, "info", info);
	 */
	if (doc->sequence.src)
	{
		cJSON* jseq = wsh_serialize_sequence_json(doc->sequence.src);
		
		cJSON_AddItemToObject(root, "sequence", jseq);
		
		//cJSON_ReplaceItemInObject(root, "sequence", jseq);
	}
	const char* result = cJSON_Print(root);
	return result;
}

const char* wsh_serial_json_document_serialize(WDocument* doc)
{
	char* buf = calloc(128, sizeof(char));
	sprintf(buf, "%d.%d.%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR,
		WSH_VERSION_PATCH);
	
	working_version = strdup(buf);
	fixup_old_style_version_string(working_version);
	
	if (0 == strcmp(working_version, "0.0.1"))
	{
		wsh_log("Serialize: %s", working_version);
		return wsh_serial_json_document_serialize_v001(doc, buf);
	}
	else if (0 == strcmp(working_version, "0.0.2"))
	{
		wsh_log("Serialize: %s", working_version);
		return wsh_serial_json_document_serialize_v002(doc, buf);
	}
	else
	{
		wsh_log("NO known code paths to serialize this format: %s", buf);
	}
	free(buf);
	
	return NULL;
}

void wsh_serialize_line(WObject* obj, FILE* f)
{
}

void wsh_serialize_point(WPoint* obj, FILE* f)
{
}

#pragma mark unserialize

WLine* w_unserialize_line_json_v_0_0_1(cJSON* data)
{
	
	// printf("%d points.\n", num);
	
	WLine* line = wsh_line_create();
	
	cJSON* jx	= cJSON_GetObjectItem(data, "points_x");
	cJSON* jy	= cJSON_GetObjectItem(data, "points_y");
	cJSON* jtime     = cJSON_GetObjectItem(data, "time");
	cJSON* jpressure = cJSON_GetObjectItem(data, "pressure");
	cJSON* jrotation = cJSON_GetObjectItem(data, "rotation");
	cJSON* jtiltx    = cJSON_GetObjectItem(data, "tilt_x");
	cJSON* jtilty    = cJSON_GetObjectItem(data, "tilt_y");
	
	int num = cJSON_GetArraySize(jx);
	if (num > 100000)
	{
		wsh_log("Something went WAY wrong (probably)");
	}
	if (DEBUG_SERIAL)
		wsh_log("%d points.", num);
	
	for (int i = 0; i < num; ++i)
	{
		WPoint p;
		wsh_point_zero(&p);
		p.x	= cJSON_GetArrayItem(jx, i)->valuedouble;
		p.y	= cJSON_GetArrayItem(jy, i)->valuedouble;
		p.pressure = 0;
		p.tilt_x = p.tilt_y = p.rotation = p.time = 0;
		if (jtime)
			p.time = cJSON_GetArrayItem(jtime, i)->valuedouble;
		if (jpressure)
			p.pressure =
			cJSON_GetArrayItem(jpressure, i)->valuedouble;
		if (jtiltx)
			p.tilt_x = cJSON_GetArrayItem(jtiltx, i)->valuedouble;
		if (jtilty)
			p.tilt_y = cJSON_GetArrayItem(jtilty, i)->valuedouble;
		if (jrotation)
			p.rotation =
			cJSON_GetArrayItem(jrotation, i)->valuedouble;
		
		wsh_line_add_point(line, p);
	}
	
	if (line->num > 100000000)
	{
		wsh_log("what the FACK");
	}
	cJSON* stroke = cJSON_GetObjectItem(data, "stroke");
	if (stroke != NULL)
	{
		line->has_stroke = true;
		// line->stroke.r = cJSON_GetArrayItem(stroke,0);
		// cJSON* test = cJSON_GetArrayItem(stroke, 0);
		line->stroke.r = cJSON_GetArrayItem(stroke, 0)->valuedouble;
		line->stroke.g = cJSON_GetArrayItem(stroke, 1)->valuedouble;
		line->stroke.b = cJSON_GetArrayItem(stroke, 2)->valuedouble;
		line->stroke.a = cJSON_GetArrayItem(stroke, 3)->valuedouble;
	}
	else
	{
		wsh_log("Error loading stroke!");
		line->has_stroke = true;
		line->stroke.r   = 0;
		line->stroke.g   = 0;
		line->stroke.b   = 0;
		line->stroke.a   = 0;
	}
	line->closed = cJSON_GetObjectItem(data, "closed")->valueint;
	
	wsh_line_calc_bounds(line);
	// printf("done?\n");
	return line;
}

WLine* w_unserialize_line_json(cJSON* data)
{
	return w_unserialize_line_json_v_0_0_1(data);
}

WObject* wsh_serial_json_unserialize_object_v_0_0_1(cJSON* data)
{
	cJSON* jlines = cJSON_GetObjectItem(data, "lines");
	int    num    = cJSON_GetArraySize(jlines);
	
	WObject* obj = wsh_object_create(NULL);
	
	obj->normalized = cJSON_GetObjectItem(data, "normalized")->valueint;

	for (int i = 0; i < num; ++i)
	{
		cJSON* jl   = cJSON_GetArrayItem(jlines, i);
		WLine* line = w_unserialize_line_json(jl);
		
		wsh_object_add_line(obj, line);
	}
	
	if (DEBUG_SERIAL)
		wsh_log("%d lines.", num);
	return obj;
}

WObject* wsh_serial_json_unserialize_object(cJSON* data)
{
	return wsh_serial_json_unserialize_object_v_0_0_1(data);
}
/*
 void* wsh_serial_document_unserialize_generic(const char* path)
 {
 return wsh_serial_document_unserialize(path);
 }
 */
WDocument* wsh_serial_document_unserialize_v002(const char* path, cJSON* root)
{
	WDocument* doc = wsh_document_create();
	
	cJSON* meta = cJSON_GetObjectItem(root, "meta");
	if (meta)
	{
		int res = wsh_serial_json_unserialize_meta_v0_0_2(meta, &doc->meta);
		if (!res)
		{
			wsh_log("Error reading meta!");
		}
		/*doc->meta   = meta;
		 cJSON* info = cJSON_GetObjectItem(meta, "info");
		 
		 cJSON* jval = cJSON_GetObjectItem(info, "path");
		 if (jval)
		 doc->path = jval->string;
		 
		 jval = cJSON_GetObjectItem(info, "uuid");
		 if (jval)
		 doc->uuid = jval->string;
		 
		 jval = cJSON_GetObjectItem(info, "ref");
		 if (jval)
		 doc->ref = jval->string;
		 */
	}
	else
	{
		wsh_log("ALERT NO META");
		//doc->meta = cJSON_CreateObject();
	}
	
	cJSON* data       = cJSON_GetObjectItem(root, "data");
	cJSON* jseq       = cJSON_GetObjectItem(data, "sequence");
	doc->sequence.src = wsh_serial_json_unserialize_sequence(jseq);
	
	return doc;
}

WDocument* wsh_serial_document_unserialize_v001(const char* path, cJSON* root)
{
	wsh_log("Unserializing at v001");
	
	WDocument* doc = wsh_document_create();
	
	cJSON*     jseq = cJSON_GetObjectItem(root, "sequence");
	WSequence* seq  = wsh_serial_json_unserialize_sequence(jseq);
	
	if (seq)
	{
		doc->sequence.src = seq;
	}
	else
	{
		wsh_log("Was unable to decode any sequence!");
		cJSON_Delete(root);
		wsh_document_destroy(doc);
		return NULL;
	}
	
	cJSON* jval = cJSON_GetObjectItem(root, "info");
	if (jval)
	{
		
		wsh_serial_json_unserialize_meta_v0_0_1(jval, &doc->meta);
	}
	else
	{
		jval = cJSON_GetObjectItem(root, "meta");
		if (jval)
		{
			wsh_serial_json_unserialize_meta_v0_0_1(jval, &doc->meta);
		}
	}
	
	cJSON_Delete(root);
	
	return doc;
}

/*
 
 
 uhhhh I didn't realize atof existed cuz im a dope
 static int index_of_char(const char* sdata)
 {
 //int  position = 0;
 char c	= '.';
 char* ptr = strchr(sdata, c);
 if ( !ptr )
 {
 return -1;
 }
 int position = ptr- sdata;
 
 //char* s = while (*(s + position++) != c)
 //	;
 printf("%d\n", position);
 return position;
 }
 */

static void wsh_serial_json_postprocess_document(WDocument* doc)
{
	//	read the fps_repr into the fps
	////printf("Reading fps repr: [%s]\n", doc->meta.fps_repr);
	//if (doc->meta.fps_repr != NULL)
	//{
	//	doc->meta.fps = strtod(doc->meta.fps_repr, (char**)NULL);
	
	/*int pos = index_of_char(doc->meta.fps_repr);
	 if (pos == -1) {
	 printf("parsing an integer fps val\n");
	 int fps = atoi(doc->meta.fps_repr);
	 if ( (int)doc->meta.fps != fps )
	 {
	 printf("Setting fps to as read by document.\n");
	 doc->meta.fps = fps;
	 }else{
	 printf("Not doing shit.\n");
	 }
	 } else {
	 
	 printf("parsing a float fps val\n");
	 //int frac = pos - 1;
	 //char* buf = calloc(16, sizeof(char));
	 doc->meta.fps = atof(doc->meta.fps_repr);
	 printf("[%f]\n", doc->meta.fps);
	 }
	 */
	//}
}


WDocument* wsh_serial_json_document_unserialize(const char* path)
{
	WDocument* doc  = NULL;
	char*      data = w_read_file_as_text_nc(path);
	cJSON*     meta = NULL;
	if (!data)
	{
		//char buf[256];
		wsh_log("An error occurred reading text file: %s", path);
		// l_warning(buf);
		//free(data);
		return NULL;
	}
	
	cJSON* root = cJSON_Parse(data);
	
	//	TODO read the version number and parse accordingly
	cJSON* info = cJSON_GetObjectItem(root, "info");
	if (info)
	{
		//v001 ?
		cJSON* version = cJSON_GetObjectItem(info, "version");
		if (version)
		{
			working_version = strdup(version->valuestring);
			fixup_old_style_version_string(working_version);
			wsh_log("version detected: %s", working_version);
		}
		doc = wsh_serial_document_unserialize_v001(path, root);
	}
	else
	{
		wsh_log("No 'info' suggesting schema 2 or higher, checking for meta.: %s", working_version);
		
		meta = cJSON_GetObjectItem(root, "meta");
		if (!meta)
		{
			wsh_log("NO meta decoded! what do?");
		}
		else
		{
			
			cJSON* info = cJSON_GetObjectItem(meta, "info");
			if (info)
			{
				cJSON* jv = cJSON_GetObjectItem(info, "version");
				//char*  doc_version = jv->valuestring;
				if ( jv ) working_version = strdup(jv->valuestring);
				fixup_old_style_version_string(working_version);
				if (0 == strcmp(working_version, "0.0.2"))
				{
					doc = wsh_serial_document_unserialize_v002(path, root);
				}
				else
				{
					wsh_log("Unknown version number! %s", working_version);
				}
			}
		}
	}
	
	//if (meta)
	//{
	
	wsh_serial_json_postprocess_document(doc);
	//}
	/*
	 cJSON* version = cJSON_GetObjectItem(info, "version");
	 if (version) {
	 working_version = version->valuestring;
	 if (DEBUG_SERIAL)
	 wsh_log("version detected: %s", working_version);
	 }
	 */
	
	//	todo:
	// 	for now, we depend on the sequence for our doc structure.  this
	// may change.
	
	free(data);
	//cJSON_Delete(root);
	
	//cJSON* meta = (cJSON*) doc->meta;
	
	//cJSON* tval = cJSON_GetObjectItem(meta, "plugins");
	//if ( tval )
	//	printf("plugin type: %d\n", tval->type);
	return doc;
}

#endif // end WSH_ENABLE_SERIAL_BACKEND_JSON
