/****************************************************************************************************
 * There are N dominoes in a line, and we place each domino vertically upright.
 * In the beginning, we simultaneously push some of the dominoes either to the left or to the right.
 * After each second, each domino that is falling to the left pushes the adjacent domino on the left.
 * Similarly, the dominoes falling to the right push their adjacent dominoes standing on the right.
 * When a vertical domino has dominoes falling on it from both sides, 
 * it stays still due to the balance of the forces.
 * For the purposes of this question, we will consider that a falling domino expends no additional force 
 * to a falling or already fallen domino.
 * Given a string "S" representing the initial state. 
 * S[i] = 'L', if the i-th domino has been pushed to the left; S[i] = 'R', 
 * if the i-th domino has been pushed to the right; S[i] = '.', if the i-th domino has not been pushed.
 * Return a string representing the final state. 
 * 
 * Example 1:
 * Input:  ".L.R...LR..L.."
 * Output: "LL.RR.LLRRLL.."
 * 
 * Example 2:
 * Input: "RR.L"
 * Output: "RR.L"
 * Explanation: The first domino expends no additional force on the second domino.
 * 
 * Note:
 * 0 <= N <= 10^5
 * String dominoes contains only 'L', 'R' and '.'
 ****************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void WriteChar(char* dominoes, int* dominoes_count, char write_char, int count)
{
	int i;

	for (i = 0; i < count; i++) {
		memcpy(&dominoes[(*dominoes_count) + i], &write_char, 1);
	}

	(*dominoes_count) += count;
}


char* pushDominoes(char* dominoes) {
	//.L.R...LR..L..
	int dominoes_count = strlen(dominoes);
	char* tmpdominoes;
	int i;
	int pushdominoes_count = 0;
	int count_point = 0;
    int count_R = 0;

    if (dominoes_count == 0)
        return dominoes;

    tmpdominoes = malloc(sizeof(char) * (dominoes_count + 1));
    memcpy(tmpdominoes, dominoes, dominoes_count);

	while (i < dominoes_count) {
        //printf("dominoes[%d]: %c\n", i, dominoes[i]);
		switch (tmpdominoes[i]) {
		case '.':
			count_point++;
			break;
		case 'L':
			if (count_point) {
				WriteChar(dominoes, &pushdominoes_count, 'L', count_point);
				count_point = 0;
			} else if (i != 0) {
                if ((tmpdominoes[i - 1] != 'R') && (dominoes[i - 1] == 'R')) {
                    pushdominoes_count -= (count_R / 2);

                    if (count_R % 2) {
                        pushdominoes_count--;
                        WriteChar(dominoes, &pushdominoes_count, '.', 1);
                    }

                    WriteChar(dominoes, &pushdominoes_count, 'L', (count_R / 2));
                }
			}

			WriteChar(dominoes, &pushdominoes_count, 'L', 1);
			break;
		case 'R':
			if (count_point) {
				WriteChar(dominoes, &pushdominoes_count, '.', count_point);
				count_point = 0;
			}

            count_R = 0;

			do {
				WriteChar(dominoes, &pushdominoes_count, 'R', 1);

                if ((i + 1) < dominoes_count) {
                    if (tmpdominoes[i + 1] == '.') {
                        count_R++;
                        i++;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
			} while (1);
			break;
		}

        i++;
	}

	if (pushdominoes_count < dominoes_count) {
		WriteChar(dominoes, &pushdominoes_count, '.', dominoes_count - pushdominoes_count);
	}

    free(tmpdominoes);

	return dominoes;
}


int main ()
{
    char* input = "LRRR....LLL...RR.....RR.....LLL...R...L...L";
    char* output;

    printf("input  : %s\n", input);

    output = pushDominoes(input);
    
    printf("output : %s\n", output);

    return 0;
}