#include "monty.h"
/**
 * pint - prints the value in the first node of a stack
 * @stack: linked list stack to pint
 * @line_number: current line number of bytecode file
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (!(*stack))
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		fclose(file);
		free_stack(stack);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}