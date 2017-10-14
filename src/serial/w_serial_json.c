
//  w_serial_json.c
//  w_serial_json
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "w_serial_json.h"

//#ifndef RPLATFORM_IOS

#include "cJSON.h"
#include <string.h>

#include <r4/r4.h>

/*
#define REGISTER(ns, id, type)                                          \
inline Inst* type##Activate() { return new type(); }                 \
extern bool type##temp

#define INSTANTIATE(ns, id, type)                                       \
Inst* type##Activate();                                              \
bool type##temp = RegisterType(ns << 8 | id, &type##Activate)
*/


//http://stackoverflow.com/questions/860273/macro-producing-macros-in-c

//#define make_macro(name,...)  name##_fn(name##_info, __VA_ARGS__)
const char* working_version = NULL;

#define DEBUG_SERIAL false

cJSON* w_serialize_object_json(WObject* obj );
cJSON* w_serialize_sequence_json(WSequence* seq );
cJSON* w_serialize_line_json(WLine* line);
cJSON* w_serialize_color_json(WColor col);


cJSON* w_serialize_object_json_v_1(WObject* obj );
cJSON* w_serialize_sequence_json_v_1(WSequence* seq );
cJSON* w_serialize_line_json_v_1(WLine* line);
cJSON* w_serialize_color_json_v_1(WColor col);

static bool check_any_valid(float* vals, int num)
{
	for ( int i = 0 ;i < num; ++i )
	{
		if ( vals[i] != -1 )
			return true;
	}
	return false;
}


cJSON*
w_serialize_line_json_v_1(WLine* line)
{

	unsigned long num_points = line->num;
	float* vx = malloc(sizeof(float) * num_points);
	float* vy = malloc(sizeof(float) * num_points);
	float* pressure = malloc(sizeof(float) * num_points);
	float* tiltx = malloc(sizeof(float) * num_points);
	float* tilty = malloc(sizeof(float) * num_points);
	float* rots = malloc(sizeof(float) * num_points);
	float* times = malloc(sizeof(float) * num_points);


	for ( int k=0; k < num_points; k++)
	{
		WPoint p = line->data[k];
		vx[k]		= p.x;
		vy[k]		= p.y;
		pressure[k] = p.pressure;
		rots[k]		= p.rotation;
		tiltx[k]	= p.tilt_x;
		tilty[k]	= p.tilt_y;
		times[k]	= p.time;
	}
	
	cJSON *line_rec = cJSON_CreateObject();

	cJSON_AddBoolToObject(line_rec, "closed", line->closed );
	if ( line->has_fill )
		cJSON_AddItemToObject(line_rec, "fill", w_serialize_color_json(line->fill));
	if ( line->has_stroke )
		cJSON_AddItemToObject(line_rec, "stroke", w_serialize_color_json(line->stroke));

	int num = (int)num_points;
	cJSON_AddItemToObject(line_rec, "points_x", cJSON_CreateFloatArray(vx, num));
	cJSON_AddItemToObject(line_rec, "points_y", cJSON_CreateFloatArray(vy, num));
	if ( check_any_valid( pressure, num ))
		cJSON_AddItemToObject(line_rec, "pressure", cJSON_CreateFloatArray(pressure, num));
	if ( check_any_valid( rots, num ))
		cJSON_AddItemToObject(line_rec, "rotation", cJSON_CreateFloatArray(rots, num));
	if ( check_any_valid( tiltx, num ))
		cJSON_AddItemToObject(line_rec, "tilt_x", cJSON_CreateFloatArray(tiltx, num ));
	if ( check_any_valid( tilty, num ))
		cJSON_AddItemToObject(line_rec, "tilt_y", cJSON_CreateFloatArray(tilty,num));
	if ( check_any_valid( times, num ))
		cJSON_AddItemToObject(line_rec, "time", cJSON_CreateFloatArray(times, num));

	free(vx);
	free(vy);
	free(pressure);
	free(tiltx);
	free(tilty);
	free(rots);
	free(times);
	return line_rec;
}

cJSON*			w_serialize_color_json_v_1(WColor col)
{
	float vals[4];
	vals[0] = col.r;
	vals[1] = col.g;
	vals[2] = col.b;
	vals[3] = col.a;

	cJSON* jv = cJSON_CreateFloatArray(vals, 4);
	return jv;
}

