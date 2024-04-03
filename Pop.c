#include "monty.h"
/**
 * pop - removes the first element of the stack
 * @stack: linked list stack to pop
 * @line_number: current line number of bytecode file
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	temp = *stack;
	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pop and empty stack\n", line_number);
		fclose(file);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	*stack = temp->next;
	if (*stack)
		(*stack)->prev = NULL;
	free(temp);
}