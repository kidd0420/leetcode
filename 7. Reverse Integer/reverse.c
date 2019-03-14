#include "stdio.h"
#include <stdlib.h>
#include <string.h>

int reverse(int x) {
    int ret = 0;
	char string[11] = {0};
	char string_ret[11] = {0};
	int end_idx = 0;
	int start_idx = 0;
	int i, j = 0;
	char compare_string[11] = {0};
	int pass = 0;
    
    if (x == 0)
        return 0;

	if (x < 0) {
		end_idx = 1;
		string_ret[0] = '-';
	}

	sprintf(string, "%d", x);

	start_idx = strlen(string) - 1;

	if ((start_idx + 1) < 10 + end_idx)
		pass = 1;
	else {
		if (x < 0)
			strcpy(compare_string, "2147483648");
		else
			strcpy(compare_string, "2147483647");
	}
	
	for (i = start_idx; i >= end_idx; i--) {
		string_ret[j + end_idx] = string[i];

		if (pass == 0) {
			if (string_ret[j + end_idx] < compare_string[j])
				pass = 1;
			else if (string_ret[j + end_idx] > compare_string[j])
				return 0;
		}

		j++;
	}
	
	ret = atoi(string_ret);

    return ret;
}


int main ()
{
    int input = -8463847412;
                // 2147483648
    int output;
    
    output = reverse(input);

    printf("Output: %d\n", output);

    return 0;
}