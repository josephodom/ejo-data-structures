#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <ejo/queue.h>

void test_queue_happy_path_byte()
{
    char value;
    EJO_Queue* queue = EJO_Queue_Create(3, sizeof(value));

    // Fill up the queue
    value = 1;
    EJO_Queue_Push(queue, &value);
    value = 2;
    EJO_Queue_Push(queue, &value);
    value = 3;
    EJO_Queue_Push(queue, &value);

    // Empty the queue
    EJO_Queue_Shift(queue, &value);
    assert(value == 1);
    EJO_Queue_Shift(queue, &value);
    assert(value == 2);
    EJO_Queue_Shift(queue, &value);
    assert(value == 3);

    EJO_Queue_Free(queue);
}

void test_queue_happy_path_multibyte()
{
    char* value;
    EJO_Queue* queue = EJO_Queue_Create(3, sizeof(char) * 5);

    // Fill up the queue
    value = "Jane";
    EJO_Queue_Push(queue, &value);
    value = "Alex";
    EJO_Queue_Push(queue, &value);
    value = "Pam!";
    EJO_Queue_Push(queue, &value);

    // Empty the queue
    EJO_Queue_Shift(queue, &value);
    assert(strcmp(value, "Jane") == 0);
    EJO_Queue_Shift(queue, &value);
    assert(strcmp(value, "Alex") == 0);
    EJO_Queue_Shift(queue, &value);
    assert(strcmp(value, "Pam!") == 0);

    EJO_Queue_Free(queue);
}

void test_queue_overpush()
{
    char value;
    EJO_Queue* queue = EJO_Queue_Create(2, sizeof(value));

    value = 8;
    assert(EJO_Queue_Push(queue, &value));
    value = 9;
    assert(EJO_Queue_Push(queue, &value));
    value = 10;
    assert(!EJO_Queue_Push(queue, &value));

    assert(EJO_Queue_Shift(queue, &value));
    assert(value == 8);
    assert(EJO_Queue_Shift(queue, &value));
    assert(value == 9);
    assert(!EJO_Queue_Shift(queue, &value));
    assert(value == 9);

    EJO_Queue_Free(queue);
}

void test_queue_overshift()
{
    char value;
    EJO_Queue* queue = EJO_Queue_Create(2, sizeof(value));

    value = 11;
    assert(EJO_Queue_Push(queue, &value));
    assert(EJO_Queue_Shift(queue, &value));
    assert(value == 11);
    assert(!EJO_Queue_Shift(queue, &value));
}

void test_queue_stress()
{
    int value;
    EJO_Queue* queue = EJO_Queue_Create(3, sizeof(value));

    for (int i = 0; i < 100; i++)
    {
        assert(EJO_Queue_Push(queue, &i));
        assert(EJO_Queue_Shift(queue, &value));
        assert(value == i);
    }
}

void test_queue()
{
    test_queue_happy_path_byte();
    test_queue_happy_path_multibyte();
    test_queue_overpush();
    test_queue_overshift();
    test_queue_stress();
}