cJSON*			w_serialize_color_json(WColor c)
{
	return w_serialize_color_json_v_1(c);
}

cJSON*			w_serialize_line_json(WLine* line)
{
	return w_serialize_line_json_v_1(line);
}

cJSON*			w_serialize_vec3_v_1(WVec3d* v )
{
	cJSON* r = cJSON_CreateObject();
	cJSON_AddNumberToObject(r, "x", v->x );
	cJSON_AddNumberToObject(r, "y", v->y );
	cJSON_AddNumberToObject(r, "z", v->z );
	return r;
}

cJSON*			w_serialize_vec3(WVec3d* v)
{
	return w_serialize_vec3_v_1(v);
}

cJSON*			w_serialize_transform_json_v_1(WTransform* trs)
{
	cJSON* root = cJSON_CreateObject();

	cJSON_AddItemToObject(root, "anchor", w_serialize_vec3(&trs->anchor));
	cJSON_AddItemToObject(root, "position", w_serialize_vec3(&trs->position));
	cJSON_AddItemToObject(root, "rotation", w_serialize_vec3(&trs->rotation));
	cJSON_AddItemToObject(root, "scale", w_serialize_vec3(&trs->scale));
	cJSON_AddNumberToObject(root, "opacity", trs->opacity);
	return root;

}


cJSON*			w_serialize_transform_json(WTransform* trs)
{
	return w_serialize_transform_json_v_1(trs);

}

cJSON*			w_serialize_object_json_v_1(WObject* obj)
{
	if(!obj)
		return NULL;
	if( DEBUG_SERIAL )
		printf("Serialization test: %p\n", obj);
	cJSON * root = cJSON_CreateObject();


	//cJSON_AddItemToObject(root, "name", cJSON_CreateString("WObject"));
	cJSON_AddBoolToObject(root, "normalized", obj->normalized );
	cJSON_AddItemToObject(root, "transform", w_serialize_transform_json(&obj->transform));

	//cJSON *line_records = malloc(num * sizeof(cJSON)); //cJSON_CreateArray();
	//cJSON *prev;

	int num = obj->num_lines;
	if( DEBUG_SERIAL )
		printf("Serializing %d lines.\n", num);
	cJSON *jlines = cJSON_CreateArray();

	for ( int i = 0 ; i < num; ++i )
	{
		if( DEBUG_SERIAL )
			printf("Serializing line %d\n", i);
		WLine* line = obj->lines[i];
		if ( line )
		{

			cJSON* jline = w_serialize_line_json(line);
			cJSON_AddItemToArray(jlines, jline);
		}
	}


	cJSON_AddItemToObject(root, "lines", jlines);

	return root;
}

cJSON*			w_serialize_sequence_json_v_1(WSequence* seq )
{

	cJSON * jseq = cJSON_CreateObject();
	cJSON * jframes = cJSON_CreateArray();

	int num = seq->num_frames;
	if( DEBUG_SERIAL )
		printf("Have %d frames to serialize.\n", num);
	for ( int i = 0 ; i < seq->num_frames; ++i )
	{
		WObject* fr = seq->frames[i];
		cJSON* fr_js = w_serialize_object_json(fr);
		cJSON_AddItemToArray(jframes, fr_js);

	}

	//	we are minimalists are we not?
	//cJSON_AddNumberToObject(jseq, "num_frames", seq->num_frames );

	if ( seq->golden_frames )
	{
		if ( seq->num_golden_frames != 0 )
		{
			cJSON* jgf = cJSON_CreateArray();
			for ( int i = 0 ; i < seq->num_golden_frames ; ++i )
			{
				cJSON* n = cJSON_CreateNumber(seq->golden_frames[i]);
				cJSON_AddItemToArray(jgf, n);
			}

			cJSON_AddItemToObject(jseq, "golden_frames", jgf);
		}
	}

	cJSON_AddNumberToObject(jseq, "current_frame_index", seq->current_frame_index);
	cJSON_AddNumberToObject(jseq, "anim_duration", seq->anim_duration );
	cJSON_AddNumberToObject(jseq, "anim_type", seq->anim_type );
	cJSON_AddItemToObject(jseq, "frames", jframes);
	return jseq;
}



