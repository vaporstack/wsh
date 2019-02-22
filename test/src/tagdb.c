
#ifndef test_tagdb_h_
#define test_tagdb_h_

#include <wsh/src/ext/wsh_tagdb.h>
#include <wsh/wsh.h>

static void test_tagdb(void)
{
	const char* jsonpath = "/tmp/test.json";
	bool	res      = wsh_tagdb_load(jsonpath);
	if (!res)
		printf("ack!\n");

	res = wsh_tagdb_add("animated");
	res = wsh_tagdb_add("animated");
	res = wsh_tagdb_add("lifedrawing");
	wsh_tagdb_add("drinkndraw");
	int	  num;
	const char** tags = wsh_tagdb_list(&num);
	printf("Have %d tags.\n", num);
	for (int i = 0; i < num; i++)
	{
		printf("tag: %s\n", tags[i]);
	}
	wsh_tagdb_save(jsonpath);

	free(tags);
}

#endif
