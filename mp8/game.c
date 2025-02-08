#include "game.h"
/*This mp was worked on by Akhil Morisetty(akhilm6), Ethan Jiyu Zhang(ethanjz2), Aashay Soni(asoni29). To complete the
machine problem for the 2048 game. We implement a variety of functions in order to complete the mp. The first
few function served as service functions such as make game and remake game. Those functions reset the game board by 
setting all of the cells to -1 and init the row size and columns size. The next function get cell is used to retrieve the address
of one of the cells. All of the move functions follow a similar logic pattern. The move up and move down function traverse 
through the rows of each column and the move left and move right traverse through the columns in each of the rows. The function implement
a tracker variable to track whether or not the cells have been merged or not and another variable to track whether a valid move
was made or not. After each move the score was updated by looking at the new value of a cell that had been merged. All of the function work
together to create the 2048 machine problem.
*/


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));
    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows; //init number of rows
    mygame->cols = cols; //init number of columns
    mygame->score = 0; //init score
    for(int x = 0;x < rows*cols;x++)
    {
        mygame->cells[x] = -1; //init cells to -1
    }

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));
	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
    (*_cur_game_ptr)->rows = new_rows; //init rows to new rows
    (*_cur_game_ptr)->cols = new_cols; //init columns to new columns 
    (*_cur_game_ptr)->score = 0; //init score back to 0
    for(int x = 0;x < new_rows*new_cols;x++)
    {
        (*_cur_game_ptr)->cells[x] = -1; //init cells back to -1
    }

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells); 
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
{
    //YOUR CODE STARTS HERE
    if(row > 0 && row < cur_game->rows && col > 0 && col < cur_game->cols)
    {
        return &cur_game->cells[(row * cur_game->cols) + col]; //return the address of the specific cell
    }


    return NULL;
}
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
int move_w(game *cur_game) {
    int combined = 0; // Initialize a check variable to 0
    int cols = cur_game->cols; // init var for columns
    int rows = cur_game->rows; // init var for rows
    
    // Loop through eash columns
    for (int j = 0; j < cols; j++) {
        
        int merged = -1; //var to check the merged cell
        
        // Loop through each of the rows top to bottom
        for (int i = 1; i < rows; i++) {
            if (cur_game->cells[cols * i + j] != -1) //check whether cell is empty or not
            {
                for (int k = i - 1; k > merged; k--) //loop from the bottom most cell of column to the top
                {
                    if (cur_game->cells[cols * k + j] == -1) //check if cell is empty
                    {
                        // Shift the cell up
                        cur_game->cells[cols * k + j] = cur_game->cells[cols * (k + 1) + j];
                        cur_game->cells[cols * (k + 1) + j] = -1;
                        combined = 1; //set checker var to 1
                    } else if (cur_game->cells[cols * k + j] == cur_game->cells[cols * (k + 1) + j]) {
                        // Merge the cells
                        cur_game->cells[cols * k + j] *= 2;
                        cur_game->score += cur_game->cells[cols * k + j];
                        cur_game->cells[cols * (k + 1) + j] = -1;
                        merged = k; //set the var to cell that was merged
                        combined = 1; // A move was made
                        break; // Exit the inner loop
                    } else {
                        // No merge, exit the inner loop
                        break;
                    }
                }
            }
        }
    }
    
    return combined; // Return 1 if a move was made, 0 otherwise
}



int move_s(game *cur_game) {
    int combined = 0; // Initialize a check variable to 0
    int cols = cur_game->cols; // init var for columns
    int rows = cur_game->rows; // init var for rows
    
    // Loop through each of the columns
    for (int j = 0; j < cols; j++) {
        //var to check the merged cell
        int merged = rows;
        
        // Loop through rows, moving from the bottom to the top of the board
        for (int i = rows - 2; i >= 0; i--) {
            if (cur_game->cells[cols * i + j] != -1) //check to see if the cell is empty
            {
                for (int k = i + 1; k < merged; k++) {
                    if (cur_game->cells[cols * k + j] == -1) {
                        // Shift the cell down
                        cur_game->cells[cols * k + j] = cur_game->cells[cols * (k - 1) + j];
                        cur_game->cells[cols * (k - 1) + j] = -1;
                        combined = 1; //set combined to 1 if a valid move was made
                    } else if (cur_game->cells[cols * k + j] == cur_game->cells[cols * (k - 1) + j]) {
                        // Merge the cells
                        cur_game->cells[cols * k + j] *= 2;
                        cur_game->score += cur_game->cells[cols * k + j];
                        cur_game->cells[cols * (k - 1) + j] = -1;
                        merged = k; //set the var to cell that was merged
                        combined = 1; // A move was made
                        break; // Exit the inner loop
                    } else {
                        // No merge, exit the inner loop
                        break;
                    }
                }
            }
        }
    }
    
    return combined; // Return 1 if a move was made, 0 otherwise
}




