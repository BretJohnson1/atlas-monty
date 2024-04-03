/**
 * swap - swaps the two top elements of a stack
 * @stack: linked list stack to swap
 * @line_number: current line number of bytecode file
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp = (*stack)->n;

	if (!(*stack) || !(*stack)->next)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		fclose(file);
		exit(EXIT_FAILURE);
	}
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}