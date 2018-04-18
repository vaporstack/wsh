//
//  w_document.h
//  wash
//
//  Created by Andrew Macfarlane on 1/18/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#ifndef w_document_h
#define w_document_h

#include "w_object.h"
#include "w_sequence.h"

enum
{
	W_DOC_STATE_UNKNOWN,
	//W_DOC_STATE_NEVERSAVED,
	W_DOC_STATE_CLEAN,
	W_DOC_STATE_DIRTY
};

typedef struct EventList
{
	const char**       descriptions;
	double**	   times;
	unsigned long long num;
} EventList;

typedef struct WDocumentMeta
{
	//	session
	EventList* events;

	//	plugins
	// ????

	//	canvas
	int canvas_width;
	int canvas_height;

	//	info
	int	 version;
	const char* version_string;
	const char* path;
	const char* name;
	const char* ref;
	
	double      fps;
	const char* fps_repr;
	const char* uuid;

} WDocumentMeta;

typedef struct WDocument
{

	int state;

	WDocumentMeta meta;

	WSequenceHnd   sequence;
	WSequenceHnd** layers;

	int layer_num;

} WDocument;

typedef struct WDocumentHnd
{
	WDocument* src;
} WDocumentHnd;

WDocument* w_document_create(void);
void       w_document_destroy(WDocument*);

WDocument* w_document_copy(WDocument*);
void       w_document_meta_clear(WDocumentMeta* meta);

#endif /* w_document_h */
