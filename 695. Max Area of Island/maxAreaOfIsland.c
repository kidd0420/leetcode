/****************************************************
 * Given a non-empty 2D array grid of 0's and 1's, 
 * an island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) 
 * You may assume all four edges of the grid are surrounded by water.
 * 
 * Find the maximum area of an island in the given 2D array. 
 * (If there is no island, the maximum area is 0.)
 *
 * Example 1:
 * 
 * [[0,0,1,0,0,0,0,1,0,0,0,0,0],
 * [0,0,0,0,0,0,0,1,1,1,0,0,0],
 * [0,1,1,0,1,0,0,0,0,0,0,0,0],
 * [0,1,0,0,1,1,0,0,1,0,1,0,0],
 * [0,1,0,0,1,1,0,0,1,1,1,0,0],
 * [0,0,0,0,0,0,0,0,0,0,1,0,0],
 * [0,0,0,0,0,0,0,1,1,1,0,0,0],
 * [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 * Given the above grid, return 6. Note the answer is not 11, 
 * because the island must be connected 4-directionally.
 * 
 * Example 2:
 *
 * [[0,0,0,0,0,0,0,0]]
 * Given the above grid, return 0.
 * 
 * Note: The length of each dimension in the given grid does not exceed 50.
 ****************************************************/
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

enum {
	LOC_UP = 0x0,
	LOC_LEFT,
	LOC_DOWN,
	LOC_RIGHT,
};

#define LOC_MASK	0x3


int calc(int** grid, int gridRowSize, int gridColSize, int row_idx, int col_idx, int locate) 
{
    int ret = 0;

	if (grid[row_idx][col_idx] == 0) {
		return 0;
    } else {
        grid[row_idx][col_idx] = 0;
        ret = 1;
    }
	
	for (int i = 1; i < 4; i++) {
		switch ((locate + i) & LOC_MASK) {
			case LOC_UP:
				if (row_idx - 1 >= 0)
					ret = ret + calc(grid, gridRowSize, gridColSize, row_idx - 1, col_idx, LOC_DOWN);
				break;
			case LOC_LEFT:
				if (col_idx - 1 >= 0)
					ret = ret + calc(grid, gridRowSize, gridColSize, row_idx, col_idx - 1, LOC_RIGHT);
				break;
			case LOC_DOWN:
				if (row_idx + 1 < gridRowSize)
					ret = ret + calc(grid, gridRowSize, gridColSize, row_idx + 1, col_idx, LOC_UP);
				break;
			case LOC_RIGHT:
				if (col_idx + 1 < gridColSize)
					ret = ret + calc(grid, gridRowSize, gridColSize, row_idx, col_idx + 1, LOC_LEFT);
				break;
		}
	}

	return ret;
}


int maxAreaOfIsland(int** grid, int gridRowSize, int gridColSize) {
    int max = 0;
    int tmp = 0;

    for (int row = 0; row < gridRowSize; row++) {
        for (int col = 0; col < gridColSize; col++) {
            if (grid[row][col] == 0)
                continue;
            tmp = calc(grid, gridRowSize, gridColSize, row, col, LOC_LEFT);

            if (tmp > max)
                max = tmp;
        }
    }

    return max;
}

#define ROW_SIZE    7
#define COL_SIZE    16


int main ()
{
    int **grid;
    int input[ROW_SIZE][COL_SIZE] = {   
        {1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0},
        {1,1,0,0,0,1,0,0,1,1,1,1,1,1,1,0},
        {1,1,0,0,0,1,0,0,0,0,0,0,1,0,1,1},
        {1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,1},
        {1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1},
        {0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1},
        {0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1}};
    int max;

    grid = malloc(sizeof(int*) * ROW_SIZE);

    for (int row = 0; row < ROW_SIZE; row++) {
        grid[row] = malloc(sizeof(int) * COL_SIZE);

        for (int col = 0; col < COL_SIZE; col++) {
            grid[row][col] = input[row][col];
        }
    }

    max = maxAreaOfIsland(grid, ROW_SIZE, COL_SIZE);

    printf("max: %d\n", max);

    for (int row = 0; row < ROW_SIZE; row++) {
        free(grid[row]);
    }

    free(grid);

    return 0;
}