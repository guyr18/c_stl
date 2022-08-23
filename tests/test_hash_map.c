#include "../ds/hash_map.c"
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

    // Put the a key "tiger" with a value 5 into our hashmap.
    put("tiger", 5, &settings);

    // Here we test out our get method. The only key in the map as of now is "tiger". So, "tige" should return 0 (to indicate false).
    // Conversely, "tiger" should return 1 (to indicate true).
    struct bucket_node* node1 = get("tige", &settings);
    int success1 = node1 != NULL ? 1 : 0;
    printf("Does hashmap contain key [%s]? %i\n", "tige", success1);

    struct bucket_node* node2 = get("tiger", &settings);
    int success2 = node2 != NULL ? 1 : 0;
    printf("Does hashmap contain key [%s]? %i\n", "tiger", success2);

    // Create array of strings to test chaining by attempting to put all elements.
    // Some should result in duplication output, while others will succeed by inserting them
    // to a new bucket or the top of an existing bucket (given a collision!).
    const char* arrayOfStrings[] = {"cat", "dog", "duck", "tiger", "dog"};
    size_t index = 0;
    const size_t arrLen = 5;

    // Iterate through arrayOfStrings and call put() at each index.
    while(index < arrLen)
    {

        put(arrayOfStrings[index], index, &settings);
        index++;

    }

    return 0;

}