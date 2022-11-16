#pragma once

typedef struct EJO_Queue EJO_Queue;

EJO_Queue EJO_Queue_Create(size_t capacity, size_t unit);

char EJO_Queue_Push(EJO_Queue* queue, void* value);

char EJO_Queue_Shift(EJO_Queue* queue, void* dest);

void EJO_Queue_Free(EJO_Queue queue);

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
    size_t index_begin;
    size_t index_end;
    size_t size_capacity;
    size_t size_unit;
} EJO_Queue;

EJO_Queue EJO_Queue_Create(size_t capacity, size_t unit)
{
    return (EJO_Queue){
        .data = EJO_ALLOCATE(capacity * unit),
        .index_begin = 0,
        .index_end = 0,
        .size_capacity = capacity,
        .size_unit = unit,
    };
}

char EJO_Queue_Push(EJO_Queue* queue, void* value)
{
    EJO_ASSERT(queue->data != NULL);
    EJO_ASSERT(value != NULL);
    
    printf("Push to %d\n", queue->index_end);
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
    
    printf("Shift from %d\n", queue->index_begin);
    EJO_MEMCPY(
        dest,
        &queue->data[queue->index_begin * queue->size_unit],
        queue->size_unit
    );
    
    queue->index_begin = (queue->index_begin + 1) % queue->size_capacity;
    
    return 1;
}

void EJO_Queue_Free(EJO_Queue queue)
{
    EJO_FREE(queue.data);
}

#endif
