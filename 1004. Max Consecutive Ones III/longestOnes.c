/******************************************************************************
 * Given an array A of 0s and 1s, we may change up to K values from 0 to 1.
 * Return the length of the longest (contiguous) subarray that contains only 1s. 
 * 
 * Example 1:
 * Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
 * Output: 6
 * Explanation: 
 * [1,1,1,0,0,1,1,1,1,1,1]
 * Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.
 * 
 * Example 2:
 * Input: A = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], K = 3
 * Output: 10
 * Explanation: 
 * [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
 * Bolded numbers were flipped from 0 to 1.  The longest subarray is underlined.
 *  
 * Note:
 * 1. 1 <= A.length <= 20000
 * 2. 0 <= K <= A.length
 * 3. A[i] is 0 or 1 
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a,b)	(a > b)?a:b

struct Counter {
	int count;
	int k;
	struct Counter* next_counter;
};


int SetMaxValue(int size, int tmp_max, int count, int k)
{
	int a = tmp_max;
	int b = count;

	if (k > 0)
		b += k;

	if ((a > size) || (b > size))
		return size;

	return MAX(a,b);
}


int longestOnes(int* A, int ASize, int K) {
    struct Counter* Head;
	struct Counter* ptr_c;
	struct Counter* prev_ptr_c;
	int idx = 0;
	int max = 0;

	Head = malloc(sizeof(struct Counter));
	memset(Head, 0, sizeof(struct Counter));
    Head->k = K;
    ptr_c = Head;

	while (idx < ASize) {
		struct Counter* tmp = Head;

		while (tmp != NULL) {
			if (A[idx] == 1) {
                if (tmp->k >= 0)
					tmp->count += 1;

				if ((idx != 0) && (A[idx - 1] == 0) && 
				    (tmp->next_counter == NULL)) {
					prev_ptr_c = ptr_c;
					ptr_c = malloc(sizeof(struct Counter));
					memset(ptr_c, 0, sizeof(struct Counter));
                    ptr_c->k = K;
                    ptr_c->count = 1;
					prev_ptr_c->next_counter = ptr_c;
                    break;
				}
			} else {
				if (tmp->k > 0) {
                    tmp->k -= 1;
					tmp->count += 1;
				} else {
                    if (tmp->k == 0)
                        tmp->k -= 1;
					if (Head->next_counter != NULL) {
						struct Counter* tmp_head = Head->next_counter;
						max = SetMaxValue(ASize, max, Head->count, Head->k);
						free(Head);
						Head = tmp_head;
						tmp = Head;
						continue;
					}
				}
			}

			tmp = tmp->next_counter;
		}

		idx++;
	}

	while(Head != NULL) {
		struct Counter* tmp_head = Head;
		max = SetMaxValue(ASize, max, Head->count, Head->k);
        Head = Head->next_counter;
		free(tmp_head);
	}

	return max;
}

int main()
{
    int inputA[] = {1,0,1,0,0,1,1,1,1,0,1,0};
    int sizeA = sizeof(inputA) / sizeof(int);
    int k = 1;
    int max;

    max = longestOnes(inputA, sizeA, k);

    printf("max: %d\n", max);

    return 0;
}