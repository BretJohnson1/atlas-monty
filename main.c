#include "monty.h"

FILE *file = NULL;
/**
 * main - Hi Mr. Monty how are you?
 * @argc: The ticker for the arguments who come in
 * @argv: The arguments themselves and what they are worth
 * Return: Sometimes 0 (on Success).
 */
int main(int argc, char **argv)
{
	void (*f)(stack_t **, unsigned int) = NULL;
	char *buffer = NULL, op[50] = {'\0'}, pushNum[50] = {'\0'}, *token = NULL;
	size_t bufsize = 0;
	stack_t *stack = NULL;
	unsigned int line_number = 1;

	if (argc != 2)
		fprintf(stderr, "USAGE: monty file\n"), exit(EXIT_FAILURE);
	file = fopen(argv[1], "r");
	if (!file)
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]), exit(EXIT_FAILURE);
	for (; getline(&buffer, &bufsize, file) != EOF; line_number++)
	{
		token = strtok((buffer), " \t\n");
		if (!token)
		{
			free(buffer), buffer = NULL;
			continue;
		}
		strcpy(op, token);
		f = get_func(&stack, line_number, op);
		if (!f)
			fprintf(stderr, "Error: malloc failed\n"), error();
		if (strcmp(op, "push") == 0)
		{
			token = strtok(NULL, " \t\n");
			if (!token)
			{
				free(buffer), buffer = NULL, free_stack(&stack);
				fprintf(stderr, "L%d: usage: push integer\n", line_number), error();
			}
			strcpy(pushNum, token);
		}
		free(buffer), buffer = NULL;
		f(&stack, line_number);
		if (strcmp(op, "push") == 0)
			pushOp(&stack, line_number, pushNum);
	}
	free(buffer), fclose(file), free_stack(&stack);
	return (EXIT_SUCCESS);
}
/**
 *get_func - get a func of some kind
 *@stack: the whole stack
 *@l: the line number
 *@code: the code being brought in
 *Return: what ever func is right
 */

void (*get_func(stack_t **stack, int l, char *code))(stack_t **, unsigned int)
{
	instruction_t instruction[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop}
	};
	int i = 0;

	while (strcmp(code, instruction[i].opcode) != 0)
	{
		i++;
		if (i > 7)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", l, code);
			free_stack(stack);
			error();
		}
	}
	return (instruction[i].f);
}
/**
 *pushOp - helps the push operation
 *@stack: is a linked list
 *@line_number: is a counter
 *@pushNum: adds to a new node
 */
void pushOp(stack_t **stack, unsigned int line_number, char *pushNum)
{
	if (strcmp(pushNum, "0") == 0)
		(*stack)->n = 0;
	if (strcmp(pushNum, "0") != 0)
	{
		(*stack)->n = atoi(pushNum);
		if ((*stack)->n == 0 || (pushNum[0] != '-' && (*stack)->n == -1))
		{
			fprintf(stderr, "L6: usage: push integer\n", line_number);
			free_stack(stack);
			error();
		}
	}
}
/**
 *error - error is bad
 *Return: an exit
 */
void error(void)
{
	fclose(file);
	exit(EXIT_FAILURE);
}
