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
	W_DOC_STATE_NEVERSAVED,
	W_DOC_STATE_CLEAN,
	W_DOC_STATE_DIRTY
};

typedef struct
{

	//	info - stuff about the document itself
	int state;
	char* version;
	char* path;
	char* ref;
		const char* uuid;

	//	meta - info about the creation of the data
	void* meta;
	
	//	not sure if tags belong to meta or not. keeping in for now.
	//	these probably belong in meta
	//	const char* tags;

	//	the data itself
	WSequenceHnd sequence;
	WSequenceHnd ** layers;
	int layer_num;
	
} WDocument;

typedef struct WDocumentHnd
{
	WDocument* src;
} WDocumentHnd;


WDocument*	w_document_create(void);
void		w_document_destroy(WDocument* );

WDocument*	w_document_copy(WDocument* );


#endif /* w_document_h */
