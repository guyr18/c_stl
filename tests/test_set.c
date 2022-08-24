#include "../ds/set.c"
#include <stdio.h>

int main(void)
{

    // Create a hash_map_settings struct. This structure defines properties that indicate the current state of the hash map.
    // These properties include the current number of buckets occupied, the total number of keys present in the hashmap,
    // the the maximum capacity, and the data representation itself, which is an array of struct bucket_node*(s).
    // This is an array of linked lists, which will support our chaining implementation. 
    //
    // If you would like to define a custom capacity, you may do so by specifying it in your hash_map_settings struct, otherwise
    // the macro, DEF_HM_CAP, will be defaulted to. Do not touch the below properties otherwise. It may lead to undefined behavior.
    struct hash_map_settings settings = {0, 0, 0, NULL};
    
    // We need to initialize our hash_map_settings field to the struct we previously created.
    struct set_data data = {settings};

    // Lets start by adding some values.
    int index = 0;
    int upper_bound = 3;
    int values[] = {1, 2, 3};
    
    while(index < upper_bound)
    {

        add(&data, values[index]);
        index++;

    }

    // Now our set should consist of three values: {1, 2, 3}. It should output 3.
    printf("Current size = %li\n", size(&data));

    // Let's see if repetition is being enforced properly by attempting to add a duplicate key, say 2.
    add(&data, 2);

    // Verify the length. It looks good, it is still 3.
    printf("Current size = %li\n", size(&data));

    // Next, we have a contains() method that we would like to test. It will allow us to verify if our
    // set contains a specific element in constant time.
    int has_1 = contains(&data, 1);
    int has_3 = contains(&data, 3);
    int has_100 = contains(&data, 100);
    printf("Does set contain value [%i]? %i\n", 1, has_1);
    printf("Does set contain value [%i]? %i\n", 3, has_3);
    printf("Does set contain value [%i]? %i\n", 100, has_100);

    // According to the output, 1 and 3 are in our set, but 100 does not exist. Since our set is = {1, 2, 3}, this 
    // is correct! Lastly, we will run a test for our discard method (removing elements).

    // Let's test an edge-case: removing an element that clearly does not exist. Our size() function should still return 3.
    discard(&data, 200);

    // Verify size.
    printf("Current size = %li\n", size(&data));

    // Okay, so now we will remove two elements that definitely exist: 1 and 2. We'll also check the size following each removal.
    discard(&data, 1);
    printf("Updated size = %li\n", size(&data));
    discard(&data, 2);
    printf("Updated size = %li\n", size(&data));

    // Free memory.
    struct bucket_node** cache = settings.cache;
    int idx = 0;

    while(idx < settings.capacity)
    {

        struct bucket_node* temp_bucket = cache[idx];

        while(temp_bucket != NULL)
        {

            struct bucket_node* next = temp_bucket->next;
            free(temp_bucket);
            temp_bucket = next;

        }

        idx++;

    }

    return 0;

}