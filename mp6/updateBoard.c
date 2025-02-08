#include <stdlib.h>
/*Akhil Morisetty(akhilm6) worked on mp6
The program uses 3 functions to count the number of live neighbors, update the board, and check if the 
board remains stable for future steps. The countLiveNeighbor functions uses nested for loops and if statements 
to count the number of alive neighbors for the give (row,col) on the board. The (row,col) is a parameter for the 
function and returns an integer count. The update board function uses a temporary array and the count live neighboars
function to update the board. The temp array holds the values of the board before each index is updated. The board is updated
following the requirements given in the machine problem. It is a void function that takes the board, row size, and col size as
its parameters. The aliveStable function also uses a temporary array to represent the board after the next step. Memory allocation
is used to create the temp array as it is called as a pointer into updateboard. After the temp array is updated, it is compared to the 
board and returns 0 if they are different and 1 if they are the same.
*/
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    
    int count = 0; //set the number of live neighbors to 0
    for(int x = row-1;x <= row+1;x++) //rows from currRow-1 to currRow+1, inclusive
    {
        if(x >= 0 && x < boardRowSize) //if the row is within the bounds of the board
        {
            for(int y = col-1;y <= col+1;y++) //for columns from currCol-1 to currCol+1, inclusive
            {
                if(y >= 0 && y < boardColSize) //if the column is within the bounds of the board
                {
                    if(x != row || y != col) //the cell isn't at (currRow, currCol)
                    {
                        if(*(board+(x*boardColSize+y)) == 1) //the cell is alive
                        {
                            count++; // increment the number of live neighbors
                        }
                    }
                }
            }
        }
    }
    //return the number of live neighbors
    return count;
}

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
    
    int prev[boardRowSize*boardColSize]; //init array same size as the board
    //uses another array to hold the values of the board before board in changed
    for(int c = 0;c < (boardRowSize*boardColSize);c++) //for loop to create a deep copy of the board
    {
        prev[c] = *(board+c); //put each element in same index from board
    }
    for(int x = 0;x < boardRowSize;x++) //loop to iterate through row value of the board
    {
        for(int y = 0;y < boardColSize;y++) //loop to iterate through the col value of the board
        {
            if(countLiveNeighbor(prev,boardRowSize,boardColSize,x,y) == 3) //check if number of live neighbors equals 3 
            {
                *(board+(x*boardColSize+y)) = 1; //set value to 1 or alive
            }
            else if(countLiveNeighbor(prev,boardRowSize,boardColSize,x,y) > 3)// check if number of live neighbors is greater than 3 or overpopulation
            {
                *(board+(x*boardColSize+y)) = 0; //set value on board to dead or zero
            }
            else if(countLiveNeighbor(prev,boardRowSize,boardColSize,x,y) < 2) //check if number of live neighbors is less than 2 or underpopulation
            {
                *(board+(x*boardColSize+y)) = 0; //set value on board to dead or zero
            }
        }

    }
}
    
/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
    int* next = malloc(boardRowSize*boardColSize*sizeof(int)); //allocate memory for the array to represent next step as a pointer
    for(int c = 0; c < boardRowSize*boardColSize;c++) //for loop to deep copy the board into the next array
    {
        next[c] = *(board+c); //make each value in next to the corresponding value in the board
    }
    updateBoard(next,boardRowSize,boardColSize); //update the array that represents the next step
    for(int x = 0;x < boardRowSize*boardColSize;x++) //for loop to check if there are any changes between the next step and current board
    {
        if(next[x] != *(board+x)) //compare the values and each index and check if they are not equal
        {
            return 0; //return 0 if board changes
        }
    }
    return 1; //return 1 if the board remains the same
}

				
				
			

