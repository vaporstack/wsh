
#ifndef wsh_line_operator_pool_h
#define wsh_line_operator_pool_h

#include "wsh_line_operator_stack.h"

typedef struct
{
	operator_stack_fn fn;
	const char*       ident;
	const char*       nice_name;
	const char*       desc;
} WshLineOperatorInfo;

typedef struct
{
	int		      num;
	WshLineOperatorInfo** data;
} WshLineOperatorPool;

WshLineOperatorPool* wsh_line_operator_pool_create(void);

WshLineOperatorPool* wsh_line_operator_pool_create_with_builtins(void);
int wsh_line_operator_pool_register(WshLineOperatorPool* pool, WshLineOperatorInfo* info);
WshLineOperatorInfo** wsh_line_operator_pool_list(WshLineOperatorPool* pool, int* num);
void wsh_line_operator_pool_create_builtins(WshLineOperatorPool* pool);

#endif
