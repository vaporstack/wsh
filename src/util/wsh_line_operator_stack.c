

#include "wsh_line_operator_stack.h"

WshOperatorStack* wsh_line_operator_stack_create(void)
{
	WshOperatorStack* stack = calloc(1, sizeof(WshOperatorStack));

	return stack;
}
void wsh_line_operator_stack_destroy(WshOperatorStack* stack)
{
	free(stack);
}

int wsh_line_operator_stack_add(WshOperatorStack* stack, operator_stack_fn fn)
{
	stack->num++;
	stack->data		    = realloc(stack->data, stack->num * sizeof(operator_stack_fn));
	stack->data[stack->num - 1] = fn;
	return stack->num;
}

WLine* wsh_line_operator_stack_apply(WLine* input, WshOperatorStack* stack)
{
	WLine* base = wsh_line_copy(input);
	for (int i = 0; i < stack->num; i++) {
		operator_stack_fn fun       = stack->data[i];
		WLine*		  processed = fn(base);
		wsh_line_destroy(base);
		base = processed;
	}
	return base;
}