int move_a(game *cur_game) {
    int combined = 0; // Initialize a check variable to 0
    int cols = cur_game->cols; // init var for columns
    int rows = cur_game->rows; // init var for rows
    
    // Loop through rows
    for (int i = 0; i < rows; i++) {
        // Initialize a variable to track the last merged cell
        int merged = -1;
        
        // Loop through columns, moving from left to right
        for (int j = 1; j < cols; j++) {
            if (cur_game->cells[cols * i + j] != -1) {
                for (int k = j - 1; k > merged; k--) {
                    if (cur_game->cells[cols * i + k] == -1) {
                        // Shift the cell to the left
                        cur_game->cells[cols * i + k] = cur_game->cells[cols * i + (k + 1)];
                        cur_game->cells[cols * i + (k + 1)] = -1;
                        combined = 1; // A move was made
                    } else if (cur_game->cells[cols * i + k] == cur_game->cells[cols * i + (k + 1)]) {
                        // Merge the cells
                        cur_game->cells[cols * i + k] *= 2;
                        cur_game->score += cur_game->cells[cols * i + k];
                        cur_game->cells[cols * i + (k + 1)] = -1;
                        merged = k; //set the var to cell that was merged
                        combined = 1; // A move was made
                        break; // Exit the inner loop
                    } else {
                        // No merge, exit the inner loop
                        break;
                    }
                }
            }
        }
    }
    
    return combined; // Return 1 if a move was made, 0 otherwise
}



int move_d(game *cur_game) {
    int combined = 0; // Initialize a check variable to 0
    int cols = cur_game->cols; // init var for columns
    int rows = cur_game->rows; // init var for rows
    
    // Loop through rows
    for (int i = 0; i < rows; i++) {
        // Initialize a variable to track the last merged cell
        int merged = cols;
        
        // Loop through columns, moving from right to left
        for (int j = cols - 2; j >= 0; j--) {
            if (cur_game->cells[cols * i + j] != -1) {
                // Non-empty cell found
                
                // Look for a merge condition
                for (int k = j + 1; k < merged; k++) {
                    if (cur_game->cells[cols * i + k] == -1) {
                        // Shift the cell to the right
                        cur_game->cells[cols * i + k] = cur_game->cells[cols * i + (k - 1)];
                        cur_game->cells[cols * i + (k - 1)] = -1;
                        combined = 1; // A move was made
                    } else if (cur_game->cells[cols * i + k] == cur_game->cells[cols * i + (k - 1)]) {
                        // Merge the cells
                        cur_game->cells[cols * i + k] *= 2;
                        cur_game->score += cur_game->cells[cols * i + k];
                        cur_game->cells[cols * i + (k - 1)] = -1;
                        merged = k; //set the var to cell that was merged
                        combined = 1; // A move was made
                        break; // Exit the inner loop
                    } else {
                        // No merge, exit the inner loop
                        break;
                    }
                }
            }
        }
    }
    
    return combined; // Return 1 if a move was made, 0 otherwise
}



int legal_move_check(game *cur_game) {
    // Check for empty spaces on the board
    for (int i = 0; i < cur_game->rows * cur_game->cols; i++) {
        if (cur_game->cells[i] == 0) {
            return 1;  // There is at least one empty space, so legal moves are possible
        }
    }

    // Check for adjacent tiles with the same value
    for (int row = 0; row < cur_game->rows; row++) {
        for (int col = 0; col < cur_game->cols; col++) {
            int current_value = cur_game->cells[row * cur_game->cols + col];
            
            // Check right neighbor
            if (col + 1 < cur_game->cols && cur_game->cells[row * cur_game->cols + col + 1] == current_value) {
                return 1;  // There are adjacent tiles with the same value, legal moves are possible
            }
            
            // Check lower neighbor
            if (row + 1 < cur_game->rows && cur_game->cells[(row + 1) * cur_game->cols + col] == current_value) {
                return 1;  // There are adjacent tiles with the same value, legal moves are possible
            }
        }
    }

    // If no empty spaces or adjacent tiles with the same value are found, no legal moves are possible
    return 0;
}



/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
