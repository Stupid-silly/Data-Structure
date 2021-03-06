#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef char Elem;

typedef struct {
    Elem *elems;
    int length;
    int capacity;  
} Stack;

void stackVisit(Stack *stack)
{
    int i;

    printf("Stack elems:");
    for (i = 0; i < stack->length; i++)
        printf("  %d", stack->elems[i]);
    printf("\n");
}

#define INITIAL_CAPACITY 4

void stackInit(Stack *stack)
{
    stack->elems = malloc(sizeof(Elem) * INITIAL_CAPACITY);
    stack->length = 0;
    stack->capacity = INITIAL_CAPACITY;
}

void stackDestroy(Stack *stack)
{
    free(stack->elems);
}

int stackLength(Stack *stack)
{
    return stack->length;
}

int stackEmpty(Stack *stack)
{
    return stack->length == 0;
}

Elem stackGetTop(Stack *stack)
{
    assert(stack->length > 0);

    Elem top = stack->elems[stack->length - 1];
    return top;
}

void stackPush(Stack *stack, Elem elem)
{
    if (stack->length >= stack->capacity) {
        int newCapacity = stack->capacity * 2;
        stack->elems = realloc(stack->elems, sizeof(Elem) * newCapacity);
        stack->capacity = newCapacity;
    }

    stack->elems[stack->length] = elem;
    stack->length++;
}

Elem stackPop(Stack *stack)
{
    assert(stack->length > 0);
    Elem top = stack->elems[stack->length - 1];
    stack->length--;
    return top;
}

void stringReverse(char *input, char *output)
{
	Stack s;
	stackInit(&s);
	int i;

    for (i = 0; *(input+i); i++)
    {
		stackPush(&s,*(input+i));
    }
	
    for (i = 0;!stackEmpty(&s); i++)
    {
		*(output+i) = stackPop(&s);
    }
	*(output+i) = '\0';
}

void testStringReverse()
{
    char output[100];

    stringReverse("abc", output);
    puts(output);

    stringReverse("a", output);
    puts(output);
}

int main()
{
    testStringReverse();
    return 0;
}