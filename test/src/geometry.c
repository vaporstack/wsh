

#ifndef geo_c
#define geo_c

#include <wsh/wsh.h>

#include <stdlib.h>

int test_geometry(void)
{
	printf("Testing geometry.\n");

	WLine* line = w_line_create();

	WObject* obj = w_object_create(NULL);
	w_object_add_line(obj, line);

	w_line_destroy(line);
	w_object_destroy(obj);
	return 0;
}

#endif
