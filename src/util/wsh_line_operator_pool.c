

#include "wsh_line_operator_pool.h"

static void provide_builtins(WshLineOperatorPool* pool)
{
}

WshLineOperatorPool* wsh_line_operator_pool_create_with_builtins(void)
{
	return NULL;
}

WshLineOperatorPool* wsh_line_operator_pool_create(void)
{
	WshLineOperatorPool* pool = calloc(1, sizeof(WshLineOperatorPool));
	return pool;
}

int wsh_line_operator_pool_register(WshLineOperatorPool* pool, WshLineOperatorInfo* info)
{
	return 0;
}

WshLineOperatorInfo** wsh_line_operator_pool_list(WshLineOperatorPool* pool, int* num)
{
	WshLineOperatorInfo** records = calloc(pool->num, sizeof(WshLineOperatorInfo));
	for (int i = 0; i < pool->num; i++) {
		records[i] = pool->data[i];
	}
	*num = pool->num;
	return records;
}

void wsh_line_operator_pool_create_builtins(WshLineOperatorPool* pool)
{
}
