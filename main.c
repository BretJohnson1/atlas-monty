#include "monty.h"

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
return (EXIT_SUCCESS);


/**
*push - pushes an element to the stack
*@stack: pointer to the stack
*@line_number: line number
*/
void push(stack_t **stack, unsigned int line_number)
{
    stack_t *new_node;

    new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = atoi(strtok(NULL, " \n\t"));
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack != NULL)
    (*stack)->prev = new_node;
    *stack = new_node;
}


/**
*pall - prints all the values on the stack
*@stack: pointer to the stack
*@line_number: line number
*/
void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *current = *stack;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}