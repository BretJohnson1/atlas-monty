#include "monty.h"

/**
 * free_stack - free the memory that has been allocated
 * @stack: ptr to the doubly linked stack representation
 * Return: bit fat nothuing
 */

void free_stack(stack_t **stack)
{
	stack_t *temp = *stack;

	while (*stack)
	{
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
	}
}