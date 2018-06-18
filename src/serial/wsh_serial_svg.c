
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

void wsh_serial_svg_object_serialize(cairo_surface_t* cr, WObject* obj)
{
	for ( int i = 0;i < obj->num_lines; i++ )
	{
		WLine* l = obj->lines[i];
		w_serialize_line_svg(cr, l);
		
		
	}
	
	
}

const char*	wsh_serial_svg_document_serialize(WDocument* doc)
{


	cairo_surface_t *surface;
	cairo_t *cr;
	
	int w = doc->meta.canvas_width;
	int h = doc->meta.canvas_height;
	surface = cairo_svg_surface_create("svgfile.svg", w, h);
	cr = cairo_create(surface);
	
	
	//cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	//cairo_set_font_size(cr, 40.0);
	//cairo_move_to(cr, 10.0, 50.0);
	//cairo_show_text(cr, "hello");
	
	
	
	
	cairo_set_line_width(cr, 1);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_set_source_rgba(cr, 0,0,0,.5);
	
	WSequence* seq = doc->sequence.src;
	WObject* first = seq->frames[0];

	wsh_serial_svg_object_serialize(cr, first);
	//WPoint prev;
	

	
	
	cairo_surface_destroy(surface);
	cairo_destroy(cr);
	
	return NULL;
	
	
}

WDocument*		wsh_serial_svg_document_unserialize(const char* path)
{
	return NULL;
}


#endif

#endif
