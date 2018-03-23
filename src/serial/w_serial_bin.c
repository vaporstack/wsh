
//  w_serial_bin.c
//  w_serial_bin
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "w_serial_bin.h"

/*
#include "w_serial.h"
#include <binn/binn.h>
#include <string.h>


#include "../io/w_io.h"

void* w_document_serialize_bin_v_1(void) { return NULL; }

void* w_document_unserialize_bin_v_1(void) { return NULL; }

WSequence* w_unserialize_sequence_bin(binn* bseq)
{
	WSequence* seq = w_sequence_create();
	binn_object_get_int32(bseq, "num_frames", &seq->num_frames);
	binn_object_get_int32(bseq, "current_frame_index",
			      &seq->current_frame_index);
	binn_object_get_int32(bseq, "num_golden_frames",
			      &seq->num_golden_frames);
	binn_object_get_double(bseq, "anim_duration", &seq->anim_duration);
	binn_object_get_int32(bseq, "anim_type", &seq->anim_type);
	int num = seq->num_frames;
	printf("%d frames to read.\n", num);

	binn* bframes = binn_list();
	binn_object_get_list(bframes, "frames", (void*)bframes);

	for (int i = 0; i < num; ++i) {
		w_sequence_frame_add(seq);
		WObject* fr = seq->frames[i];
		// binn* bobj = binn_list_get_(bframes,
		// seq->frames[i] = w_unserialize_object_bin(
		// w_unserialize_object_bin()
	}

	return seq;
}

// WObject* w_unserialize_object_bin(FILE*);
WDocument* w_document_unserialize_bin(const char* path)
{

	binn* obj;

	long  buf_len = 0;
	void* mydata  = NULL;
	mydata	= w_read_file_as_bin(path, &buf_len);
	// if ( res != 0 )
	//{
	//	printf("Couldn't read file, file had len 0 or couldn't be
	// opened\n"); 	return NULL;
	//}
	// printf("Read %lu bytes\n%s\n", buf_len, mydata);
	for (int i = 0; i < buf_len; ++i) {
		// printf("%x", mydata[i]);
	}
	obj = binn_open(mydata);
	if (obj == 0) {
		printf("binn failed to read the data.");
		return NULL;
	}

	binn* info = binn_object_object(obj, "info");

	binn* bseq = binn_object_object(obj, "sequence");

	WDocument* doc = w_document_create();
	doc->meta.uuid      = binn_object_str(info, "uuid");
	doc->meta.version   = binn_object_str(info, "version");

	doc->sequence.src = w_unserialize_sequence_bin(bseq);
	binn_free(obj);

	return doc;
}

binn* w_serialize_transform_bin(WTransform* trans) { return NULL; }

binn* w_serialize_line_bin(WLine* l)
{
	binn* bobj = binn_object();

	unsigned long long num = l->num;
	printf("serializing %llu points\n", num);
	binn_object_set_bool(bobj, "closed", l->closed);

	binn* bx = binn_list();
	binn* by = binn_list();

	for (unsigned int i = 0; i < num; ++i) {
		WPoint p = l->data[i];

		binn_list_add(bx, BINN_FAMILY_FLOAT, (void*)&p.x, i);
		binn_list_add(by, BINN_FAMILY_FLOAT, (void*)&p.y, i);
	}

	//
	binn_object_set_list(bobj, "points_x", bx);

	return bobj;
}

binn* w_serialize_object_bin(WObject* obj)
{

	binn* bobj   = binn_object();
	binn* blines = binn_list();

	binn_object_set_bool(bobj, "normalized", obj->normalized);
	binn_object_set_int64(bobj, "num_lines", obj->num_lines);
	binn_object_set_object(bobj, "transform",
			       w_serialize_transform_bin(&obj->transform));

	unsigned long long num = obj->num_lines;
	for (int i = 0; i < num; ++i) {
		WLine* l  = obj->lines[i];
		binn*  bl = w_serialize_line_bin(l);
		binn_list_add(blines, BINN_FAMILY_BINN, bl, i);
		// binn_list_add(blines, )
		// w_serialize_line_bin(l);
	}

	return bobj;
}

int w_serialize_sequence_bin(binn* obj, WSequence* seq)
{
	binn* bseq    = binn_object();
	binn* bframes = binn_list();

	binn_object_set_int32(bseq, "num_frames", seq->num_frames);
	binn_object_set_int32(bseq, "current_frame_index",
			      seq->current_frame_index);
	binn_object_set_int32(bseq, "num_golden_frames",
			      seq->num_golden_frames);

	binn_object_set_double(bseq, "anim_duration", seq->anim_duration);
	binn_object_set_int32(bseq, "anim_type", seq->anim_type);

	int num = seq->num_frames;

	for (int i = 0; i < num; ++i) {
		WObject* fr = seq->frames[i];

		binn* btrans = w_serialize_transform_bin(&seq->transform);
		binn* bframe = w_serialize_object_bin(fr);
		// binn_list_add(bframes, BINN_FAMILY_BINN, bframe, num );
		// binn_list_add(bframes, BINN_FAMILY_BINN
		// w_serialize_object_bin(bframes, fr);
	}

	binn_object_set_object(obj, "sequence", bseq);

	return 0;
}

int w_document_serialize_bin(WDocument* doc, const char* path)
{

	binn* obj;
	binn* info;
	info = binn_object();
	obj  = binn_object();
	char uuid[256];
	if (!doc->meta.uuid) {
		printf("No uuid, bailing, half written bullshit code\n");
		return 1;
	}
	strcpy(uuid, doc->meta.uuid);
	binn_object_set_str(info, "version", doc->meta.version);
	binn_object_set_str(info, "uuid", uuid);
	binn_object_set_object(obj, "info", info);

	// w_serialize_sequence_bin( obj, doc->sequence.src );

	FILE* f = fopen(path, "wb");
	if (f) {

		fwrite(binn_ptr(obj), sizeof(char), binn_size(obj), f);

	} else {
		printf("Couldn't open file for writing:\n%s", path);
	}

	// release the buffer
	binn_free(obj);
	binn_free(info);

	// WDocument* doc2 = w_document_unserialize_bin(path);

	// printf("%s - %s\n", doc->version, doc2->version );
	// printf("%s - %s\n", doc->uuid, doc2->uuid );

	return 0;
}


 */
