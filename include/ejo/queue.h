#pragma once

typedef struct EJO_Queue EJO_Queue;

EJO_Queue EJO_Queue_Create(size_t capacity, size_t unit);

#ifdef EJO_DEFINE

typedef struct EJO_Queue
{
    char* data;
    size_t index;
    size_t size_capacity;
    size_t size_unit;
} EJO_Queue;

EJO_Queue EJO_Queue_Create(size_t capacity, size_t unit)
{
    return (EJO_Queue){
        .data = malloc(capacity * unit),
        .index = 0,
        .size_capacity = capacity,
        .size_unit = unit,
    };
}

#endif
