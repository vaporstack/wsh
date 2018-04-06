

#ifndef serial_c
#define serial_c

#include <stdio.h>
#include <wsh/wsh.h>

#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON
int test_serial_backend_json(void)
{
	return 1;
}
#endif //WSH_ENABLE_SERIAL_BACKEND_JSON

int test_serial_backends(void)
{
	printf("Testing serial backends.\n");
	int err;

#ifdef WSH_ENABLE_SERIAL_BACKEND_JSON

	err = test_serial_backend_json();
	if (err)
		printf("Error code: %d\n", err);

#endif

	return 0;
}

#endif
