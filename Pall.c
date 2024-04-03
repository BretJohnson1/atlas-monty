#include "monty.h"

/**
 * pall - prints all elements of a stack
 * @stack: linked list stack to pall
 * @line_number: current line number of bytecode file
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *node;

	node = *stack;
	while (node)
	{
		printf("%d\n", node->n);
		node = node->next;
	}
	(void) line_number;
}