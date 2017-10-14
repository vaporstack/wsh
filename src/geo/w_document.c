//
//  w_document.c
//  wash
//
//  Created by Andrew Macfarlane on 1/18/17.
//  Copyright © 2017 vaporstack. All rights reserved.
//

#include "w_document.h"

#include <wsh/wsh.h>

#include <stdbool.h>

WDocument*	w_document_create()
{
	WDocument* doc = calloc(1, sizeof(WDocument));
	//printf("Creating all document attributes\n");

	char buf[128];
	sprintf(buf, "%d_%d_%d", WSH_V_MAJOR, WSH_V_MINOR, WSH_V_PATCH);

	//printf("buf : %s\n", buf );
	doc->state = W_DOC_STATE_NEVERSAVED;
	doc->version = buf;
	//doc->art.src = NULL;
	//no guarantees

	doc->layers = NULL;
	doc->layer_num = 1;
	doc->sequence.src = NULL;

	doc->version = buf;
	doc->path = NULL;

	doc->ref = NULL;
	doc->meta = NULL;

	doc->uuid = NULL;
	//doc->tags = NULL;

	return doc;
}


void w_document_destroy(WDocument* doc )
{
	if ( doc == NULL )
	{
		return;
	}

	printf("Destroying all document attributes\n");
	//if ( doc->art.src )
	//	w_object_destroy(doc->art.src);

	if ( doc->sequence.src )
		w_sequence_destroy(doc->sequence.src);

}

WDocument* w_document_copy(WDocument* old )
{
	WDocument* doc = malloc(sizeof(WDocument));
	//printf("buf : %s\n", buf );
	doc->state = old->state;
	doc->version = old->version;

	//	TODO: we haven't done layer logic yet.
	doc->layers = NULL;
	doc->layer_num = old->layer_num;
	doc->sequence.src = w_sequence_copy(old->sequence.src);

	doc->version = old->version;
	doc->path = old->path;

	doc->ref = old->ref;
	doc->meta = old->meta;
	doc->uuid = old->uuid;
	//doc->tags = old->tags;
	return doc;
}
