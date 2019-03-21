/****************************************************************************************
 * Design your implementation of the linked list. 
 * You can choose to use the singly linked list or the doubly linked list. 
 * A node in a singly linked list should have two attributes: val and next. 
 * val is the value of the current node, and next is a pointer/reference to the next node. 
 * If you want to use the doubly linked list, 
 * you will need one more attribute prev to indicate the previous node in the linked list. 
 * Assume all nodes in the linked list are 0-indexed.
 * 
 * Implement these functions in your linked list class:
 * 
 * get(index)             : Get the value of the index-th node in the linked list. 
 *                          If the index is invalid, return -1.
 * addAtHead(val)         : Add a node of value val before the first element of the linked list. 
 *                          After the insertion, the new node will be the first node of the linked list.
 * addAtTail(val)         : Append a node of value val to the last element of the linked list.
 * addAtIndex(index, val) : Add a node of value val before the index-th node in the linked list. 
 *                          If index equals to the length of linked list, 
 *                          the node will be appended to the end of linked list. 
 *                          If index is greater than the length, the node will not be inserted.
 * deleteAtIndex(index)   : Delete the index-th node in the linked list, if the index is valid.
 * 
 * Example:
 * MyLinkedList linkedList = new MyLinkedList();
 * linkedList.addAtHead(1);
 * linkedList.addAtTail(3);
 * linkedList.addAtIndex(1, 2);  // linked list becomes 1->2->3
 * linkedList.get(1);            // returns 2
 * linkedList.deleteAtIndex(1);  // now the linked list is 1->3
 * linkedList.get(1);            // returns 3
 * 
 * Note:
 * All values will be in the range of [1, 1000].
 * The number of operations will be in the range of [1, 1000].
 * Please do not use the built-in LinkedList library.
 ***************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList {
	int Value;
	struct LinkedList *Next;
} MyLinkedList;

static int g_Total;
static MyLinkedList* Tail_List;


/** Initialize your data structure here. */
MyLinkedList* myLinkedListCreate() {
	MyLinkedList* start = malloc(sizeof(MyLinkedList));

	start->Value = 0;
	start->Next = NULL;

	g_Total = 0;
	Tail_List = start;

	return start;
}

/** Get the value of the index-th node in the linked list.
 * If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) {
	int i;
	MyLinkedList *loc = obj;

	if (index > g_Total - 1)
		return -1;

	for (i = 0; i < index + 1; i++) {
		loc = loc->Next;
	}

	return loc->Value;
}

/** Add a node of value val before the first element of the linked list.
 * After the insertion, the new node will be the first node of the linked list. */
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
	MyLinkedList *new = malloc(sizeof(MyLinkedList));

	new->Value = val;

	if (obj->Next != NULL)
		new->Next = obj->Next;

	obj->Next = new;

	if (g_Total == 0)	//Only start link (No any valid link)
		Tail_List = new;

	g_Total++;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
	MyLinkedList *new = malloc(sizeof(MyLinkedList));

    obj = obj;
	new->Value = val;

	Tail_List->Next = new;
	Tail_List = new;

	g_Total++;
}

/** Add a node of value val before the index-th node in the linked list.
 * If index equals to the length of linked list, the node will be appended to the end of linked list.
 * If index is greater than the length, the node will not be inserted. */
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
	int i;
	MyLinkedList *new;
	MyLinkedList *loc = obj;

	if (index > g_Total)
		return;
	else if (index == g_Total) {
		myLinkedListAddAtTail(obj, val);
        return;
    }

	new = malloc(sizeof(MyLinkedList));

	for (i = 0; i < index; i++)
		loc = loc->Next;

	new->Value = val;
	new->Next = loc->Next;

	loc->Next = new;
	g_Total++;
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
	int i;
	MyLinkedList *loc = obj;
	MyLinkedList *free_list;

	if (index > g_Total - 1)
		return;

	for (i = 0; i < index; i++)
		loc = loc->Next;

	free_list = loc->Next;

	if (index == g_Total - 1) {
		Tail_List = loc;
		loc->Next = NULL;
	} else {
		loc->Next = loc->Next->Next;
	}

	free(free_list);
	g_Total--;
}

void myLinkedListFree(MyLinkedList* obj) {
	int i;
	MyLinkedList *remove = obj;
	MyLinkedList *next;

	for (i = 0; i < g_Total + 1; i++) {
		next = remove->Next;
		free(remove);
		remove = next;
	}
}

/**
 * Your MyLinkedList struct will be instantiated and called as such:
 * struct MyLinkedList* obj = myLinkedListCreate();
 * int param_1 = myLinkedListGet(obj, index);
 * myLinkedListAddAtHead(obj, val);
 * myLinkedListAddAtTail(obj, val);
 * myLinkedListAddAtIndex(obj, index, val);
 * myLinkedListDeleteAtIndex(obj, index);
 * myLinkedListFree(obj);
 */

int main ()
{
    MyLinkedList* list;
    int val;
    int idx;
    
    list = myLinkedListCreate();

    myLinkedListAddAtHead(list, 1);
    myLinkedListAddAtHead(list, 10);
    myLinkedListAddAtHead(list, 11);
    myLinkedListAddAtTail(list, 3);
    myLinkedListAddAtIndex(list, 1, 2);
    idx = 1;
    val = myLinkedListGet(list, idx);
    printf("Index[%d]: %d\n", idx, val);
    myLinkedListDeleteAtIndex(list, 1);
    idx = 1;
    val = myLinkedListGet(list, idx);
    printf("Index[%d]: %d\n", idx, val);
    
    myLinkedListFree(list);

    return 0;
}