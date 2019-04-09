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
	UINT64 DefinedCap;	//User defined size
	UINT64 SetCap;		//Actually created buffer size
	UINT64 UsedCap;		//Used size
	UINT32 Divisor;
	HashTable* HeadHT;
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
			max_capacity <<= CAPACITY_SHIFT;
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

	cache = malloc(sizeof(LRUCache));

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
	//printf("[%s:%d]\n", __func__, __LINE__);

	cache->HeadHT = malloc(cache->SetCap * sizeof(HashTable));
	memset(cache->HeadHT, 0, cache->SetCap * sizeof(HashTable));

	//Head <---> Tail, Initialize status, no data between Head and Tail
	cache->HeadLRU = malloc(sizeof(HashTable));
	cache->TailLRU = malloc(sizeof(HashTable));
	memset(cache->HeadLRU, 0, sizeof(HashTable));
	memset(cache->TailLRU, 0, sizeof(HashTable));
	cache->HeadLRU->Next_LRU = cache->TailLRU;
	cache->TailLRU->Prev_LRU = cache->HeadLRU;

	return cache;
}


int GetCacheIndex(LRUCache* obj, int key)
{
	return (key & obj->Divisor);
}

void lRUCacheAdd(LRUCache* obj, int idx, int key, int value)
{
	HashTable* HeadHT = &obj->HeadHT[idx];
	HashTable* new;

	//Allocate memory for insert data
	new = malloc(sizeof(HashTable));

	//Set key and value
	new->Index = key;
	new->Value = value;
	//HeadHT <--- --->Orig 1st HT
	//	         ^
	//	        New
	if (HeadHT->Next_HT != NULL)
		HeadHT->Next_HT->Prev_HT = new;
	new->Next_HT = HeadHT->Next_HT;
	new->Prev_HT = HeadHT;
	HeadHT->Next_HT = new;

	//HeadLRU <--- --->Orig 1st LRU
	//	          ^
	//	         New
	obj->HeadLRU->Next_LRU->Prev_LRU = new;
	new->Prev_LRU = obj->HeadLRU;
	new->Next_LRU = obj->HeadLRU->Next_LRU;
	obj->HeadLRU->Next_LRU = new;

	//Count used
	obj->UsedCap++;
}

void lRUCacheRemove(LRUCache* obj)
{
	HashTable* remove = obj->TailLRU->Prev_LRU;

	remove->Prev_LRU->Next_LRU = obj->TailLRU;
	obj->TailLRU->Prev_LRU = remove->Prev_LRU;
	remove->Prev_HT->Next_HT = remove->Next_HT;
	remove->Next_HT->Prev_HT = remove->Prev_HT;

	free(remove);
}

void lRUCacheRefresh(LRUCache* obj, int idx, HashTable* refresh, int value)
{
	HashTable* HeadHT = &obj->HeadHT[idx];
	HashTable* HeadLRU = obj->HeadLRU;

	refresh->Value = value;
	refresh->Prev_LRU->Next_LRU = refresh->Next_LRU;
	refresh->Next_LRU->Prev_LRU = refresh->Prev_LRU;

	HeadHT->Next_HT->Prev_HT = refresh;
	refresh->Next_HT = HeadHT->Next_HT;
	refresh->Prev_HT = HeadHT;
	HeadHT->Next_HT = refresh;

	HeadLRU->Next_LRU->Prev_LRU = refresh;
	refresh->Prev_LRU = HeadLRU;
	refresh->Next_LRU = HeadLRU->Next_LRU;
	HeadLRU->Next_LRU = refresh;
}

int lRUCacheGet(LRUCache* obj, int key)
{
	int idx = GetCacheIndex(obj, key);
	HashTable* HT = obj->HeadHT[idx].Next_HT;

	while (1) {
		if (HT == NULL)
			return -1;

		if (HT->Index == (UINT32)key) {
			lRUCacheRefresh(obj, idx, HT, HT->Value);
			return HT->Value;
		}	

		HT = HT->Next_HT;
	}

	return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value)
{
	int idx = GetCacheIndex(obj, key);
	HashTable* HT = obj->HeadHT[idx].Next_HT;

	//printf("idx: %d\n", idx);

	while (1) {
		if (HT == NULL) {
			lRUCacheAdd(obj, idx, key, value);

			if (obj->UsedCap == obj->DefinedCap)
				lRUCacheRemove(obj);

			break;
		}

		if (HT->Index == (UINT32)key) {
			lRUCacheRefresh(obj, idx, HT, value);
			break;
		}

		HT = HT->Next_HT;
	}
}

void lRUCacheFree(LRUCache* obj) {
	UINT32 idx = 0;
	HashTable* HT;
	HashTable* Next_HT;

	if (obj == NULL)
		return;

	while (idx < obj->SetCap) {
		HT = obj->HeadHT[idx].Next_HT;

		while (HT != NULL) {
			Next_HT = HT->Next_HT;
			free(HT);
			HT = Next_HT;
		}

		idx++;
	}

	free(obj->HeadLRU);
	free(obj->TailLRU);
	free(obj);
}


int main ()
{
	LRUCache* cache;
	int value;

	cache = lRUCacheCreate(11);

	printf("Define size: %lld\n", cache->DefinedCap);
	printf("Set size   : %lld\n", cache->SetCap);

	lRUCachePut(cache, 10, 100);

	value = lRUCacheGet(cache, 10);

	printf("Get key 10 value: %d\n", value);

	lRUCachePut(cache, 20, 101);

	value = lRUCacheGet(cache, 20);

	printf("Get key 20 value: %d\n", value);

	value = lRUCacheGet(cache, 30);

	printf("Get key 30 value: %d\n", value);

	lRUCacheFree(cache);

    return 0;
}


/**
 * Your LRUCache struct will be instantiated and called as such:
 * struct LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */