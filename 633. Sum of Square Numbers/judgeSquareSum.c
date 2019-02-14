#include "stdio.h"
#include "stdbool.h"


bool judgeSquareSum(int c) {
	int base_a = 1, base_b = 1;
    int max = 1;
	int sum = c;

    if (c == 3)
		return 0;
	else if (c <= 5)
		return 1;

	while (1) {
		//printf("max: %d\n", max);
		if (c > max * max) {
			if (c < (max + 1) * (max + 1)) {
				break;
			} else if (c > (max + 1) * (max + 1)) {
				if (max < 32768)
					max = max << 1;
				else {
					max = 46340;
					break;
				}		
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
	
	while (1) {
		if (sum == base_a * base_a) {
			return 1;
		} else if (c - (base_a * base_a) > (base_a - 1) * (base_a - 1)) {
			return 0;
		}

		while (1) {
			//printf("base_b: %d\n", base_b);
			if (sum > base_b * base_b) {
				if (sum < (base_b + 1) * (base_b + 1)) {
					break;
				} else if (sum > (base_b + 1) * (base_b + 1)) {
                    if (base_a > base_b * base_b) {
						if (base_b < 32768)
							base_b = base_b << 1;
						else
							base_b = 46340;
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

		base_b = 1;
		base_a--;
		sum = c - (base_a * base_a);

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