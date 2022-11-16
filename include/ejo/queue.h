#pragma once

/**
 * @brief First-in, first-out data structure.
 */
typedef struct EJO_Queue EJO_Queue;

/**
 * @brief Create a queue. It is allocated & must be freed by the user with the
 * given `EJO_Queue_Free` function.
 * 
 * @param capacity number of elements queue can hold at once
 * @param unit size of the elements
 * @return EJO_Queue* allocated queues
 */
EJO_Queue* EJO_Queue_Create(unsigned long capacity, unsigned long unit);

/**
 * @brief Add an element to a queue, unless full.
 * 
 * @param queue queue to add element to
 * @param value pointer to value to add to queue, expected to be queue unit size
 * @return char `1` if not full, `0` if full
 */
char EJO_Queue_Push(EJO_Queue* queue, void* value);

/**
 * @brief Read the oldest element in the queue & remove it.
 * 
 * @param queue queue to read element from
 * @param dest pointer to save element value in, expected to be queue unit size
 * @return char `1` if not empty, `0` if empty
 */
char EJO_Queue_Shift(EJO_Queue* queue, void* dest);

/**
 * @brief Free queue memory. Pointer should not be accessed after this.
 * 
 * @param queue queue to destroy
 */
void EJO_Queue_Free(EJO_Queue* queue);

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

typedef struct EJO_Queue
{
    char* data;
    unsigned long index_begin;
    unsigned long index_end;
    unsigned long size_capacity;
    unsigned long size_unit;
    char untouched;
} EJO_Queue;

EJO_Queue* EJO_Queue_Create(unsigned long capacity, unsigned long unit)
{
    EJO_Queue* queue = EJO_ALLOCATE(sizeof(EJO_Queue));
    queue->data = EJO_ALLOCATE(capacity * unit);
    queue->index_begin = 0;
    queue->index_end = 0;
    queue->size_capacity = capacity;
    queue->size_unit = unit;
    queue->untouched = 1;

    return queue;
}

char EJO_Queue_Push(EJO_Queue* queue, void* value)
{
    EJO_ASSERT(queue->data != NULL);
    EJO_ASSERT(value != NULL);

    if (
        !queue->untouched
        && queue->index_begin == queue->index_end
    ) {
        return 0;
    }

    queue->untouched = 0;
    
    EJO_MEMCPY(
        &queue->data[queue->index_end * queue->size_unit],
        value,
        queue->size_unit
    );
    queue->index_end = (queue->index_end + 1) % queue->size_capacity;
    
    return 1;
}

char EJO_Queue_Shift(EJO_Queue* queue, void* dest)
{
    EJO_ASSERT(queue->data != NULL);
    EJO_ASSERT(dest != NULL);

    if (queue->untouched) {
        return 0;
    }
    
    EJO_MEMCPY(
        dest,
        &queue->data[queue->index_begin * queue->size_unit],
        queue->size_unit
    );
    
    queue->index_begin = (queue->index_begin + 1) % queue->size_capacity;

    if (queue->index_begin == queue->index_end) {
        queue->untouched = 1;
    }
    
    return 1;
}

void EJO_Queue_Free(EJO_Queue* queue)
{
    EJO_FREE(queue->data);
    EJO_FREE(queue);
}

#endif