WSequence*		w_unserialize_sequence_json_v_1(cJSON* data )
{
	WSequence* seq = w_sequence_create();

	int num;
	cJSON* jframes = cJSON_GetObjectItem(data, "frames");


	num = cJSON_GetArraySize(jframes);

	seq->num_frames = num;
	seq->current_frame_index = 0; // TODO read this back in properly?
	seq->num_golden_frames = 20; // don't care right now
	seq->golden_frames = NULL;
	struct WObject** frames;

	frames =  calloc(num, sizeof(struct WObject*) );
	seq->current_frame = NULL;
	seq->parent = NULL;

	seq->anim_duration = cJSON_GetObjectItem(data, "anim_duration")->valuedouble;
	seq->anim_type = cJSON_GetObjectItem(data,"anim_type")->valueint;


	//seq->frames = malloc(sizeof(WObject) * num
	if( DEBUG_SERIAL )
		printf("%d frames to read.\n", num );
	for ( int i = 0 ; i < num; ++i )
	{
		cJSON* jframe = cJSON_GetArrayItem(jframes, i);
		frames[i] = w_unserialize_object_json(jframe);
	}

	seq->frames = frames;
	return seq;

}

WSequence*		w_unserialize_sequence_json(cJSON* data)
{
	if ( 0 == strcmp(working_version, "0_0_1"))
	{
		return w_unserialize_sequence_json_v_1(data);
	}else{
		printf("No code to handle this version or unable to read version.\n");
		return NULL;
	}

}

cJSON*			w_serialize_sequence_json(WSequence* seq )
{
	return w_serialize_sequence_json_v_1(seq);
}

cJSON*			w_serialize_object_json(WObject* obj )
{
	return w_serialize_object_json_v_1(obj);
}

const char*		w_document_serialize_json(WDocument* doc)
{

	if (DEBUG_SERIAL)
		printf("Serialization doc: %p\n", doc);

	//printf("//------------------------\n\n\n\n %s", W_LIBWASH_SVER(ASDF));




	cJSON * root = cJSON_CreateObject();

	cJSON*	info = cJSON_CreateObject();



	char buf[128];
	sprintf(buf, "%d_%d_%d", WSH_V_MAJOR, WSH_V_MINOR, WSH_V_PATCH);
	//printf("buf : %s\n", buf );

	cJSON_AddStringToObject(info, "version", buf );


	if ( doc->path )
		cJSON_AddStringToObject(info, "path", doc->path);

	if ( doc->ref )
		cJSON_AddStringToObject(info, "ref", doc->ref );

	if( doc->meta)
		cJSON_AddItemToObject(root, "meta", doc->meta );

	//if(doc->meta)
//#ifdef R4_PLATFORM_IOS
	cJSON_AddStringToObject(info, "uuid", doc->uuid);
//#endif

	cJSON_AddItemToObject(root, "info", info);

	/*
	if ( doc->art.src )
	{
		cJSON * obj = w_serialize_object_json(doc->art.src);
		cJSON_AddItemToObject(root, "art", obj);
	}
	 */

	if ( doc->sequence.src )
	{
		cJSON * obj = w_serialize_sequence_json(doc->sequence.src);
		cJSON_AddItemToObject(root, "sequence", obj);
	}


	const char* result = cJSON_Print(root);
	return result;


}


void w_serialize_line(WObject* obj, FILE* f)
{


}

void w_serialize_point(WPoint* obj, FILE* f)
{


}


#pragma mark unserialize


