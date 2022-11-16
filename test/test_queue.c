#include <assert.h>
#include <stdio.h>
#include <string.h>

#define EJO_ASSERT_QUEUE(x) {\
    if (!(x)) { \
        fprintf(stderr, "FAILURE: " #x "\n"); \
        assert(x); \
    } \
}

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
    EJO_ASSERT_QUEUE(value == 1);
    EJO_Queue_Shift(queue, &value);
    EJO_ASSERT_QUEUE(value == 2);
    EJO_Queue_Shift(queue, &value);
    EJO_ASSERT_QUEUE(value == 3);

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
    EJO_ASSERT_QUEUE(strcmp(value, "Jane") == 0);
    EJO_Queue_Shift(queue, &value);
    EJO_ASSERT_QUEUE(strcmp(value, "Alex") == 0);
    EJO_Queue_Shift(queue, &value);
    EJO_ASSERT_QUEUE(strcmp(value, "Pam!") == 0);

    EJO_Queue_Free(queue);
}

void test_queue_overpush()
{
    char value;
    EJO_Queue* queue = EJO_Queue_Create(2, sizeof(value));

    value = 8;
    EJO_ASSERT_QUEUE(EJO_Queue_Push(queue, &value));
    value = 9;
    EJO_ASSERT_QUEUE(EJO_Queue_Push(queue, &value));
    value = 10;
    EJO_ASSERT_QUEUE(!EJO_Queue_Push(queue, &value));

    EJO_ASSERT_QUEUE(EJO_Queue_Shift(queue, &value));
    EJO_ASSERT_QUEUE(value == 8);
    EJO_ASSERT_QUEUE(EJO_Queue_Shift(queue, &value));
    EJO_ASSERT_QUEUE(value == 9);
    EJO_ASSERT_QUEUE(!EJO_Queue_Shift(queue, &value));
    EJO_ASSERT_QUEUE(value == 9);

    EJO_Queue_Free(queue);
}

void test_queue_overshift()
{
    char value;
    EJO_Queue* queue = EJO_Queue_Create(2, sizeof(value));

    value = 11;
    EJO_ASSERT_QUEUE(EJO_Queue_Push(queue, &value));
    EJO_ASSERT_QUEUE(EJO_Queue_Shift(queue, &value));
    EJO_ASSERT_QUEUE(value == 11);
    EJO_ASSERT_QUEUE(!EJO_Queue_Shift(queue, &value));
}

void test_queue_stress()
{
    int value;
    EJO_Queue* queue = EJO_Queue_Create(1, sizeof(value));

    for (int i = 0; i < 999; i++)
    {
        EJO_ASSERT_QUEUE(EJO_Queue_Push(queue, &i));
        EJO_ASSERT_QUEUE(EJO_Queue_Shift(queue, &value));
        EJO_ASSERT_QUEUE(value == i);
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
