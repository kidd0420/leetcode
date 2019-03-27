/****************************************************************
 * Given a positive 32-bit integer n, 
 * you need to find the smallest 32-bit integer 
 * which has exactly the same digits existing in the integer n 
 * and is greater in value than n. 
 * If no such positive 32-bit integer exists, you need to return -1.
 * 
 * Example 1:
 * Input: 12
 * Output: 21
 *  
 * Example 2:
 * Input: 21
 * Output: -1
 ****************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>

//Same as 31. Next Permutation


unsigned int convert(char *st) {
  char *x;
  for (x = st ; *x ; x++) {
    if (!isdigit(*x))
      return 0L;
  }
  return (strtoul(st, 0L, 10));
}


void Revert(char* string, int len) {
	int tmp;
	int i;

	for (i = 0; i < len / 2; i++) {
		tmp = string[(len - 1) - i];
		string[(len - 1) - i] = string[i];
		string[i] = tmp;
	}
}


void Reorder(char* string, int len, int idx)
{
	int tmp;

	if (idx == len - 1) {
		tmp = string[idx - 1];
		string[idx - 1] = string[idx];
		string[idx] = tmp;
	} else {
		int i;

		for (i = len - 1; i >= idx; i--) {
			if (string[idx - 1] < string[i]) {
				tmp = string[i];
				string[i] = string[idx - 1];
				string[idx - 1] = tmp;
				Revert(&string[idx], len - idx);
				return;
			}
		}
	}
}


int nextGreaterElement(int n) {
  unsigned int tmp = 0;
	char string[11] = {0};
	int i;
	int len;

	if (n > 0x7FFFFFFF)
		return -1;

	sprintf(string, "%d", n);
	len = strlen(string);

	for (i = len - 1; i > 0; i--) {
		if (string[i] > string[i - 1]) {
			Reorder(string, len, i);

			tmp = convert(string);
      break;
		}
	}

	if ((tmp == 0) || (tmp > 0x7FFFFFFF))
		return -1;
	else
		return tmp;
}


int main ()
{
  int input = 10321;
  int output = nextGreaterElement(input);

  printf("Input : %d\n", input);
  printf("Output: %d\n", output);

  return 0;
}