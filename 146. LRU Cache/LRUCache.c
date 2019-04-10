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

#define DBG_PRINT printf("[%s:%d]\n", __func__, __LINE__);

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
	memset(cache, 0, sizeof(LRUCache));

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

	//printf("Add key[%d]\n", key);
	
	//Allocate memory for insert data
	new = malloc(sizeof(HashTable));
	memset(new, 0, sizeof(HashTable));

	//Set key and value
	new->Index = key;
	new->Value = value;
	//printf("new [%x,k%d]\n", new, new->Index);
	
	//HeadHT <--- --->Orig 1st HT
	//	         ^
	//	        New
	if (HeadHT->Next_HT != NULL) {
		HeadHT->Next_HT->Prev_HT = new;
		new->Next_HT = HeadHT->Next_HT;
	}
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
	if (obj->UsedCap <= obj->DefinedCap)
		obj->UsedCap++;

	//printf("HeadHT [%x]\n", HeadHT);
	//printf("new [%x,k%d]\n", new, new->Index);
	//printf("new->Next_HT [%x]\n", new->Next_HT);
	//printf("new->Prev_HT [%x]\n", new->Prev_HT);
}

void lRUCacheRemove(LRUCache* obj)
{
	HashTable* rm = obj->TailLRU->Prev_LRU;

	rm->Prev_LRU->Next_LRU = obj->TailLRU;
	obj->TailLRU->Prev_LRU = rm->Prev_LRU;
	rm->Prev_HT->Next_HT = rm->Next_HT;

	if (rm->Next_HT != NULL)
		rm->Next_HT->Prev_HT = rm->Prev_HT;

	//printf("free [%x,k%d]\n", rm, rm->Index);
	free(rm);
}

void lRUCacheRefresh(LRUCache* obj, int idx, HashTable* refresh, int value)
{
	HashTable* HeadHT = &obj->HeadHT[idx];
	HashTable* HeadLRU = obj->HeadLRU;

	refresh->Value = value;

	if (refresh->Prev_LRU != HeadLRU) {
		refresh->Prev_LRU->Next_LRU = refresh->Next_LRU;
		refresh->Next_LRU->Prev_LRU = refresh->Prev_LRU;

		HeadLRU->Next_LRU->Prev_LRU = refresh;
		refresh->Prev_LRU = HeadLRU;
		refresh->Next_LRU = HeadLRU->Next_LRU;
		HeadLRU->Next_LRU = refresh;
	}

	if (refresh->Prev_HT != HeadHT) {
		HeadHT->Next_HT->Prev_HT = refresh;
		refresh->Prev_HT->Next_HT = refresh->Next_HT;

		if (refresh->Next_HT != NULL)
			refresh->Next_HT->Prev_HT = refresh->Prev_HT;

		refresh->Next_HT = HeadHT->Next_HT;
		refresh->Prev_HT = HeadHT;
		HeadHT->Next_HT = refresh;
	}

	//printf("HeadHT [%x]\n", HeadHT);
	//printf("refresh [%x,k%d]\n", refresh, refresh->Index);
	//printf("refresh->Next_HT [%x]\n", refresh->Next_HT);
	//printf("refresh->Prev_HT [%x]\n", refresh->Prev_HT);
}

int lRUCacheGet(LRUCache* obj, int key)
{
	int idx;
	HashTable* HT;

	if (obj == NULL)
		return -1;
	
	idx = GetCacheIndex(obj, key);
	HT = obj->HeadHT[idx].Next_HT;

	while (1) {
		//printf("HT: %x\n", HT);
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
	int idx;
	HashTable* HT;

	if (obj == NULL)
		return;

	idx = GetCacheIndex(obj, key);
	HT = obj->HeadHT[idx].Next_HT;

	while (1) {
		if (HT != NULL) {
			if (HT->Index == (UINT32)key) {
				lRUCacheRefresh(obj, idx, HT, value);
				break;
			}
		} else {
			lRUCacheAdd(obj, idx, key, value);

			if (obj->UsedCap == obj->DefinedCap + 1)
				lRUCacheRemove(obj);

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
			//printf("free [%x]\n", HT);
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

	cache = lRUCacheCreate(1);

	//printf("Define size: %lld\n", cache->DefinedCap);
	//printf("Set size   : %lld\n", cache->SetCap);

	lRUCachePut(cache, 2, 1);
	lRUCachePut(cache, 3, 2);

	value = lRUCacheGet(cache, 3);
	printf("Get key 3 value: %d\n", value);

	value = lRUCacheGet(cache, 2);
	printf("Get key 2 value: %d\n", value);

	lRUCachePut(cache, 4, 3);

	value = lRUCacheGet(cache, 2);
	printf("Get key 2 value: %d\n", value);

	value = lRUCacheGet(cache, 3);
	printf("Get key 3 value: %d\n", value);

	value = lRUCacheGet(cache, 4);
	printf("Get key 4 value: %d\n", value);

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