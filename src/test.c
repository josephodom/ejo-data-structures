#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void* my_allocator(size_t size);
void my_free(void* ptr);

#define EJO_DEFINE
#define EJO_ALLOCATE my_allocator
#define EJO_FREE my_free
#include <ejo/queue.h>

int main()
{
    printf("Hello, World!\n");
    
    char value;
    
    EJO_Queue queue = EJO_Queue_Create(4, sizeof(value));
    
    value = 3;
    EJO_Queue_Push(&queue, &value);
    value = 4;
    EJO_Queue_Push(&queue, &value);
    value = 6;
    EJO_Queue_Push(&queue, &value);
    
    EJO_Queue_Shift(&queue, &value);
    assert(value == 3);
    EJO_Queue_Shift(&queue, &value);
    assert(value == 4);
    EJO_Queue_Shift(&queue, &value);
    assert(value == 6);
    
    value = 3;
    EJO_Queue_Push(&queue, &value);
    value = 4;
    EJO_Queue_Push(&queue, &value);
    value = 6;
    EJO_Queue_Push(&queue, &value);
    
    EJO_Queue_Shift(&queue, &value);
    assert(value == 3);
    EJO_Queue_Shift(&queue, &value);
    assert(value == 4);
    EJO_Queue_Shift(&queue, &value);
    assert(value == 6);
    
    value = 3;
    EJO_Queue_Push(&queue, &value);
    value = 4;
    EJO_Queue_Push(&queue, &value);
    value = 6;
    EJO_Queue_Push(&queue, &value);
    
    EJO_Queue_Shift(&queue, &value);
    assert(value == 3);
    EJO_Queue_Shift(&queue, &value);
    assert(value == 4);
    EJO_Queue_Shift(&queue, &value);
    assert(value == 6);
    
    EJO_Queue_Free(queue);
    
    return 0;
}

void* my_allocator(size_t size)
{
    printf("Allocating a size of %d bytes\n");
    
    return malloc(size);
}

void my_free(void* ptr)
{
    printf("Freeing memory at %d\n", ptr);
    
    free(ptr);
}
