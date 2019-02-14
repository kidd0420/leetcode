#include "stdio.h"
#include "stdbool.h"

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode(int n, int* returnSize) {
    int *output;
	int idx = 0;
	int *used;
	int currsize = 0;
	int curridx = 0;
	int value = 1;
    int tmp_value = 0;

    *returnSize = 1 << n;
    output = malloc((*returnSize) * sizeof(int));
	used = malloc((*returnSize) * sizeof(int));

	memset(used, 0x0, (*returnSize) * sizeof(int));

	do {
		int one_count = 0;

		while (used[curridx]) {
			curridx++;
		}

		tmp_value = value ^ curridx;

		while (tmp_value != 0) {
			one_count += tmp_value & 0x1;
			tmp_value = tmp_value >> 1;
		}

		if (one_count == 1) {
			output[idx] = curridx;
            value = curridx;
			idx++;
			used[curridx] = 1;
            curridx = 0;
			currsize++;
		} else {
            curridx++;
        }
	} while (currsize != *returnSize);

	free(used);

    return output;
}


int main ()
{
    int input;
    int size = 0;
    int *output;
    int i;

    scanf("%d", &input);

	output = grayCode(input, &size);

    printf("[");

    for (i = 0; i < size; i++) {
        printf("%d", output[i]);
        
        if (i != size - 1)
            printf(",");
    }

    printf("]\n");

    free(output);

    return 0;
}