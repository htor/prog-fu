#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

/* stack impl using singly linked list */

struct stack 
{
    int data;
    struct stack *next;
};

int stack_size(struct stack *stack)
{
    if (!stack->next)
        return 0;
    return 1 + stack_size(stack->next);
}

struct stack *stack_create(void)
{
    struct stack *head = calloc(1, sizeof(struct stack));
    return head;
}

void stack_push(struct stack *stack, int data)
{
    struct stack *new = calloc(1, sizeof(struct stack));
    new->data = data;
    new->next = stack->next;
    stack->next = new;
}

int stack_pop(struct stack *stack)
{
    if (!stack->next)
        return -1;
    struct stack *top = stack->next;
    int topdata = top->data;
    stack->next = stack->next->next;
    free(top);
    return topdata;
}

int stack_peek(struct stack *stack)
{
    return stack->next ? stack->next->data : -1;
}

void stack_traverse(struct stack *stack, void (*callback)(struct stack *stack))
{
    if (stack->next) 
    {
        callback(stack->next);
        stack_traverse(stack->next, callback);
    }
}

void stack_print(struct stack *stack)
{
    printf("%d\n", stack->data);
}

void stack_free(struct stack *stack)
{
    if (stack)
    {
        stack_free(stack->next);
        free(stack);
    }
}

int main(int argc, char **argv)
{
    struct stack *stack = stack_create();
    assert(stack_size(stack) == 0);

    stack_push(stack, 23);
    stack_push(stack, 55);
    stack_push(stack, 66);
    assert(stack_size(stack) == 3);
    assert(stack_pop(stack) == 66);
    assert(stack_pop(stack) == 55);
    assert(stack_pop(stack) == 23);
    assert(stack_size(stack) == 0);

    stack_push(stack, 89);
    stack_push(stack, 34);
    assert(stack_peek(stack) == 34);
    assert(stack_size(stack) == 2);
    
    stack_pop(stack);
    stack_pop(stack);
    assert(stack_size(stack) == 0);
    assert(stack_pop(stack) == -1);

    stack_push(stack, 11);
    stack_push(stack, 23);
    stack_push(stack, 123321);
    stack_traverse(stack, stack_print);

    stack_free(stack);
    return 0;
}
