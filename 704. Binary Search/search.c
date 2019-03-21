/******************************************************************************
 * Given a sorted (in ascending order) integer array nums of n elements 
 * and a target value, write a function to search target in nums. 
 * If target exists, then return its index, otherwise return -1.
 * 
 * Example 1:
 * Input: nums = [-1,0,3,5,9,12], target = 9
 * Output: 4
 * Explanation: 9 exists in nums and its index is 4
 * 
 * Example 2:
 * Input: nums = [-1,0,3,5,9,12], target = 2
 * Output: -1
 * Explanation: 2 does not exist in nums so return -1
 * 
 * Note:
 * You may assume that all elements in nums are unique.
 * n will be in the range [1, 10000].
 * The value of each element in nums will be in the range [-9999, 9999].
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>


int search(int* nums, int numsSize, int target) {
	int mid;

	//No any numbers in the list
	if (numsSize <= 0)
		return -1;

	mid = numsSize / 2;

	if (target == nums[mid]) {
		return mid;
	} else if (target > nums[mid]) {
        int ret;
		int start_idx = mid + 1;

		if (mid == numsSize)
			return -1;

        if ((ret = search(&nums[start_idx], numsSize - start_idx, target)) >= 0)
            return (ret + start_idx);
        else
            return -1;
	} else if (target < nums[mid]) {
		if (mid == 0)
			return -1;

		return search(nums, numsSize - mid, target);
	}

    return -1;
}


int main ()
{
    int input[10] = {-1,1,5,6,8,12,17,20,22,100};
    int target = 22;
    int output;

    output = search(input, 10, target);

    printf("idx: %d\n", output);

    return 0;
}