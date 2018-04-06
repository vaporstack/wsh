

#include "stdlib.h"
#include <wsh/wsh.h>

//#include "geometry.c"
//#include "serial.c"

int test_serial_backends(void);
int test_geometry(void);

int main(int argc, char** argv)
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
		printf("Version does not match!!\n");
	}

	int err = test_geometry();
	if (err)
	{
		printf("Err code: %d\n", err);
	}

	err = test_serial_backends();
	if (err)
	{
		printf("Err code: %d\n", err);
	}
	return 0;
	/*


	*/
}
