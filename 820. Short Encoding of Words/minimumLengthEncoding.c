/*****************************************************************************************************
 * Given a list of words, we may encode it by writing a reference string S and a list of indexes A.
 * For example, if the list of words is ["time", "me", "bell"], 
 * we can write it as S = "time#bell#" and indexes = [0, 2, 5].
 * 
 * Then for each index, we will recover the word by reading from 
 * the reference string from that index until we reach a "#" character.
 * 
 * What is the length of the shortest reference string S possible that encodes the given words?
 * 
 * Example:
 * Input: words = ["time", "me", "bell"]
 * Output: 10
 * Explanation: S = "time#bell#" and indexes = [0, 2, 5].
 * 
 * Note:
 * 1 <= words.length <= 2000.
 * 1 <= words[i].length <= 7.
 * Each word has only lowercase letters.
 *****************************************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b)	(a < b)?a:b


int CompareString(char* str_a, char* str_b)
{
	int len_a = strlen(str_a);
	int len_b = strlen(str_b);
	int i;
    int min_num = min(len_a, len_b);

	for (i = 1; i <= min_num; i++) {
		if (str_a[len_a - i] != str_b[len_b - i])
			return 0;	//String a and b are difference string
	}

	if (len_a >= len_b)
		return 1;		//String b can be remove
	else
		return 2;		//String a can be remove
}


int minimumLengthEncoding(char** words, int wordsSize) {
    int count = 0;
    int sum = 0;
    bool *remove_flag;
    int i, j;
    int used = 0;

    remove_flag = malloc(sizeof(bool) * wordsSize);
    memset(remove_flag, false, sizeof(bool) * wordsSize);

    for (i = 0; i < wordsSize; i++) {
    	if (remove_flag[i])
    		continue;

    	used = 0;

    	for (j = 0; j <= i; j++) {
    		int stat;

    		if (used == count) {
                sum += strlen(words[j]) + 1;
    			count++;
    			break;
    		}

    		if (remove_flag[i])
    			continue;

    		used++;

    		stat = CompareString(words[i], words[j]);

            //printf("stat: %d\n", stat);

    		if (stat == 1) {
    			remove_flag[i] = 1;
                sum += strlen(words[i]);
                sum -= strlen(words[j]);
    			break;
    		} else if (stat == 2) {
    			remove_flag[j] = 1;
    			break;
    		}
    	}

    }

    free(remove_flag);

    return sum;
}


int main()
{
    char **input;
    char input_0[8] = "me";
    char input_1[8] = "time";
    char input_2[8] = "bell";

    int sum;

    input = malloc(sizeof(char**) * 3);

    input[0] = input_0;
    input[1] = input_1;
    input[2] = input_2;

    sum = minimumLengthEncoding(input, 3);

    printf("sum: %d\n", sum);

    return 0;
}