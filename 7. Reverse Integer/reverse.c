#include "stdio.h"
#include <stdlib.h>
#include <string.h>

int reverse(int x) {
    
    
    if (x == 0) {
        return 0;
    }
}


int main ()
{
    int input = 123;
    int output;
    
    output = reverse(input);

    printf("Output: %d\n", output);

    return 0;
}