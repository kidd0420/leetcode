/*********************************************************************************************************
 * Given a square array of integers A, we want the minimum sum of a falling path through A.
 * 
 * A falling path starts at any element in the first row, and chooses one element from each row.  
 * The next row's choice must be in a column that is different from the previous row's column by at most one.
 * 
 * Example 1:
 * Input: [[1,2,3],[4,5,6],[7,8,9]]
 * Output: 12
 * Explanation: 
 * The possible falling paths are:
 * [1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]
 * [2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]
 * [3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]
 * The falling path with the smallest sum is [1,4,7], so the answer is 12.
 * 
 * Note:
 * 1 <= A.length == A[0].length <= 100
 * -100 <= A[i][j] <= 100
 *********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define min(x,y)         (x < y?x:y)


int minFallingPathSum(int** A, int ARowSize, int *AColSizes) {
	int count = ARowSize - 1;
	int i;
	int min_sum;

	if (ARowSize == 1)
		return A[0][0];

    while (count > 0) {
    	for (i = 0; i < *AColSizes; i++) {
    		if (i == 0) {
    			A[count - 1][i] += min(A[count][i], A[count][i + 1]);
    		} else if (i == (*AColSizes) - 1) {
    			A[count - 1][i] += min(A[count][i - 1], A[count][i]);
    		} else {
    			int tmp;

    			tmp = min(A[count][i - 1], A[count][i]);
    			tmp = min(tmp, A[count][i + 1]);
    			A[count - 1][i] += tmp;
    		}
    	}

        count--;
    }

    min_sum = A[0][0];

    for (i = 1; i < *AColSizes; i++) {
    	min_sum = min(min_sum, A[0][i]);
    }

    return min_sum;
}


int main ()
{
    int **input;
    int input_0[3] = {1,2,3};
    int input_1[3] = {4,5,6};
    int input_2[3] = {7,8,9};
    int col = 3;
    int min;

    input = malloc(3 * sizeof(int*));

    input[0] = input_0;
    input[1] = input_1;
    input[2] = input_2;

    min = minFallingPathSum(input, 3, &col);

    printf("min: %d\n", min);

    return 0;
}