#include "monty.h"
/**
*push - pushes an element to the stack
*@stack: pointer to the stack
*@line_number: line number
*@arg: argument to push
*/
void push(stack_t **stack, char *arg,unsigned int line_number)
{
    stack_t *new_node;

    if (!arg || !isdigit(*arg))
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

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