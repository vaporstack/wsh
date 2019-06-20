

#ifndef wsh_line_operator_stack_h
#define wsh_line_operator_stack_h

#include <wsh/wsh.h>

typedef WLine* (*operator_stack_fn)(WLine*);

typedef struct
{
	int		    num;
	operator_stack_fn** data;
	//WLine* (*operators)(WLine*)stack;
} WshOperatorStack;

WshOperatorStack* wsh_line_operator_stack_create(void);
void wsh_line_operator_stack_destroy(WshOperatorStack* stack);
int wsh_line_operator_stack_add(WshOperatorStack* stack, operator_stack_fn fn);
WLine* wsh_line_operator_stack_apply(WLine* input, WshOperatorStack* stack);

#endif
