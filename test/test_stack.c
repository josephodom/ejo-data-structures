#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ejo/stack.h>

void test_stack_happy_path_byte()
{
    char value;
    EJO_Stack* stack = EJO_Stack_Create(3, sizeof(value));

    // Fill up stack
    value = 1;
    EJO_Stack_Push(stack, &value);
    value = 2;
    EJO_Stack_Push(stack, &value);
    value = 3;
    EJO_Stack_Push(stack, &value);

    // Empty stack
    EJO_Stack_Pop(stack, &value);
    assert(value == 3);
    EJO_Stack_Pop(stack, &value);
    assert(value == 2);
    EJO_Stack_Pop(stack, &value);
    assert(value == 1);

    EJO_Stack_Free(stack);
}

void test_stack_happy_path_multibyte()
{
    char* value;
    EJO_Stack* stack = EJO_Stack_Create(3, sizeof(char) * 5);

    // Fill up stack
    value = "Jane";
    EJO_Stack_Push(stack, &value);
    value = "Alex";
    EJO_Stack_Push(stack, &value);
    value = "Pam!";
    EJO_Stack_Push(stack, &value);

    // Empty stack
    EJO_Stack_Pop(stack, &value);
    assert(strcmp(value, "Pam!") == 0);
    EJO_Stack_Pop(stack, &value);
    assert(strcmp(value, "Alex") == 0);
    EJO_Stack_Pop(stack, &value);
    assert(strcmp(value, "Jane") == 0);

    EJO_Stack_Free(stack);
}

void test_stack_overpush()
{
    char value = 0;
    EJO_Stack* stack = EJO_Stack_Create(2, sizeof(value));

    assert(EJO_Stack_Push(stack, &value));
    assert(EJO_Stack_Push(stack, &value));
    assert(!EJO_Stack_Push(stack, &value));

    EJO_Stack_Free(stack);
}

void test_stack_overpop()
{
    char value = 0;
    EJO_Stack* stack = EJO_Stack_Create(2, sizeof(value));

    assert(EJO_Stack_Push(stack, &value));
    assert(EJO_Stack_Push(stack, &value));

    assert(EJO_Stack_Pop(stack, &value));
    assert(EJO_Stack_Pop(stack, &value));
    assert(!EJO_Stack_Pop(stack, &value));

    EJO_Stack_Free(stack);
}

void test_stack()
{
    test_stack_happy_path_byte();
    test_stack_happy_path_multibyte();
    test_stack_overpush();
    test_stack_overpop();
}
