/*
You are a professional robber planning to rob houses along a street. 
Each house has a certain amount of money stashed, 
the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and 
it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of non-negative integers representing the amount of money of each house, 
determine the maximum amount of money you can rob tonight without alerting the police.

Example 1:

Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
Example 2:

Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.
*/
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

int rob(int* nums, int numsSize) {
    int *add_nums;
	int i,j;
	int tmp_num;

    if (numsSize == 0) {
        return 0;
	} else if (numsSize == 1) {
		return nums[0];
	} else if (numsSize == 2) {
		if (nums[0] > nums[1])
			return nums[0];
		else
			return nums[1];
	}

	add_nums = malloc(sizeof(int) * numsSize);
	memcpy(add_nums, nums, sizeof(int) * numsSize);

	for (i = 0; i < numsSize - 2; i++) {
		for (j = 2; j < 4; j++) {
			if (i + j >= numsSize)
				break;

			if (nums[i] > add_nums[i])
				tmp_num = nums[i + j] + nums[i];
			else
				tmp_num = nums[i + j] + add_nums[i];

			if (tmp_num > add_nums[i + j])
				add_nums[i + j] = tmp_num;
		}
	}

	if (add_nums[numsSize - 2] > add_nums[numsSize - 1])
		tmp_num = add_nums[numsSize - 2];
	else
		tmp_num = add_nums[numsSize - 1];
	
	free(add_nums);

	return tmp_num;
}


int main ()
{
    int input[] = {8,3,1,4,5,9};
    int count = sizeof(input) / sizeof(int);
    int sum;

    sum = rob(input, count);

    printf("sum: %d\n", sum);

    return 0;
}