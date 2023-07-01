#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CACHE_SIZE 4

typedef struct {
    int key;
    int value;
} CacheEntry;

CacheEntry cache[CACHE_SIZE];

void initCache() {
    for (int i = 0; i < CACHE_SIZE; ++i) {
        cache[i].key = -1; // -1 indicates an empty cache entry
        cache[i].value = -1;
    }
}

int findCacheIndex(int key) {
    for (int i = 0; i < CACHE_SIZE; ++i) {
        if (cache[i].key == key) {
            return i; // Return the index if key is found in cache
        }
    }
    return -1; // Return -1 if key is not found in cache
}

void shiftCacheEntries(int startIndex) {
    for (int i = startIndex; i > 0; --i) {
        cache[i] = cache[i - 1]; // Shift cache entries to the right
    }
}

void updateCache(int index) {
    CacheEntry temp = cache[index]; // Store the cache entry temporarily
    shiftCacheEntries(index);
    cache[0] = temp; // Move the cache entry to the front
}

int get(int key) {
    int index = findCacheIndex(key);
    
    if (index != -1) {
        updateCache(index); // Update cache entry position
        return cache[0].value; // Return the value
    }
    
    return -1; // Cache miss, return -1
}

void put(int key, int value) {
    int index = findCacheIndex(key);
    
    if (index != -1) {
        updateCache(index); // Update cache entry position
        cache[0].value = value; // Update the value
    } else {
        shiftCacheEntries(CACHE_SIZE - 1); // Shift cache entries to the right
        cache[0].key = key; // Insert new key at the front
        cache[0].value = value; // Insert new value at the front
    }
}

void printCache() {
    printf("Cache Contents:\n");
    for (int i = 0; i < CACHE_SIZE; ++i) {
        if (cache[i].key != -1) {
            printf("Key: %d, Value: %d\n", cache[i].key, cache[i].value);
        }
    }
    printf("-------------------------------\n");
}

int main() {
    initCache();
    
    put(1, 10);
    put(2, 20);
    put(3, 30);
    put(4, 40);
    
    printCache(); // Cache should be: 4->3->2->1
    
    get(3); // Accessing key 3, it should move to the front
    
    printCache(); // Cache should be: 3->4->2->1
    
    put(5, 50); // Inserting a new key 5, causing eviction of key 1
    
    printCache(); // Cache should be: 5->3->4->2
    
    return 0;
}

