/***************************************************************************************************
 * Given a sorted array, two integers k and x, find the k closest elements to x in the array. 
 * The result should also be sorted in ascending order. 
 * If there is a tie, the smaller elements are always preferred.
 * 
 * Example 1:
 * Input: [1,2,3,4,5], k=4, x=3
 * Output: [1,2,3,4]
 * 
 * Example 2:
 * Input: [1,2,3,4,5], k=4, x=-1
 * Output: [1,2,3,4]
 * 
 * Note:
 * The value k is positive and will always be smaller than the length of the sorted array.
 * Length of the given array is positive and will not exceed 104
 * Absolute value of elements in the array and x will not exceed 104
 * 
 * UPDATE (2017/9/19):
 * The arr parameter had been changed to an array of integers 
 * (instead of a list of integers). Please reload the code definition to get the latest changes.
 ***************************************************************************************************/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int FindMinGap(int* arr, int idx_a, int idx_b, int x)
{
	int gap_a = x - arr[idx_a];
	int gap_b = arr[idx_b] - x;

	if (gap_a - gap_b <= 0)
		return idx_a;
	else
		return idx_b;
}


int FindStartPosition(int* arr, int arrSize, int x)
{
	int idx = arrSize >> 1;

	while (1) {
		if (x > arr[idx]) {
			if (idx == (arrSize - 1))
				return idx;

			if (x <= arr[idx + 1])
				return FindMinGap(arr, idx, idx + 1, x);

			return idx + FindStartPosition(&arr[idx], arrSize - idx, x);
		} else if (x < arr[idx]) {
			if (idx == 0)
				return 0;

			if (x > arr[idx - 1])
				return FindMinGap(arr, idx - 1, idx, x);

			return FindStartPosition(arr, idx, x);
		} else
			return idx;
	}
}

int* findClosestElements(int* arr, int arrSize, int k, int x, int* returnSize) {
	int idx_x;
	int head, tail;
	int counter;
	int* ret;

	if ((arrSize <= 0) || (k <= 0)) {
		*returnSize = 0;
		return NULL;
	}

	if (k > arrSize)
		counter = arrSize;
	else if (k < arrSize)
		counter = k;

	*returnSize = counter;

	ret = malloc(counter * sizeof(int));

    if (k == arrSize) {
        memcpy(ret, arr, arrSize * sizeof(int));
        return ret;
    }

	idx_x = FindStartPosition(arr, arrSize, x);

	if (counter == 1) {
		ret[0] = arr[idx_x];
		return ret;
	}

	if (idx_x == 0) {
		memcpy(ret, arr, counter * sizeof(int));
		return ret;
	} else if (idx_x == (arrSize - 1)) {
		memcpy(ret, &arr[arrSize - counter], counter * sizeof(int));
		return ret;
	}

	head = tail = idx_x;
	counter--;

	while (counter) {
		if ((x - arr[head - 1]) > (arr[tail + 1] - x))
			tail++;
		else
			head--;

		counter--;

		if ((head == 0) && (counter > 0)) {
			tail += counter;
			counter = 0;
		} else if ((tail == arrSize - 1) && (counter > 0)) {
			head -= counter;
			counter = 0;
		}
	}

	memcpy(ret, &arr[head], (tail - head + 1) * sizeof(int));

	return ret;
}


int main()
{
    int input[] = {1,2,3,4,8,9,10,15,20};
    int size = sizeof(input) / sizeof(int);
    int number = 1;
    int x = 6;
    int* output;
    int ret_len;
    int i;

    output = findClosestElements(input, size, number, x, &ret_len);

    printf("[");

    for (i = 0; i < ret_len; i++) {
        printf("%d", output[i]);

        if (i != (ret_len - 1))
            printf(",");
    }

    printf("]\n");

    free(output);

    return 0;
}