/******************************************************************************************
 * Let's call any (contiguous) subarray B (of A) a mountain if the following properties hold:
 * 
 * B.length >= 3
 * There exists some 0 < i < B.length - 1 such that 
 * B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
 * (Note that B could be any subarray of A, including the entire array A.)
 * 
 * Given an array A of integers, return the length of the longest mountain. 
 * 
 * Return 0 if there is no mountain.
 * 
 * Example 1:
 * Input: [2,1,4,7,3,2,5]
 * Output: 5
 * Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
 * 
 * Example 2:
 * Input: [2,2,2]
 * Output: 0
 * Explanation: There is no mountain.
 * 
 * Note:
 * 0 <= A.length <= 10000
 * 0 <= A[i] <= 10000
 ******************************************************************************************/
#include <stdio.h>

#define max(a,b)	(a > b)?a:b


int longestMountain(int* A, int ASize) {
	int ret = 0;
	int i = 1;
	int rising_tmp = 1;
	int falling_tmp = 0;

    while (i < ASize) {
    	if (A[i] > A[i - 1]) {
    		if (falling_tmp != 0) {
    			ret = max(ret, rising_tmp + falling_tmp);
    			rising_tmp = 1;
    			falling_tmp = 0;
    		}

    		rising_tmp++;
    	} else if ((A[i] < A[i - 1]) && (rising_tmp > 1)) {
    		falling_tmp++;

            if (i == (ASize - 1))
                ret = max(ret, rising_tmp + falling_tmp);
    	} else {
            if (falling_tmp != 0)
                ret = max(ret, rising_tmp + falling_tmp);

            rising_tmp = 1;
    		falling_tmp = 0;
        }

    	i++;
    }

    return ret;
}


int main()
{
    int input[] = {2,5,8,7,2,2,2,6,7,8,9,8,7,6,2,2,5,5,5,5,5,5,5,2,1};
    int size = sizeof(input) / sizeof(int);
    int ret;
    
    ret = longestMountain(input, size);

    printf("LongestMountain: %d\n", ret);

    return 0;
}