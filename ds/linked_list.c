#ifndef LL_C
#include <stdlib.h>
#include <stdio.h>

// Linked_list.c represents a singly linked list with common functions that would find for manipulating a
// standard linked list. These include, but are not limited to insertion, deletion, and searching.

// A struct representing a singly-linked list. It contains an integer value
// and a next pointer of type struct lnode.
struct lnode
{

    int value; // Value of this lnode.
    struct lnode* next; // Next node in chain.

};

// Log_contents(root) prints the values associated with each lnode struct of root. If root is null,
// the function will do nothing.
void log_contents(struct lnode* root)
{

    if(root == NULL) { 
        
        printf("log_contents(): No contents to print, returning function.\n");
        return; 

    }

    while(root != NULL)
    {

        printf("%i", root->value);

        if(root->next != NULL)
        {

            printf("->");

        }

        root = root->next;

    }

    printf("\n");

}

// Erase_node_of(root, value) deletes the first occurrence of value in struct lnode* root. If it is successful, a struct lnode*
// to the head of the linked list is returned. Otherwise, null will be returned.
struct lnode* erase_node_of(struct lnode* root, const int value)
{

    // Empty list.
    if(root == NULL) { 

        printf("erase_node_of(): Can\'t delete from an empty list, returning function.\n");   
        return NULL; 

    }

    struct lnode* prev = NULL;
    struct lnode* cur = root;

    while(cur != NULL)
    {

        if(cur->value == value)
        {

            if(prev == NULL)
            {

                printf("erase_node_of(): Deleting linked list node with value [%i].\n", value);
                free(cur);
                cur = NULL;
                printf("erase_node_of(): Node with value [%i] deleted.\n", value);
                return NULL;

            }

            printf("erase_node_of(): Deleting linked list node with value [%i].\n", value);
            struct lnode* next = cur->next;
            prev->next = next;
            free(cur);
            printf("erase_node_of(): Node with value [%i] deleted.\n", value);
            return root;

        }

        prev = cur;
        cur = cur->next;

    }

    // Value is not present in the list.
    printf("erase_node_of(): Value [%i] not found in linked list.\n", value);
    return NULL;

}

// Lead_insert(root, value) inserts a struct lnode* with the value, value, at the beginning of the linked list.
// It returns the struct lnode*.
struct lnode* lead_insert(struct lnode* root, const int value)
{

    // Empty list, just allocate space for root and assign value.
    if(root == NULL) 
    {

        printf("lead_insert(): list empty; insert linked list node with value [%i] at head of linked list.\n", value);
        root = (struct lnode*)malloc(sizeof(struct lnode));
        root->value = value;
        return root;

    }

    // One or more nodes.
    printf("lead_insert(): list non-empty; insert linked list node with value [%i] at head of linked list.\n", value);
    struct lnode* ptr = (struct lnode*)malloc(sizeof(struct lnode));
    struct lnode* old_head = root;
    ptr->value = value;
    root = ptr;
    root->next = old_head;
    return root;

}

// Get_integer_repr(root) returns the integer representing by the linked list, starting at the head
// node. For example, suppose we have the following linked list: 1 -> 2 -> 3. This method would return
// 123.
int get_integer_repr(struct lnode* root)
{

    // Linked list is empty. There is no integer representation. Return 0.
    if(root == NULL) { 

        printf("get_integer_repr(): empty list supplied, root parameter is null.\n");
        return 0;

    }

    int repr = 0;
    int is_first_node = 1;
    int is_negative = 0;

    while(root != NULL)
    {

        repr = (repr * 10) + root->value;

        // If first value is negative, take note of this. We will compute the value
        // as positive and check this flag before returning the value. If it equal to 1,
        // we can negate the return value.
        if(is_first_node == 1 && root->value < 0)
        {

            repr *= -1;
            is_first_node = 0;
            is_negative = 1;

        }

        root = root->next;

    }

    printf("get_integer_repr(): returning integer representation [%i].\n", is_negative ? repr * -1 : repr);
    return is_negative ? repr * -1 : repr;

}

