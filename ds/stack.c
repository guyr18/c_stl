#ifndef STACK_C
#include "linked_list.c"
#include <stdio.h>

// Stack.c represents a LIFO stack data structure with three core functions:
//
//     push: Push item to the top of the stack
//     peek: Returns a pointer to the item at the top of the queue structure
//     pop: Removes the item at the top of the queue data structure
//

// Stack_container is a struct that encapsulates a stack data structure.
struct stack_container
{

    size_t size; // The current number of items in this stack.
    size_t capacity; // The max capacity allowed for items in this stack.
    struct lnode* data; // A lnode* (linked list) representing the items stored by this stack.

};

// Push(cnt, value) pushes a struct lnode* of value, value, to the top of the stack. If doing so
// would exceed the stack capacity, then the function will do nothing.
struct lnode* push(struct stack_container* cnt, const int value)
{

    // We don't have enough capacity for this. So just return the function.
    if(cnt == NULL || cnt->size + 1 == cnt->capacity)
    {

        printf("push(): stack_container must be non-null and have capacity for this value [%i]", value);   
        return NULL; 

    }

    printf("push(): value [%i] pushed to top of stack.\n", value);
    struct lnode* data = cnt->data;
    cnt->data = lead_insert(data, value);
    cnt->size++;
    return cnt->data;

}

// Peek(cnt) returns the struct lnode* at the top of the stack (or linked list in this context). If no such item
// is available due to size or a null pointer, a null pointer is returned.
struct lnode* peek(struct stack_container* cnt)
{

    if(cnt == NULL || cnt->data == NULL || cnt->size == 0 || cnt->capacity == 0)
    {

        printf("peek(): stack_container must be non-null and have a size and capacity > 0.\n");
        return NULL; 

    }

    printf("peek(): returning lnode with value [%i].\n", cnt->data->value);
    return cnt->data;

}

// Pop(cnt) pops the element at the top of the stack, if possible. If it is not, then this method simply returns.
struct lnode* pop(struct stack_container* cnt)
{

    // No items to pop or cnt is null, just return.
    if(cnt == NULL || cnt->size == 0) 
    {

        printf("pop(): stack_container must be non-null and have size > 1 to pop.\n");   
        return NULL;

    }

    struct lnode* data = cnt->data;

    // No data to pop, something is wrong as size property is wrong.
    if(data == NULL) 
    {

        printf("pop(): no data to pop.\n");
        return NULL;

    }

    printf("pop(): popped lnode with value [%i] from stack.\n", cnt->data->value);
    struct lnode* temp = data;
    data = data->next;
    free(temp);
    cnt->size--;
    cnt->data = data;
    return cnt->data;
    
}

#endif