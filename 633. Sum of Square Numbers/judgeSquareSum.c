#include "stdio.h"
#include "stdbool.h"


bool judgeSquareSum(int c) {
	int base_a = 1, base_b = 1;
    int max = 1;
    int shift = 0;
	int sum = c;

    if (c <= 1)
		return 0;

	while (1) {
		if (c > max * max) {
			if (c < (max + 1) * (max + 1)) {
				break;
			} else if (c > (max + 1) * (max + 1)) {
                shift++;
				max = max << shift;
			} else {
				return 1;
			}
		} else if (c < max * max) {
			max--;
		} else {
			return 1;
		}
	}

	base_a = max;
	sum = c - (base_a * base_a);
    shift = 0;
	
	while (1) {
		if (c - (base_a * base_a) > (base_a - 1) * (base_a - 1)) {
			return 0;
		}

		while (1) {
			if (sum > base_b * base_b) {
				if (sum < (base_b + 1) * (base_b + 1)) {
					break;
				} else if (sum > (base_b + 1) * (base_b + 1)) {
                    if (base_a > base_b * base_b) {
                        shift++;
				        base_b = base_b << shift;
                    } else {
                        base_b = base_a - 1;
                    }
				} else {
					return 1;
				}
			} else if (sum < base_b * base_b) {
				base_b--;
			} else {
				return 1;
			}
			
            if (base_b < 1)
                return 0;
		}

		base_a--;
		sum = c - (base_a * base_a);
        shift = 0;

        if (base_a < 1)
            return 0;
	}

	return 0;
}


int main ()
{
    int input;
	bool isSquareSum;

    scanf("%d", &input);

	isSquareSum = judgeSquareSum(input);

    printf("Number %d is square sum? %s\n", input, (isSquareSum)?"True":"False");

    return 0;
}