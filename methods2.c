#include "monty.h"

/**
 * add_list - adds the top two elements
 * @stack: head of list
 * @line_number: instruction
 */
void add_list(stack_t **stack, unsigned int line_number)
{
	stack_t *current = *stack;
	stack_t *next;

	if (!current || !current->next)
	{
		dprintf(STDERR_FILENO, "L%u: can't add, stack too short\n", line_number);
		garbage_collection();
		exit(EXIT_FAILURE);
	}
	next = current->next;
	next->n += current->n;
	pop_list(stack, line_number);
}

/**
 * nop_list - do nothing
 * @stack: head of the list
 * @line_number: instruction
 */
void nop_list(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
