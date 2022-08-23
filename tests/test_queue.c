#include "../ds/queue.c"
#include <stdio.h>

int main(void)
{

    // You will need to allocate memory or queue.c will NOT work. It assumes that
    // you have allocated memory to the heap.
    struct lnode* data = (struct lnode*)malloc(sizeof(struct lnode));
    struct queue_container qc = {0, 20, data};

    // Our queue consists of: 5.
    push(&qc, 5);

    // Our stack consists of: 5, 1.
    push(&qc, 1);

    // Our stack consists of 5, 1, 52.
    push(&qc, 52);

    // Pop. Our new stack is 1, 52.
    pop(&qc);

    // Peek to verify this.
    peek(&qc);

    // Free memory.
    while(data != NULL)
    {

        struct lnode* next = data->next;
        free(data);
        data = next;

    }

    return 0;

}