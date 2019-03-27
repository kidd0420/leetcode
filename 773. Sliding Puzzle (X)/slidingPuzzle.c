/***************************************************************
 * 
 * On a 2x3 board, there are 5 tiles represented by the integers 1 through 5, 
 * and an empty square represented by 0.
 * 
 * A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
 * 
 * The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
 * 
 * Given a puzzle board, 
 * return the least number of moves required so that the state of the board is solved. 
 * If it is impossible for the state of the board to be solved, return -1.
 * 
 * Examples:
 * 
 * Input: board = [[1,2,3],[4,0,5]]
 * Output: 1
 * Explanation: Swap the 0 and the 5 in one move.
 * 
 * Input: board = [[1,2,3],[5,4,0]]
 * Output: -1
 * Explanation: No number of moves will make the board solved.
 * 
 * Input: board = [[4,1,2],[5,0,3]]
 * Output: 5
 * Explanation: 5 is the smallest number of moves that solves the board.
 * An example path:
 * After move 0: [[4,1,2],[5,0,3]]
 * After move 1: [[4,1,2],[0,5,3]]
 * After move 2: [[0,1,2],[4,5,3]]
 * After move 3: [[1,0,2],[4,5,3]]
 * After move 4: [[1,2,0],[4,5,3]]
 * After move 5: [[1,2,3],[4,5,0]]
 * 
 * Input: board = [[3,2,4],[1,5,0]]
 * Output: 14
 * 
 * Note:
 * board will be a 2 x 3 array as described above.
 * board[i][j] will be a permutation of [0, 1, 2, 3, 4, 5].
 **************************************************************/

#include <stdbool.h>

#define MAX_COUNT		720
#define INVALID_DATA	0xFF

int dir[6][3] = {{1,3,0xFF},{0,2,4},{1,5,0xFF},{0,4,0xFF},{1,3,5},{2,4,0xFF}};

bool HasSameNumber(int *list, int list_count, int number, int *idx)
{
	int i;

	for (i = 0; i < list_count; i++) {
		if ((number - list[i]) == 0) {
			*idx = i;
			return true;
		}
	}

	return false;
}

int FindSolution(int *list, int *list_count, int number, int zero_idx, int prev_zero_idx, int step_count)
{
	int i;

	for (i = 0; i < 3; i++) {
		if ((dir[zero_idx][i] != INVALID_DATA) && (dir[zero_idx][i] != prev_zero_idx)) {
			int idx;

			if (HasSameNumber(list, *list_count, number, &idx)) {
				
			}
		}
	}
}

int slidingPuzzle(int** board, int boardRowSize, int *boardColSizes) {
    int i, j, k = 0;
	int store_list[MAX_COUNT] = {0};	// 1 * 2 * 3 * 4 * 5 * 6 = 720
	int step_count[MAX_COUNT] = {0};
	int list_count = 0;
	int tmp_number = 0;
	int zero_idx;

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			tmp_number += board[i][j] * (10 ^ (5 - k));

			if (board[i][j] == 0)
				zero_idx = k;

			k++;
		}
	}

	printf("tmp_number: %d\n", tmp_number);
	printf("zero_idx  : %d\n", zero_idx);

	store_list[0] = 123450;
	step_count[0] = 0;
	list_count++;

	while (list_count < MAX_COUNT) {
		
	}
}