#include "monty.h"
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
/**
*main - entry point
*@argc: argument count
*@argv: argument vector
*Return: EXIT_SUCCESS or EXIT_FAILURE
*/
int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    stack_t *stack = NULL;
    unsigned int line_number = 0;
    instruction_t instructions[] = {
        {"push", push},
        {"pall", pall},
        {NULL, NULL}
};

if (argc != 1)
{
    fprintf(stderr, "Usage: %s\n", argv[0]);
    exit(EXIT_FAILURE);
}

while ((read = getline(&line, &len, stdin)) != -1)
{
    char *opcode, *argument;
    line_number++;

/** parse the line into opcode and argument*/
    opcode = strtok(line, " \n\t");
    argument = strtok(NULL, " \n\t");

/** search for the opcode and execute the associated function*/
int found = 0;
for (int i = 0; instructions[i].opcode != NULL; i++)
{
    if (strcmp(opcode, instructions[i].opcode) == 0)
    {
        found = 1;
        if (argument != NULL && strcmp(opcode, "push") == 0)
        {
            if (isdigit(*argument) || (argument[0] == '-' && isdigit(argument[1])))
            instructions[i].f(&stack, line_number);
        else
        {
            fprintf(stderr, "L%d: usage: push integer\n", line_number);
            exit(EXIT_FAILURE);
        }
        }
        else if (argument != NULL)
        {
            fprintf(stderr, "L%d: usage: %s\n", line_number, opcode);
            exit(EXIT_FAILURE);
        }
        else
        instructions[i].f(&stack, line_number);
    break;
    }
}
if (!found)
{
    fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
    exit(EXIT_FAILURE);
}
}
free(line);
return (EXIT_SUCCESS;)
}
