

#ifndef geo_c
#define geo_c

#include <wsh/wsh.h>

#include <stdlib.h>

int test_geometry(void)
{
	printf("Testing geometry.\n");

	WLine* line = wsh_line_create();

	WObject* obj = wsh_object_create(NULL);
	wsh_object_addrw_line(obj, line);

	wsh_line_destroy(line);
	wsh_object_destroy(obj);
	return 0;
}

#endif
