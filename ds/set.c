#ifndef SET_C
#if !defined(BUF_SIZE)
#define BUF_SIZE 256
#endif

#include "hash_map.c"
#include <string.h>

// A set represents a collection of objects with no repetition. This is implemented by using the hash_map.c
// implementation. This allows for constant amortized run-time on all functions. i.e.: inserting a value,
// removing a value, and fetching a value, amongst other common utility methods.

// Set_data struct used to simulate set object instantiation.
struct set_data
{

    // Hash_map_settings struct required for this set. This struct
    // will need to be initialized correctly! For an example of this please
    // refer to tests/test_hash_map.c.
    struct hash_map_settings settings;

};

// Add(data, value) adds an element with a value, value, if possible. If this value currently exists in the set it 
// will not be added. This method returns 1 if the operation is successful. And otherwise, 0.
int add(struct set_data* data, const int value)
{

    printf("add(): set add invoked on value [%i].\n", value);
    char buf[BUF_SIZE];
    sprintf(buf, "%d", value);
    return put(buf, value, &data->settings) != NULL ? 1 : 0;
   
}

// Discard(data, value) removes value, value, if it exists. If this operation successfully performs a removal, 1
// is returned. Otherwise, 0, is returned.
int discard(struct set_data* data, const int value)
{

    char buf[BUF_SIZE];
    sprintf(buf, "%d", value);
    return remove_key(buf, &data->settings);

}

// Contains(data, value) returns 1 if an element exists with a value of value. Otherwise, it will return 0.
int contains(struct set_data* data, const int value)
{

    printf("contains(): set contains invoked on value [%i].\n", value);
    char buf[BUF_SIZE];
    sprintf(buf, "%d", value);
    return get(buf, &data->settings) != NULL ? 1 : 0;

}

// Size(settings) returns the length of the set object represented by parameter data.
size_t size(const struct set_data* data) 
{

    return data->settings.total_nodes;

}

#endif