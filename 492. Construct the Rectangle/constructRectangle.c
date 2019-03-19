/********************************************************
 * For a web developer, it is very important to know how to design a web page's size. 
 * So, given a specific rectangular web page’s area, 
 * your job by now is to design a rectangular web page, 
 * whose length L and width W satisfy the following requirements:
 * 
 * 1. The area of the rectangular web page you designed must equal to the given target area.
 * 
 * 2. The width W should not be larger than the length L, which means L >= W.
 * 
 * 3. The difference between length L and width W should be as small as possible.
 * You need to output the length L and the width W of the web page you designed in sequence.
 * 
 * Example:
 * Input: 4
 * Output: [2, 2]
 * Explanation: The target area is 4, and all the possible ways to construct it are [1,4], [2,2], [4,1]. 
 * But according to requirement 2, [1,4] is illegal; 
 * according to requirement 3,  [4,1] is not optimal compared to [2,2]. 
 * So the length L is 2, and the width W is 2.
 * 
 * Note:
 * The given area won't exceed 10,000,000 and is a positive integer
 * The web page's width and length you designed must be positive integers.
 * 
 *******************************************************/

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include "stdio.h"
#include <stdlib.h>

int* constructRectangle(int area, int* returnSize) {
    int *a;
	int tmp;
    int count = 1;

	if (area <= 0)
		return 0;

    a = malloc(sizeof(int) * 2);

    a[0] = 10000001;
    a[1] = 1;

	*returnSize = 2;

	while (count * count <= area) {
		if (area % count == 0) {
            a[1] = count;
			tmp = area / a[1];

			if (abs(tmp - a[1]) < abs(a[0] - a[1]))
				a[0] = tmp;
		}

        count++;
	}

	if (a[0] < a[1]) {
		tmp = a[0];
		a[0] = a[1];
		a[1] = tmp;
	}

	return a;
}


int main ()
{
    int area = 500;
    int* ans;
    int size;

    ans = constructRectangle(area, &size);

    printf("ans: [%d,%d]\n", ans[0], ans[1]);

    return 0;
}