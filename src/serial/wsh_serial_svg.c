
//  w_serial_svg.c
//  w_serial_svg
//
//  Created by Andrew Macfarlane on 21/03/17.
//  Copyright © 2017 vaporstack. All rights reserved.

#include "wsh_serial_svg.h"


#ifndef RPLATFORM_IOS
#ifndef RPLATFORM_WIN

#include <stdio.h>
#include <string.h>
#include "libxml/parser.h"
#include <stdio.h>

#include <cairo/cairo.h>
#include <cairo/cairo-svg.h>

//#define xmlNodePtr void*

void	w_serialize_line_svg_v_1(cairo_surface_t* cr, WLine* line)
{
	
	for ( int j = 1; j < line->num; j++)
	{
		WPoint prev = line->data[j-1];
		cairo_move_to(cr, prev.x, prev.y);
		WPoint p = line->data[j];
		cairo_line_to(cr, p.x, p.y);
	}
	cairo_stroke(cr);
}


void	w_serialize_line_svg(cairo_surface_t* cr, WLine* line)
{
	w_serialize_line_svg_v_1(cr, line);
}

void	w_serialize_sequence_svg_v_1(WSequence* seq )
{


	

}

void	w_serialize_sequence_svg(cairo_surface_t* cr, WSequence* seq )
{
	return w_serialize_sequence_svg_v_1(seq);

}

void	w_serialize_object_svg_v_1(WObject* obj)
{
	/*
	//xmlNodePtr xobj;
	for ( int i = 0 ; i < obj->num_lines; ++i )
	{
		WLine* line = obj->lines[i];
		xmlNodePtr xline = w_serialize_line_svg( line);


	}
	return xobj;
	*/
	
}

void	w_serialize_object_svg(cairo_surface_t* cr, WObject* obj)
{
	return w_serialize_object_svg_v_1(obj);
}

void wsh_serial_svg_object_serialize(const char* path, WDocument* doc, WObject* obj)
{
	cairo_surface_t *surface;
	cairo_t *cr;
	WDocumentMeta meta = doc->meta;
	int w = doc->meta.canvas_width;
	int h = doc->meta.canvas_height;

	surface = cairo_svg_surface_create(path, w, h);
	cr = cairo_create(surface);

	
	cairo_set_line_width(cr, 1);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_source_rgba(cr, 0,0,0,.5);
	
	
	for ( int i = 0;i < obj->num_lines; i++ )
	{
		WLine* l = obj->lines[i];
		w_serialize_line_svg(cr, l);
		
		
	}
	cairo_surface_destroy(surface);
	cairo_destroy(cr);
	
	

	
}

const char*	wsh_serial_svg_document_serialize(WDocument* doc)
{


	WDocumentMeta meta = doc->meta;
	int w = doc->meta.canvas_width;
	int h = doc->meta.canvas_height;
	const char* path = meta.path;

	printf("Exporting svg for document: %s\n", path);
	
	char buf[PATH_MAX];
	
	


	const char* name = meta.name;
	
	if (!name )
	{
		name = "unnamed_wash_document";
	}
	
	//cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	//cairo_set_font_size(cr, 40.0);
	//cairo_move_to(cr, 10.0, 50.0);
	//cairo_show_text(cr, "hello");
	
	
	
	WSequence* seq = doc->sequence.src;
	
	for ( int i = 0; i < seq->num_frames; i++ )
	{
		sprintf(buf, "/tmp/%s-%02d.svg", name, i );

		WObject* frame = seq->frames[i];
		wsh_serial_svg_object_serialize(buf, doc, frame);

	}

	//WPoint prev;
	
	
	

	return NULL;
	
	
}

WDocument*		wsh_serial_svg_document_unserialize(const char* path)
{
	return NULL;
}


#endif

#endif
