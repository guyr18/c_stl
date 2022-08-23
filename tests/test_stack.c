#include "../ds/stack.c"
#include <stdio.h>

int main(void)
{

    // You will need to allocate memory or stack.c will NOT work. It assumes that
    // you have allocated memory to the heap.
    struct lnode* data = (struct lnode*)malloc(sizeof(struct lnode));
    struct stack_container sc = {0, 20, data};

    // Our stack consists of: 5.
    push(&sc, 5);

    // Our stack consists of: 1, 5.
    push(&sc, 1);

    // Our stack consists of 52, 1, 5.
    push(&sc, 52);

    // Pop. Our new stack is 1, 5.
    pop(&sc);

    // Peek to verify this.
    peek(&sc);

    // Free memory.
    while(data != NULL)
    {

        struct lnode* next = data->next;
        free(data);
        data = next;

    }

    return 0;

}