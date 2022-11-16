#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void* my_allocator(unsigned long size);
void my_free(void* ptr);

#define EJO_DEFINE
#define EJO_ALLOCATE my_allocator
#define EJO_FREE my_free
#include <ejo/queue.h>
#include <ejo/stack.h>

extern void test_queue();
extern void test_stack();

int main()
{
    printf("Hello, World!\n");
    
    char value;
    unsigned long lol;
    
    test_queue();
    
    return 0;
}

void* my_allocator(unsigned long size)
{
    printf("Allocating a size of %zu bytes\n", size);
    
    return malloc(size);
}

void my_free(void* ptr)
{
    printf("Freeing memory\n");
    
    free(ptr);
}
