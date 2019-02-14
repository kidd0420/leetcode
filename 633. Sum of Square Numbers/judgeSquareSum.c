#include "stdio.h"
#include "stdbool.h"


bool judgeSquareSum(int c) {
    long temp;
    for(long i = 0, j = 0; temp = i*i, temp<= c; i++)
    {
        j = sqrt(c - temp);
        if(temp+j*j == c) return true;
    }
    return false;
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