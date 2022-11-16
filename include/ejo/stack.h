#pragma once

/**
 * @brief Last-in, first-out data structure.
 */
typedef struct EJO_Stack EJO_Stack;

/**
 * @brief Create a stack. It is allocated & must be freed by the user with the
 * given `EJO_Stack_Free` function.
 * 
 * @param capacity number of elements stack can hold at once
 * @param unit size of the elements
 * @return EJO_Stack* allocated stack
 */
EJO_Stack* EJO_Stack_Create(unsigned long capacity, unsigned long unit);

/**
 * @brief Add an element to the stack, unless full.
 * 
 * @param stack stack to add element to
 * @param value pointer to value to add to stack, expected to be queue unit size
 * @return char `1` if not full, `0` if full
 */
char EJO_Stack_Push(EJO_Stack* stack, void* value);

/**
 * @brief Read the most recently-added element from the stack & remove it.
 * 
 * @param stack stack to read element from
 * @param dest pointer to save element value in, expected to be queue unit size
 * @return char `1` if not empty, `0` if empty
 */
char EJO_Stack_Pop(EJO_Stack* stack, void* dest);

/**
 * @brief Free stack memory. Pointer should not be accessed after this.
 * 
 * @param stack stack to destroy
 */
void EJO_Stack_Free(EJO_Stack* stack);

#ifdef EJO_DEFINE

#ifndef EJO_ALLOCATE
#include <stdlib.h>
#define EJO_ALLOCATE malloc
#endif

#ifndef EJO_FREE
#include <stdlib.h>
#define EJO_FREE free
#endif

#ifndef EJO_ASSERT
#include <assert.h>
#define EJO_ASSERT assert
#endif

#ifndef EJO_MEMCPY
#include <string.h>
#define EJO_MEMCPY memcpy
#endif

typedef struct EJO_Stack
{
    char* data;
    unsigned long index;
    unsigned long size_capacity;
    unsigned long size_unit;
} EJO_Stack;

EJO_Stack* EJO_Stack_Create(unsigned long capacity, unsigned long unit)
{
    EJO_Stack* stack = EJO_ALLOCATE(sizeof(EJO_Stack));
    stack->data = EJO_ALLOCATE(capacity * unit);
    stack->index = 0;
    stack->size_capacity = capacity;
    stack->size_unit = unit;

    return stack;
}

char EJO_Stack_Push(EJO_Stack* stack, void* value)
{
    EJO_ASSERT(stack != NULL);
    EJO_ASSERT(value != NULL);

    if (stack->index >= stack->size_capacity)
    {
        return 0;
    }

    EJO_MEMCPY(
        &stack->data[stack->size_unit * stack->index],
        value,
        stack->size_unit
    );
    stack->index++;

    return 1;
}

char EJO_Stack_Pop(EJO_Stack* stack, void* dest)
{
    EJO_ASSERT(stack != NULL);
    EJO_ASSERT(dest != NULL);

    if (stack->index == 0)
    {
        return 0;
    }

    EJO_MEMCPY(
        dest,
        &stack->data[stack->size_unit * stack->index],
        stack->size_unit
    );
    stack->index++;

    return 1;
}

void EJO_Stack_Free(EJO_Stack* stack)
{
    EJO_FREE(stack->data);
    EJO_FREE(stack);
}

#endif