// Trail_insert(root, end, value) appends a struct lnode* with value, value, to the end of the linked list
// root (or end->next). There are three cases for this algorithm:
//
//  root is null => We dynamically allocate to the heap in constant time. The end pointer does not matter, because
//                  the list is empty.
//
//  end is null => We have a root pointer, but do not have an end pointer. Because of this we will need to traverse
//                 the list, which will take linear time and then perform dynamic allocation.
//
//  root and end are non-null => This is the ideal case giving the provided parameters and will allow us to allocate
//                               memory in constant time by using the end->next pointer.
//
struct lnode* trail_insert(struct lnode* root, struct lnode* end, const int value)
{

    // If root is null, then the end pointer does not matter. We just allocate space for
    // the root pointer and the initialize the correct value.
    if(root == NULL)
    {

        printf("trail_insert(): list is empty. allocating for and assigning node with value [%i].\n", value);
        root = (struct lnode*)malloc(sizeof(struct lnode));
        root->value = value;
        return root;

    }

    // root is not null, but end is, as a result we will need to traverse the linked list
    // and find the end node in order to allocate for it in the heap.
    if(end == NULL)
    {

        struct lnode* main_root = root;

        while(root != NULL)
        {

            if(root->next == NULL)
            {

                printf("trail_insert(): list is non-empty, inserting value [%i] at end, given null end pointer.\n", value);
                root->next = (struct lnode*)malloc(sizeof(struct lnode));
                root->next->value = value;
                break;

            }

            root = root->next;

        }

        return main_root;

    }

    // Root and end are non-null we can just allocate in constant time to the heap by using end->next. We
    // assume that root and end are interconnected.
    printf("trail_insert(): list is non-empty, inserting value [%i] at end, given two non-null pointers.\n", value);
    end->next = (struct lnode*)malloc(sizeof(struct lnode));
    end->next->value = value;
    return root;

}

// Reverse_list(root) takes a lnode struct pointer and reverses its contents.
struct lnode* reverse_list(struct lnode* root)
{

    struct lnode* prev = NULL;
    struct lnode* cur = root;

    printf("reverse_list(): reversing linked list.\n");
    while(cur != NULL)
    {

        struct lnode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;

    }

    return prev != NULL ? prev : root;

}

// Find_node_with_value(value, root) searches for value, value, inside linked list root. If the value is found,
// the containing lnode struct pointer is returned. Otherwise, null is returned.
struct lnode* find_node_with_value(const int value, struct lnode* root)
{

    printf("find_node_with_value(): searching for node with value [%i].\n", value);

    while(root != NULL)
    {

        if(root->value == value)
        {

            printf("find_node_with_value(): value [%i] found.\n", value);
            return root;

        }

        root = root->next;

    }

    printf("find_node_with_value(): value [%i] does not exist.\n", value);
    return NULL;

}

// Contains_value(value, root) returns 1 if value, value, is found within linked list root. Otherwise, this method
// returns 0.
int contains_value(const int value, struct lnode* root)
{

    printf("contains_value(): searching for value [%i].\n", value);

    while(root != NULL)
    {

        if(root->value == value) 
        {

            printf("contains_value(): value [%i] exists.\n", value);
            return 1;

        }

        root = root->next;

    }

    printf("contains_value(): value [%i] does not exist.\n", value);
    return 0;

}

// Build_from_array(src) takes an array of integers, src, and builds a linked list (struct lnode*), then returns
// a pointer to the head of the corresponding list.
struct lnode* build_from_array(int src[], const size_t n)
{

    if(n == 0 || src == NULL) { 

        printf("build_from_array(): can\'t build a linked list from an empty array, returning function.\n");   
        return NULL; 

    }
    
    struct lnode* main_head = NULL;
    size_t index = 1;
    struct lnode* root = (struct lnode*)malloc(sizeof(struct lnode));
    root->value = src[0];
    main_head = root;

    printf("build_from_array(): building linked list from array.\n");
    while(index < n)
    {

        root->next = (struct lnode*)malloc(sizeof(struct lnode));
        root->next->value = src[index];
        root = root->next;
        index++;

    }

    printf("build_from_array(): linked list built.\n");
    return main_head;

}

#endif