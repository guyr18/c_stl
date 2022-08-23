#include "ds/linked_list.c"
#include <stdio.h>

int main(void)
{

    // To start, we specify an array of integers and we are going to build a small linked list from these values.
    // You may build a linked list of any size by using the build_from_array method as such:
    int values[] = {1, 2, 3};
    struct lnode* my_linked_list = build_from_array(values, 3);

    // Log_contents prints out the contents of the linked_list. This is great for debugging! So, we can make sure our
    // linked_list was build correctly. Alternatively, you may iterate until you encounter a null node starting at
    // the head (my_linked_list).
    log_contents(my_linked_list);

    my_linked_list = erase_node_of(my_linked_list, 2);
    
    log_contents(my_linked_list);

    return 0;

}