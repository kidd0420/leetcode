#include "stdio.h"

int titleToNumber(char* s)
{
	int idx = 0;
	int carry = 26;
	int count = 0;

    while ((s[idx] != '\0') || (s[idx] != NULL)) {
    	if ((s[idx] < 'A') || (s[idx] > 'Z')) {
            printf("Invalid input: %c\n", s[idx]);
    		return -1;
        }

        if (idx != 0)
            count *= carry;

    	count += (s[idx] - 0x40);

    	idx++;
    }

    return count;
}

int main ()
{
    char s[256];
    int count;

    scanf("%s", &s);

    count = titleToNumber(s);

    printf("count: %d\n", count);

    return 0;
}