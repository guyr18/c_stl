#include "../ds/linked_list.c"
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

    // Try to erase the first occurrence of a node with value 2. Our current list is 1->2->3, so our new
    // list should reflect 1->3.
    erase_node_of(my_linked_list, 2);

    // Verify contents. Our list is 1->3.
    log_contents(my_linked_list);

    // Invoke the same function to confirm that a non-existent node value cannot be deleted.
    erase_node_of(my_linked_list, 2);

    // Verify contents. Our list is still 1->3.
    log_contents(my_linked_list);

    // Insert a node at the head of our linked list, I chose value 9 here. Our new list in theory
    // should be 9 -> 1 -> 3. NOTE: it is important that we perform assignment here.
    my_linked_list = lead_insert(my_linked_list, 9);

    // Verify this. It is indeed 9 -> 1 -> 3.
    log_contents(my_linked_list);

    // Test get_integer_repr() method. Given our linked list, we should get 913. We can analyze the standard output
    // to verify the result of the function.
    get_integer_repr(my_linked_list);
    
    // Test trail_insert(..) method, given our current linked list of: 9 -> 1 -> 3, our new linked list should append 
    // a particular value to the end of the linked list. Suppose, we we want to add value 5. Our new linked list should
    // be 9 -> 1 -> 3 -> 5. The time complexity varies based on the pointers that you are able to supply. Read the
    // documentation of trail_insert() in linked_list.c for more details.
    my_linked_list = trail_insert(my_linked_list, NULL, 5);

    // Verify contents.
    log_contents(my_linked_list);

    // Here we attempt to reverse our linked list.
    my_linked_list = reverse_list(my_linked_list);

    // Verify contents. Indeed it is reversed, per the output.
    log_contents(my_linked_list);

    // Check if a certain value exists in our linked list. We will check for a number that we know exists and one that
    // does not. Our current linked list is: 5->3->1->9. So lets try 1 and 50.
    find_node_with_value(1, my_linked_list);
    find_node_with_value(50, my_linked_list);

    // This method returns a struct lnode*. It will be null if it does not exist, and non-null if it does.
    // Next, we will test our contains_value() method. It is similarly to the previous method except that it
    // returns 1 if a value exists and 0 if it does not.
    contains_value(1, my_linked_list);
    contains_value(50, my_linked_list);

    // Free memory.
    while(my_linked_list != NULL)
    {

        struct lnode* next = my_linked_list->next;
        free(my_linked_list);
        my_linked_list = next;

    }

    return 0;

}