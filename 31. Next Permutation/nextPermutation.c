/***********************************************************************************
 * Implement next permutation, 
 * which rearranges numbers into the lexicographically next greater permutation of numbers.
 * 
 * If such arrangement is not possible, it must rearrange it as the lowest possible order 
 * (ie, sorted in ascending order).
 * 
 * The replacement must be in-place and use only constant extra memory.
 * 
 * 
 * Here are some examples. 
 * Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1
 ***********************************************************************************/
#include <stdio.h>


void Revert(int* nums, int numsSize) {
	int tmp;
	int i;

	for (i = 0; i < numsSize / 2; i++) {
		tmp = nums[(numsSize - 1) - i];
		nums[(numsSize - 1) - i] = nums[i];
		nums[i] = tmp;
	}
}


void Reorder(int* nums, int numsSize, int idx) {
	int tmp;

	if (idx == numsSize - 1) {
		tmp = nums[idx - 1];
		nums[idx - 1] = nums[idx];
		nums[idx] = tmp;
	} else {
		int i;

		for (i = numsSize - 1; i > idx; i--) {
			if (nums[idx - 1] < nums[i]) {
				tmp = nums[i];
				nums[i] = nums[idx - 1];
				nums[idx - 1] = tmp;
				Revert(&nums[idx], numsSize - idx);
				return;
			}
		}
	}
}


void nextPermutation(int* nums, int numsSize) {
	int i;

	if (numsSize <= 1)
		return;

	for (i = numsSize - 1; i > 0; i--) {
		if (nums[i] > nums[i - 1]) {
			Reorder(nums, numsSize, i);
			return;
		}
	}

	Revert(nums, numsSize);
}


void ShowArray(int* nums, int numsSize)
{
    int i;

    printf("[");

    for (i = 0; i < numsSize; i++) {
        printf("%d", nums[i]);

        if (i != numsSize -1)
            printf(",");
    }

    printf("]\n");
}


int main ()
{
    int input[6] = {5,4,4,4,2,1};
    int size = sizeof(input) / sizeof(int);

    ShowArray(input, size);
    nextPermutation(input, size);
    ShowArray(input, size);

    return 0;
}