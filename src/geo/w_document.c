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

void w_document_meta_clear(WDocumentMeta* meta)
{
	meta->path	   = NULL;
	meta->name	   = NULL;
	meta->ref	    = NULL;
	meta->fps	    = 24;
	meta->fps_repr       = NULL;
	meta->uuid	   = NULL;
	meta->canvas_width   = 0;
	meta->canvas_height  = 0;
	meta->events	 = NULL;
	meta->version_string = NULL;
	meta->version	= 0;
	meta->animated = false;
	
}

WDocument* w_document_create()
{
	WDocument* doc = calloc(1, sizeof(WDocument));
	// printf("Creating all document attributes\n");

	char buf[128];
	sprintf(buf, "%d_%d_%d", WSH_VERSION_MAJOR, WSH_VERSION_MINOR,
		WSH_VERSION_PATCH);

	//meta->name = "Untitled";

	// printf("buf : %s\n", buf );
	doc->state = W_DOC_STATE_CLEAN;
	//doc->meta.version = buf;
	// doc->art.src = NULL;
	// no guarantees

	doc->layers       = NULL;
	doc->layer_num    = 1;
	doc->sequence.src = NULL;

	//doc->version = buf;
	//doc->path    = NULL;

	//doc->ref  = NULL;
	//doc->meta = NULL;
	w_document_meta_clear(&doc->meta);

	//doc->uuid = NULL;
	// doc->tags = NULL;

	return doc;
}

void w_document_destroy(WDocument* doc)
{
	if (doc == NULL)
	{
		return;
	}

	//printf("Destroying all document attributes\n");
	// if ( doc->art.src )
	//	w_object_destroy(doc->art.src);

	if (doc->sequence.src)
		w_sequence_destroy(doc->sequence.src);
}

WDocument* w_document_copy(WDocument* old)
{
	WDocument* doc = malloc(sizeof(WDocument));
	// printf("buf : %s\n", buf );
	doc->state = old->state;
	//doc->meta = old->meta;

	//	TODO: we haven't done layer logic yet.
	doc->layers       = NULL;
	doc->layer_num    = old->layer_num;
	doc->sequence.src = w_sequence_copy(old->sequence.src);
	doc->meta	 = old->meta;

	/*doc->version = old->version;
	doc->path    = old->path;

	doc->ref  = old->ref;
	doc->uuid = old->uuid;
	*/
	// doc->tags = old->tags;
	return doc;
}
