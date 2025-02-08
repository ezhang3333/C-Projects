/*This mp was worked on by Akhil Morisetty(akhilm6), Aashay Soni(asoni29), and Ethan Zhang(ethanjz2)
 The mp we have written uses a variety of functions working with a previously defined maze structure. The goal of the 
 mp is to solve the maze structure and find the path to the end of the maze. Using a depth-first search algorithm the maze is
 solved in the mp. The function we have create the maze, destroy the maze, print the maze, and solve maze using the depth-first 
 search algorithm. The solve function explores the possible paths until the solvable path is found to be solved. If the maze,
 is unsolvable then the maze is marked as being unsolvable and that is what is returned.
*/
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    maze_t* maze = (maze_t *) malloc(sizeof(maze_t)); //allocate memory for the maze struct
    FILE* Mfile = fopen(fileName,"r"); //open the file for reading
    int col = 0; //init col var
    int row = 0; //init row var
    char temp; //init temp char
    fscanf(Mfile,"%d %d",&col,&row); //read the col and row values for the array and put in to variables
    //fgetc(Mfile);
    maze->width = col; //set the width of the maze to the col
    maze->height = row; //set the height to the row
    maze->cells = (char**)malloc(row*sizeof(char*)); //allocation memory for each the rows
    for(int x = 0;x < row;x++)//for loop to allocate the memory for each of the cells in the maze
    {
        maze->cells[x] = (void*) malloc(col*sizeof(char));
    }
    fscanf(Mfile,"%c",&temp); //use a temp var to hold the new line

    //nested for loop to go through each of the cells in the file

    for(int x = 0;x < row;x++) 
    {
        for(int y = 0;y < col+1;y++)
        {
            char c = fgetc(Mfile); //get the next char from the file
            if(c == '\n') //if its a new line dont set the cell to that value
            {

            }
            else
            {
            maze->cells[x][y] = c;
            }
            if(maze->cells[x][y] == 'S') //check for start of the maze
            {
                maze->startColumn = y;
                maze->startRow = x;
            }
             if(maze->cells[x][y] == 'E') //check for end of the maze
            {
                maze->endColumn = y;
                maze->endRow = x;
            }
            
        }
    }
    fclose(Mfile); 
    
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    for(int i = 0; i<maze->height;i++){ //for loop to go through each of the rows
        free(maze->cells[i]); //free all of the rows
}
free(maze->cells); //free the memory of the cells
free(maze);
}
/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    //init var to hold row and col 
    int row = maze->height; 
    int col = maze->width;

    //nested for loop to go through all of the cells
    for(int i = 0;i<row;i++){

        for(int j = 0;j<col;j++){

            char c = maze->cells[i][j]; //set temp char to hold current cell value

            printf("%c",c); //print cell value
        }
        printf("\n"); //new line
    }
    return;
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    //init var to hold row and col of the maze
    int height = maze->height;
    int width = maze->width;

    //if the currently visisted cell is not in the maze return 0
    if((row < 0) || (col < 0) || (row >= height) || (col >= width))
    {
        return 0;
    }
    //if the current visited cell is at the END return 1
    if(((col == maze->endColumn)  && (row == maze->endRow)))
    {
        maze->cells[maze->startRow][maze->startColumn] = 'S';
        return 1;
    }
    //if not an empty cell return 0
    if(maze->cells[row][col] != 'S' && maze->cells[row][col] != ' ')
    {
        return 0;
    }
    maze->cells[row][col] = '*'; //set maze as already visited
    
    //for if statements checking if the values around
    //the current cell to find which movement is valid 
    if(solveMazeDFS(maze, col, (row + 1)) == 1)
    {
        return 1;
    }
    if(solveMazeDFS(maze, col, (row - 1)) == 1)
    {
        return 1;
    }
    if(solveMazeDFS(maze, (col + 1), row) == 1)
    {
        return 1;
    }
    if(solveMazeDFS(maze, (col -1), row) == 1)
    {
        return 1;
    }
        maze->cells[row][col] = '~';
    


    return 0;
}
