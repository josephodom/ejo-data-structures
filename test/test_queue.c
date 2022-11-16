#include <assert.h>

#include <ejo/queue.h>

void test_queue_happy_path()
{
    char value;
    EJO_Queue* queue = EJO_Queue_Create(3, sizeof(value));

    EJO_Queue_Free(queue);
}

void test_queue()
{
    test_queue_happy_path();
}
