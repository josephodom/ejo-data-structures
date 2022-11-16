# Basic Data Structures in C

In this project, I've created examples of some basic data structures in C.

## Queue

Struct `EJO_Queue` is a first-in, first-out structure.

```c
int value;

// Create a queue that can hold 2 values, the size of `int`
EJO_Queue* queue = EJO_Queue_Create(2, sizeof(value));

// Add 123 to the queue
value = 123;
EJO_Queue_Push(queue, &value); // 1
// Add 456 to the queue
value = 456;
EJO_Queue_Push(queue, &value); // 1
// Fail to add 789 to the queue
value = 789;
EJO_Queue_Push(queue, &value); // 0

EJO_Queue_Shift(queue, &value); // 1
printf("%d\n", value); // prints: 123
EJO_Queue_Shift(queue, &value); // 1
printf("%d\n", value); // prints: 456
EJO_Queue_Shift(queue, &value); // 0
printf("%d\n", value); // prints: 456
                       // Does not print 789

EJO_Queue_Free(queue); // Remember to free!
```
