#include "stdio.h"
#include "stdbool.h"

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode(int n, int* returnSize) {
    int *output;
    int value = 0x1;

    *returnSize = 1 << n;
    output = malloc((*returnSize) * sizeof(int));
	
    output[0] = 0;

    for (int i = 0; i < n; i++) {
        int k = (1 << i);
        for (int j = k, m = 1; j < (1 << (i + 1)); j++, m++) {
            output[j] = k | output[k - m];
        }
    }

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

    printf("Data %d, Length: %d\n", input, size);

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