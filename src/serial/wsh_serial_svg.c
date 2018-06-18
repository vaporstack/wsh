
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

#define xmlNodePtr void*

xmlNodePtr	w_serialize_line_svg_v_1(WLine* line)
{
	/*
	 xmlNodePtr xobj;
	xobj = xmlNewNode(NULL, BAD_CAST "polyline");


	unsigned long long num = line->num;

	bool done = false;
	unsigned long long i = 0;

	//	this is unsafe as all fuck
	int sz = 256;
	char* buf = malloc(sizeof(char) * sz);
	memset(buf, 0 , sizeof(char) * sz);

	if ( num == 0 ) {
		printf("No points!\n");
		return xobj;
	}
	while ( !done )
	{
		WPoint p = line->data[i];
		double x = p.x;
		double y = p.y;
		char pair[256];

		sprintf(pair, "%f,%f", x, y);

		if ( strlen(buf)+ strlen(pair) +2 >= sz )
		{
			sz *= 2;
			buf = realloc(buf, sz);
			//printf("Reallocd buf\n");
		}

		strcat(buf, pair);
		strcat(buf, " ");

		i++;
		if ( i == num )
			done = true;

	}

	xmlNewProp(xobj, BAD_CAST "points", BAD_CAST buf);

	xmlNewProp(xobj, BAD_CAST "style", BAD_CAST "fill:none;stroke:black;stroke-width:1");
	/*
	char buffer[64];
	int ret = snprintf(buffer, sizeof buffer, "%f", myFloat);

	if (ret < 0) {

	}
	if (ret > sizeof buffer)
	{
		//Result was truncated - resize the buffer and retry.
	
	}

	//char* buff =malloc(sizeof(char)*20 * num );

	char mini[512];
	for ( int i = 0 ; i < num ; ++ i )
	{
		WPoint* p = &line->data[i];
		//sprintf(mini, "%f,%f", p->x, p->y);


	}
	 
	 
	 
	 */
	return NULL;
	//return xobj;

}

xmlNodePtr	w_serialize_line_svg(WLine* line)
{
	return w_serialize_line_svg_v_1(line);
}

xmlNodePtr	w_serialize_sequence_svg_v_1(WSequence* seq )
{

	//xmlNodePtr xobj;


	return NULL;
	

}

xmlNodePtr	w_serialize_sequence_svg(WSequence* seq )
{
	return w_serialize_sequence_svg_v_1(seq);

}

xmlNodePtr	w_serialize_object_svg_v_1(WObject* obj)
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
	return NULL;
}

xmlNodePtr	w_serialize_object_svg(WObject* obj)
{
	return w_serialize_object_svg_v_1(obj);
}

const char*	wsh_serial_svg_document_serialize(WDocument* doc)
{

	//xmlDoc	*xdoc;
/*

	xmlDocPtr xdoc = NULL;
	//xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;
	//char buff[256];
	
	LIBXML_TEST_VERSION;

	
	//Creates a new document, a node and set it as a root node
	 
	xdoc = xmlNewDoc(BAD_CAST "1.0");
	//root_node = xmlNewNode(NULL, BAD_CAST "root");
	//xmlDocSetRootElement(xdoc, root_node);

	xmlNodePtr svg = xmlNewNode(NULL, BAD_CAST "svg");

	xmlNewProp(svg, BAD_CAST "version", BAD_CAST "1.0");

	xmlNewProp(svg, BAD_CAST "height", BAD_CAST "1024");
	xmlNewProp(svg, BAD_CAST "width", BAD_CAST "1024");
	xmlNewProp(svg, BAD_CAST "viewbox", BAD_CAST "0 0 1024 1024");

	xmlDocSetRootElement(xdoc, svg);
*/
	//xmlAddChild(root_node,svg);

	/*
		WE WANT THIS, disabled because we're removing 'art' field from document
	 in favor of sequences
	WObject* art = doc->art.src;
	if ( art )
	{
		for( int i = 0 ; i < art->num_lines; ++i )
		{
			xmlNodePtr line = w_serialize_line_svg(art->lines[i]);

			xmlAddChild(svg, line);

		}
		//xmlNodePtr xart = w_serialize_object_svg(art);
	}

	 
	 */

	//xmlCreateIntSubset(xdoc, BAD_CAST "root", NULL, BAD_CAST "tree2.dtd");


	//xmlNewChild() creates a new node, which is "attached" as child node
	 //of root_node node.


	/*
	xmlNewChild(root_node, NULL, BAD_CAST "node1",
				BAD_CAST "content of node 1");

	 // The same as above, but the new child node doesn't have a content

	xmlNewChild(root_node, NULL, BAD_CAST "node2", NULL);


	 // xmlNewProp() creates attributes, which is "attached" to an node.
	 //It returns xmlAttrPtr, which isn't used here.

	node =
	xmlNewChild(root_node, NULL, BAD_CAST "node3",
				BAD_CAST "this node has attributes");
	xmlNewProp(node, BAD_CAST "attribute", BAD_CAST "yes");
	xmlNewProp(node, BAD_CAST "foo", BAD_CAST "bar");


	//Here goes another way to create nodes. xmlNewNode() and xmlNewText
	//creates a node and a text node separately. They are "attached"
	//by xmlAddChild()

	node = xmlNewNode(NULL, BAD_CAST "node4");
	node1 = xmlNewText(BAD_CAST
					   "other way to create content (which is also a node)");
	xmlAddChild(node, node1);
	xmlAddChild(root_node, node);


	 // A simple loop that "automates" nodes creation

	for (i = 5; i < 7; i++) {
		sprintf(buff, "node%d", i);
		node = xmlNewChild(root_node, NULL, BAD_CAST buff, NULL);
		for (j = 1; j < 4; j++) {
			sprintf(buff, "node%d%d", i, j);
			node1 = xmlNewChild(node, NULL, BAD_CAST buff, NULL);
			xmlNewProp(node1, BAD_CAST "odd", BAD_CAST((j % 2) ? "no" : "yes"));
		}
	}
	*/

	//Dumping document to stdio or file
/*
	xmlSaveFormatFileEnc( "asdf.xml" , xdoc, "UTF-8", 1);

	xmlFreeDoc(xdoc);


	xmlCleanupParser();


	xmlMemoryDump();


*/

	/*
	xmlDoc         *document;
	xmlNode        *root, *first_child, *node;
	char           *filename;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s filename.xml\n", argv[0]);
		return 1;
	}
	filename = argv[1];

	document = xmlReadFile(filename, NULL, 0);
	root = xmlDocGetRootElement(document);
	fprintf(stdout, "Root is <%s> (%i)\n", root->name, root->type);
	first_child = root->children;
	for (node = first_child; node; node = node->next) {
		fprintf(stdout, "\t Child is <%s> (%i)\n", node->name, node->type);
	}
	fprintf(stdout, "...\n");
	return 0;



	 */
	
	
	cairo_surface_t *surface;
	cairo_t *cr;
	
	surface = cairo_svg_surface_create("svgfile.svg", 390, 60);
	cr = cairo_create(surface);
	
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
			       CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, 40.0);
	
	cairo_move_to(cr, 10.0, 50.0);
	cairo_show_text(cr, "Disziplin ist Macht.");
	
	cairo_surface_destroy(surface);
	cairo_destroy(cr);
	
	return 0;
	
	
	
}

WDocument*		wsh_serial_svg_document_unserialize(const char* path)
{
	return NULL;
}


#endif

#endif