WLine*			w_unserialize_line_json_v_1(cJSON* data )
{

	//printf("%d points.\n", num);

	WLine* line = w_line_create();

	cJSON* jx = cJSON_GetObjectItem(data, "points_x");
	cJSON* jy = cJSON_GetObjectItem(data, "points_y");
	cJSON* jtime = cJSON_GetObjectItem(data, "time");
	cJSON* jpressure = cJSON_GetObjectItem(data, "pressure");
	cJSON* jrotation = cJSON_GetObjectItem(data, "rotation");
	cJSON* jtiltx = cJSON_GetObjectItem(data, "tilt_x");
	cJSON* jtilty = cJSON_GetObjectItem(data, "tilt_y");

	int num = cJSON_GetArraySize(jx);

	if (DEBUG_SERIAL)
		printf("%d points.\n", num);


	for ( int i = 0 ; i < num; ++i )
	{
		WPoint p;
		p.x = cJSON_GetArrayItem(jx, i)->valuedouble;
		p.y = cJSON_GetArrayItem(jy, i)->valuedouble;
		p.pressure = 0;
		p.tilt_x = p.tilt_y = p.rotation = p.time = 0;
		if ( jtime)
			p.time = cJSON_GetArrayItem(jtime, i)->valuedouble;
		if (jpressure )
			p.pressure = cJSON_GetArrayItem(jpressure, i)->valuedouble;
		if ( jtiltx )
			p.tilt_x = cJSON_GetArrayItem(jtiltx, i)->valuedouble;
		if ( jtilty )
			p.tilt_y = cJSON_GetArrayItem(jtilty, i)->valuedouble;
		if (jrotation )
			p.rotation = cJSON_GetArrayItem(jrotation, i)->valuedouble;


		w_line_add_point(line, p);

	}
	
	cJSON* stroke = cJSON_GetObjectItem(data, "stroke");
	if ( stroke != NULL )
	{
		line->has_stroke = true;
		//line->stroke.r = cJSON_GetArrayItem(stroke,0);
		//cJSON* test = cJSON_GetArrayItem(stroke, 0);
		line->stroke.r = cJSON_GetArrayItem(stroke, 0)->valuedouble;
		line->stroke.g = cJSON_GetArrayItem(stroke, 1)->valuedouble;
		line->stroke.b = cJSON_GetArrayItem(stroke, 2)->valuedouble;
		line->stroke.a = cJSON_GetArrayItem(stroke, 3)->valuedouble;

	}
	line->closed = cJSON_GetObjectItem(data, "closed")->valueint;

	//printf("done?\n");
	return line;

}

WLine*			w_unserialize_line_json(cJSON* data )
{
	return w_unserialize_line_json_v_1(data);
}

WObject*		w_unserialize_object_json_v_1(cJSON* data )
{
	cJSON* jlines = cJSON_GetObjectItem(data, "lines");
	int num = cJSON_GetArraySize(jlines);

	WObject* obj = w_object_create(NULL);

	obj->normalized = cJSON_GetObjectItem(data, "normalized")->valueint;

	//obj->lines = malloc(sizeof(WLine) * obj->num_lines);

	for ( int i = 0 ; i < num; ++i )
	{
		cJSON* jl = cJSON_GetArrayItem(jlines, i);
		WLine* line =  w_unserialize_line_json(jl);

		w_object_add_line(obj, line);
	}


	if (DEBUG_SERIAL)
		printf("%d lines.\n", num);
	return obj;
}

WObject*		w_unserialize_object_json(cJSON* data)
{
	return w_unserialize_object_json_v_1(data);
}


WDocument*		w_document_unserialize_json(const char* path )
{
	char* data = w_read_file_as_text_nc(path);

	if ( !data ){
		char buf[256];
		sprintf( buf, "An error occurred reading text file: %s\n", path);
		//l_warning(buf);
		free(data);
		return NULL;
	}

	WDocument* doc = w_document_create();

	cJSON * root = cJSON_Parse(data);

	//	TODO read the version number and parse accordingly
	cJSON* info = cJSON_GetObjectItem(root, "info");

	cJSON* version = cJSON_GetObjectItem(info, "version");
	if( version )
	{
		working_version = version->valuestring;
		if (DEBUG_SERIAL)
			printf("version detected: %s\n", working_version);
	
	}
	cJSON* jseq = cJSON_GetObjectItem(root,"sequence");

	WSequence* seq = w_unserialize_sequence_json(jseq);
	//	todo:
	// 	for now, we depend on the sequence for our doc structure.  this may change.
	if ( seq )
	{
		free(data);
		doc->sequence.src = seq;
		cJSON_Delete(root);
		
	}else{
		printf("Was unable to decode any sequence!\n");
		cJSON_Delete(root);
		w_document_destroy(doc);
		doc = NULL;
	}

	return doc;
}


//#endif

