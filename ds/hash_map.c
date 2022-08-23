#ifndef HM_C
#include <stdlib.h>
#include <stdio.h>
#if !defined(DEF_HM_CAP)
#define DEF_HM_CAP 20
#endif

// Bucket_node is a struct representing a key-value pair per a hashmap instance.
// It is a singly linked list with the addition of a key and value variable.
struct bucket_node 
{

    const char* key; // A const char* (string) representing the key for this node.
    int value; // A 32-bit integer representing the value of this node.
    struct bucket_node* next; // A struct bucket_node* representing the next node in the linked list.

};

// Hash_map_settings is a struct that represents the configuration of a particular hashmap 
// instance. The properties are documented.
struct hash_map_settings
{

    size_t cur_buckets_filled; // The total number of buckets that are currently in use.
    size_t total_nodes; // The total number of keys present.
    size_t capacity; // The capacity of the bucket list.
    struct bucket_node** cache;

};

// Get_hash(key, settings) returns the hashed bucket index to look in. It does this by performing
// by computing the ASCII sum of the characters in key and obtaining the remainder of the cache
// capacity.
static int get_hash(const char* key, const struct hash_map_settings* settings)
{

    int ascii_sum = 0;
    char c;

    // Iterate until we see a null-terminator character.
    while((c = *key++) != '\0')
    {

        // Compute ascii sum at each iteration and add it to ascii_sum.
        ascii_sum += (int)c;

    }

    return ascii_sum % settings->capacity;

}

// Get(key, settings) returns a struct bucket_node* representing the node of the bucket with key, key. If it does not exist, return null.
struct bucket_node* get(const char* key, const struct hash_map_settings* settings)
{
    
    // If there are no current nodes or settings is null, there is nothing for this function to get. Just return null.
    if(settings == NULL || settings->capacity == 0 || settings->cur_buckets_filled == 0 || settings->total_nodes == 0)
    {

        return NULL;

    }

    int bucket_index = get_hash(key, settings);
    struct bucket_node* bucket_head = settings->cache[bucket_index];
    
    // Key does not exist.
    if(bucket_head == NULL) { 
        return NULL; }

    // Loop until the current item in our bucket (bucket_head) is null or we find the key that we are looking for.
    while(bucket_head != NULL && bucket_head->key != key) { bucket_head = bucket_head->next; }

    // Return the result; if it is null return a null pointer, otherwise return the bucket that we found.
    return bucket_head == NULL ? NULL : bucket_head;

}

// Put(key, value, settings) inserts key, key, and value, value, as a key-value pair. It updates several properties in 
// settings as needed. If it is unsuccessful, a null pointer is returned. Otherwise, the head of the bucket that it is 
// inserted in is returned; struct bucket_node*.
struct bucket_node* put(const char* key, const int value, struct hash_map_settings* settings)
{

    if(settings == NULL)
    {

        return NULL;

    }

    if(settings->total_nodes == 0)
    {

        printf("put(): initializing hash_map_settings data.\n");
        settings->cur_buckets_filled = 0;
        settings->capacity = settings->capacity == 0 ? DEF_HM_CAP : settings->capacity;
        settings->cache = (struct bucket_node**)malloc(settings->capacity * sizeof(struct bucket_node*));  
        printf("put(): hash_map_settings data initialized.\n");      
        
    }

    int bucket_index = get_hash(key, settings);
    struct bucket_node* bucket = settings->cache[bucket_index];

    // This is a new bucket.
    if(bucket == NULL)
    {

        printf("put(): key[%s] is being hashed to a new bucket.\n", key);
        bucket = (struct bucket_node*)malloc(sizeof(struct bucket_node));
        bucket->key = key;
        bucket->value = value;
        settings->cur_buckets_filled++;
        settings->total_nodes++;
        settings->cache[bucket_index] = bucket;
        printf("put(): key[%s] was hashed to a new bucket.\n", key);
        return bucket;

    }

    struct bucket_node* bucket_head = bucket;

    // Search across the bucket for the key we are considering adding.
    while(bucket != NULL)
    {

        // This is a duplicate key, we cannot add it. Just return null.
        if(bucket->key == key) 
        {

            printf("put(): key[%s] is a duplicate key; returning function.\n", key);
            return NULL;
            
        }

        bucket = bucket->next;

    }

    printf("put(): key[%s] is being hashed to bucket index => %i.\n", key, bucket_index);
    struct bucket_node* temp = bucket_head;
    bucket_head = (struct bucket_node*)malloc(sizeof(struct bucket_node));
    bucket_head->key = key;
    bucket_head->value = value;
    bucket_head->next = temp;
    settings->total_nodes++;
    settings->cache[bucket_index] = bucket_head;
    printf("put(): key[%s] hashed to head of linked list at bucket index => %i.\n", key, bucket_index);
    return bucket_head;

}

#endif