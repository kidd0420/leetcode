/********************************************************************************************************
 * N couples sit in 2N seats arranged in a row and want to hold hands. 
 * We want to know the minimum number of swaps so that every couple is sitting side by side. 
 * A swap consists of choosing any two people, then they stand up and switch seats.
 * 
 * The people and seats are represented by an integer from 0 to 2N-1, 
 * the couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), 
 * and so on with the last couple being (2N-2, 2N-1).
 * 
 * The couples' initial seating is given by row[i] being the value of the person 
 * who is initially sitting in the i-th seat.
 * 
 * Example 1:
 * Input: row = [0, 2, 1, 3]
 * Output: 1
 * Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
 * 
 * Example 2:
 * Input: row = [3, 2, 0, 1]
 * Output: 0
 * Explanation: All couples are already seated side by side.
 * 
 * Note:
 * len(row) is even and in the range of [4, 60].
 * row is guaranteed to be a permutation of 0...len(row)-1.
 ********************************************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
	Standby = 0,
	Left    = 1,
	Right   = 2,
    Stop    = 3,
} Move_Direction;


bool CheckTwoPersons(int* row, int* flags, int person_a, int person_b,
		               int* couple_count)
{
	if (((row[person_a] % 2 == 0) && (row[person_b] == row[person_a] + 1)) ||
	    ((row[person_a] % 2 == 1) && (row[person_b] == row[person_a] - 1))) {
		flags[person_a] = Stop;
		flags[person_b] = Stop;
		(*couple_count)++;

		return true;
	}

	return false;
}


void FindTheirOtherHalf(int* row, int rowSize, int* flags, int person_a, int direction, int* couple_count)
{
	int i;

	switch (direction) {
	case Left:
		for (i = person_a - 1; i >= 0; i--) {
			if (((row[person_a] % 2 == 0) && (row[i] == row[person_a] + 1)) ||
				((row[person_a] % 2 == 1) && (row[i] == row[person_a] - 1))) {
                if (i == person_a - 1) {
                    flags[person_a] = Stop;
                    flags[i] = Stop;
                    (*couple_count)++;
                } else {
				    flags[person_a] = Left;
				    flags[i] = Right;
                }
				return;
			}
		}
		break;
	case Right:
		for (i = person_a + 1; i < rowSize; i++) {
			if (((row[person_a] % 2 == 0) && (row[i] == row[person_a] + 1)) ||
				((row[person_a] % 2 == 1) && (row[i] == row[person_a] - 1))) {
                if (i == person_a + 1) {
                    flags[person_a] = Stop;
                    flags[i] = Stop;
                    (*couple_count)++;
                } else {
				    flags[person_a] = Right;
				    flags[i] = Left;
                }
				return;
			}
		}
		break;
	}
}


void CheckTheyAreCouple(int* row, int rowSize, int* flags,
		                  int* person_a, int* couple_count)
{
	if ((*person_a) < rowSize - 1) {
		if (CheckTwoPersons(row, flags, (*person_a), (*person_a) + 1, couple_count)) {
			(*person_a)++;
			return;
		}

		FindTheirOtherHalf(row, rowSize, flags, (*person_a), Right, couple_count);
	}

	if ((*person_a) > 0) {
		if (CheckTwoPersons(row, flags, (*person_a), (*person_a) - 1, couple_count)) {
			return;
		}

		FindTheirOtherHalf(row, rowSize, flags, (*person_a), Left, couple_count);
	}
}


void SwapPerson(int* row, int* flags, int person_a, int person_b)
{
	int tmp_row, tmp_flag;

    //printf("Swap: %d(%d) and %d(%d)\n", row[person_a], flags[person_a], row[person_b], flags[person_b]);

	tmp_row 		= row[person_a];
	tmp_flag 		= flags[person_a];
	row[person_a] 	= row[person_b];
	flags[person_a] = flags[person_b];
	row[person_b] 	= tmp_row;
	flags[person_b]	= tmp_flag;
}


void CheckSidePerson(int* row, int* flags, int person_a, int direction, int* step_count, int* couple_count)
{
	switch (direction) {
	case Left:
		if (flags[person_a - 1] == Stop) {
			SwapPerson(row, flags, person_a, person_a - 2);
			(*step_count) += 2;
		} else if (flags[person_a - 1] == Right) {
            if (CheckTwoPersons(row, flags, person_a, person_a - 1, couple_count) == false) {
                SwapPerson(row, flags, person_a, person_a - 1);
			    (*step_count)++;
            }
		}
		break;
	case Right:
		if (flags[person_a + 1] == Stop) {
			SwapPerson(row, flags, person_a, person_a + 2);
			(*step_count) += 2;
		} else if (flags[person_a + 1] == Left) {
            if (CheckTwoPersons(row, flags, person_a, person_a + 1, couple_count) == false) {
			    SwapPerson(row, flags, person_a, person_a + 1);
			    (*step_count)++;
            }
		}
		break;
	}
}


void ShowList(int* row, int rowSize)
{
    int i;

    printf("[");

    for (i = 0; i < rowSize; i++) {
        printf("%d", row[i]);

        if (i != rowSize - 1)
            printf(",");
    }

    printf("]\n");
}


int minSwapsCouples(int* row, int rowSize) {
    int* flags;
    int couple_count = 0;
    int expected_count = rowSize / 2;
    int i;
    int step_count = 0;

    flags = malloc(sizeof(int) * rowSize);
    memset(flags, Standby, sizeof(int) * rowSize);

    while(couple_count < expected_count) {
    	for (i = 0; i < rowSize; i++) {
    		CheckSidePerson(row, flags, i, flags[i], &step_count, &couple_count);

            if (flags[i] != Stop)
    		    CheckTheyAreCouple(row, rowSize, flags, &i, &couple_count);
    	}

        //ShowList(row, rowSize);
    }

    free(flags);

    return step_count;
}


int main ()
{
    int input[] = {15,4,8,10,9,2,1,0,3,11,6,5,13,12,7,14};
    int size = sizeof(input) / sizeof(int);
    int count;

    count = minSwapsCouples(input, size);

    printf("Ans count: %d\n", count);

    return 0;
}