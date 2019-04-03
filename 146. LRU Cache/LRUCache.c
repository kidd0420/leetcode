/*******************************************************************
 * Design and implement a data structure for Least Recently Used (LRU) cache. 
 * It should support the following operations: get and put.
 * 
 * get(key) - Get the value (will always be positive) of the key 
 * if the key exists in the cache, otherwise return -1.
 * 
 * put(key, value) - Set or insert the value if the key is not already present. 
 * When the cache reached its capacity, 
 * it should invalidate the least recently used item before inserting a new item.
 * 
 * Follow up:
 * Could you do both operations in O(1) time complexity?
 * 
 * Example:
 * LRUCache cache = new LRUCache( 2 capacity );
 * 
 * cache.put(1, 1);
 * cache.put(2, 2);
 * cache.get(1);       // returns 1
 * cache.put(3, 3);    // evicts key 2
 * cache.get(2);       // returns -1 (not found)
 * cache.put(4, 4);    // evicts key 1
 * cache.get(1);       // returns -1 (not found)
 * cache.get(3);       // returns 3
 * cache.get(4);       // returns 4
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UINT64	unsigned long long int
#define UINT32 unsigned int

#define CAPACITY_SHIFT	10
#define CLOSE_MAX_SIZE	1073741824
#define MAX_SIZE		4294967296

typedef struct HT {
	UINT32 Index;
	UINT32 Value;
	struct HT* Prev_HT;
	struct HT* Next_HT;
	struct HT* Prev_LRU;
	struct HT* Next_LRU;
} HashTable;

typedef struct {
	UINT64* IndexCount;
	UINT64 DefinedCap;	//User defined size
	UINT64 SetCap;		//Actually created buffer size
	UINT64 UsedCap;		//Used size
	UINT32 Divisor;
	HashTable* HeadHT;
	HashTable* TailHT;
	HashTable* HeadLRU;
	HashTable* TailLRU;
} LRUCache;


UINT64 SetCacheCapacity(UINT64 defined_capacity)
{
	UINT64 min_capacity = 1;
	UINT64 max_capacity = 1024;

	while (1) {
		if ((defined_capacity >= min_capacity) &&
			(defined_capacity <= max_capacity)) {
			UINT32 i;
			UINT64 tmp = min_capacity;

			for (i = 0; i < 10; i++) {
				if (defined_capacity == tmp) {
					return tmp;
				} else if (defined_capacity <= (tmp << 1)) {
					return tmp << 1;
				}

				tmp <<= 1;
			}

			break;
		}

		min_capacity = max_capacity;

		if (max_capacity == MAX_SIZE)
			return 0;
		else if (max_capacity == CLOSE_MAX_SIZE)
			max_capacity = MAX_SIZE;
		else
			max_capacity << CAPACITY_SHIFT;
	}

	return 0;
}


LRUCache* lRUCacheCreate(int capacity) 
{
	LRUCache* cache;
	UINT64 defined_capacity = (UINT64)capacity;

	//Return NULL if capacity is zero (invalid)
	if (capacity == 0)
		return NULL;

	cache->DefinedCap = defined_capacity;
	cache->UsedCap = 0;
	cache->SetCap = SetCacheCapacity(defined_capacity);

	if (cache->SetCap == 0)
		return NULL;
	else {
		if (cache->SetCap > 0xFFFFFFFF)
			cache->Divisor = 0xFFFFFFFF;
		else
			cache->Divisor = cache->SetCap - 1;
	}

	//Head <---> Tail, Initialize status, no data between Head and Tail
	cache->HeadHT = malloc(sizeof(HashTable));
	cache->TailHT = malloc(sizeof(HashTable));
	cache->HeadHT->Next_HT = cache->TailHT;
	cache->TailHT->Prev_HT = cache->HeadHT;
	cache->HeadLRU = malloc(sizeof(HashTable));
	cache->TailLRU = malloc(sizeof(HashTable));
	cache->HeadLRU->Next_LRU = cache->TailLRU;
	cache->TailLRU->Prev_LRU = cache->HeadLRU;

	cache->IndexCount = malloc(cache->SetCap * sizeof(UINT32));
	memset(cache->IndexCount, 0, cache->SetCap * sizeof(UINT32));

	return cache;
}


int GetCacheIndex(LRUCache* obj, int key)
{
	return (key & obj->Divisor);
}


int lRUCacheGet(LRUCache* obj, int key) 
{

}

void lRUCachePut(LRUCache* obj, int key, int value) 
{

}

void lRUCacheFree(LRUCache* obj) {
	UINT32 i;
	HashTable* HT = obj->HeadHT;
	HashTable* Next_HT;

	while (HT != NULL) {
		Next_HT = HT->Next_HT;
		free(HT);
		HT = Next_HT;
	}

	free(obj->IndexCount);
	free(obj);
}


int main ()
{
    return 0;
}


/**
 * Your LRUCache struct will be instantiated and called as such:
 * struct LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */