

#include "stdlib.h"
#include <wsh/wsh.h>

int
main(int argc, char **argv)
{
	//	simple test program for wash.
	//	create some geometry, write an svg, possibly a png?

	printf("Running wsh tests.\n");
	printf("making sure header matches library.\n");
	if (wsh_check_version_match(wsh_get_version_string()))
	{
		printf("version matches.\n");
	}
	else
	{
		printf("Version does not match!\n");
	}

	WLine *line = w_line_create();

	WObject *obj = w_object_create(NULL);
	w_object_add_line(obj, line);

	w_line_destroy(line);
	w_object_destroy(obj);
	return 0;
}