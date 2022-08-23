#ifndef QUEUE_C
#include "linked_list.c"
#include <stdio.h>

// Queue.c represents a FIFO queue data structure with three core functions:
//
//     push: Push item to the rear of the queue
//     peek: Returns a pointer to the item at the top of the queue structure
//     pop: Removes the item at the top of the queue data structure
//

// Queue_container is a struct that encapsulates a queue data structure.
struct queue_container
{

    size_t size; // The current number of items in this queue.
    size_t capacity; // The max capacity allowed for items in this queue.
    struct lnode* data; // A lnode* (linked list) representing the items stored by this queue.
    struct lnode* end; // A lnode* (linked list) points to the last item in the queue.

};

// Push(cnt, value) pushes a struct lnode* of value, value, to the rear of the queue. If doing so
// would exceed the queue capacity, then the function will do nothing.
struct lnode* push(struct queue_container* cnt, const int value)
{

    // We don't have enough capacity for this. So just return the function.
    if(cnt == NULL || cnt->size + 1 == cnt->capacity)
    {

        printf("push(): queue_container must be non-null and have a size + 1 != capacity.\n");
        return NULL; 

    }

    printf("push(): pushing value [%i] to rear of queue.\n", value);
    struct lnode* data = cnt->data;
    const int is_empty = data == NULL ? 1 : 0;
    cnt->data = trail_insert(data, cnt->end, value);
    cnt->end = is_empty ? cnt->data : cnt->end->next;
    cnt->size++;
    return cnt->data;

}

// Peek(cnt) returns the struct lnode* at the top of the queue (or linked list in this context). If no such item
// is available due to size or a null pointer, a null pointer is returned.
struct lnode* peek(struct queue_container* cnt)
{

    if(cnt == NULL || cnt->data == NULL || cnt->size == 0 || cnt->capacity == 0)
    {

        printf("peek(): queue_container must be non-null and have data non-null, size, capacity > 0.\n");   
        return NULL; 

    }

    printf("peek(): returning node with value [%i]", cnt->data->value);
    return cnt->data;

}

// Pop(cnt) pops the element at the top of the queue, if possible. If it is not, then this method simply returns.
struct lnode* pop(struct queue_container* cnt)
{

    // No items to pop or cnt is null, just return.
    if(cnt == NULL || cnt->size == 0)
    {

        printf("pop(): cannot pop from null queue_container, size must be > 0.\n");   
        return NULL; 

    }

    struct lnode* data = cnt->data;

    // No data to pop, something is wrong as size property is wrong.
    if(data == NULL) 
    {

        printf("pop(): no data allocated within queue_container.\n");   
        return NULL; 

    }

    struct lnode* temp = data;
    data = data->next;

    if(temp == cnt->end || cnt->size == 1)
    {

        cnt->end = NULL;

    }

    free(temp);
    cnt->size--;
    cnt->data = data;
    printf("pop(): popped value [%i] from queue_container.\n", cnt->data->value);
    return cnt->data;
    
}

#endif