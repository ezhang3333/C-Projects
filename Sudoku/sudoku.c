#include "sudoku.h"

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int x = 0;x < 9;x++) //for loop to traverse to the ith row of an array
  {
    if(sudoku[i][x] == val) //check if any value is equal to the value in the ith row
    {
      return 1; //return 1 if the value already exists in the row
    }
  }
  return 0; //return 0 if the value does not exist in the row
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int y = 0;y < 9;y++) //traverse through the values of the ith column on the sudoku board
  {
    if(sudoku[y][j] == val) //check if the val is equal to any of the values in the ith column
    {
      return 1; //return 1 if the value is in the ith column of the board
    }
  }
  
  return 0; //return 0 if the val does not exist in the ith column
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  //define variables x and y to correspond to the starting row and column
  //of the 3x3 zone passed as the parameter of the question
  int x = i/3; 
  x = x*3;
  int y = j/3;
  y = y*3;
  for(int a = x;a < x+3;a++) //traverse throuh the rows of the 3x3 zone
  {
    for(int b = y;b < y+3;b++) //traverse through the columns of the 3x3 zone
    {
      if(sudoku[a][b] == val) //check if the values in the 3x3 zone equals the val
      {
        return 1; //return 1 if the val exists in the zone
      }
    }
  }
  
  return 0; //return 0 if value does not exist
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val, i, sudoku) == 1) //check if the val exists in the ith row
  {
    return 0;
  }
  else if(is_val_in_col(val, j, sudoku) == 1) //check if the val exists in the jth column
  {
    return 0;
  }
  else if(is_val_in_3x3_zone(val,i, j, sudoku) == 1) //check if the val exists in the 3x3 zone
  {
    return 0;
  }
  return 1;

  // END TODO
}
/* function made to check whether all the entries in the sudoku are already assigned
the function takes in the parameter of the sudoku board and returns 0 if all the numbers are 
not assigned yet and returns 1 if they have been assigned
*/

int all_assigned(int sudoku[9][9])
{
    int i,j; //init integers i and j
    for(i = 0;i < 9;i++) //traverse through the rows of the board
    {
      for(j = 0;j <9;j++) //traverse through the columns of the board
      {
        if(sudoku[i][j] == 0) //check if the values and the specific index equals 0
        {
          return 0; //return 0
        }
      }
    }
    return 1; //return 1
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {


  // BEG TODO.
  int i,j;
  int a,b;
  if(all_assigned(sudoku) == 1) //calls all_assigned function to check whether all of the spaces on the board have already been assigned
  {
    return 1;
  }
  else
  {
    for(i = 0;i < 9;i++) //travers through the rows of the board
    {
      for(j = 0;j <9;j++) //traverse through the columns of the board
      {
        if(sudoku[i][j] == 0)
        {
          a = i; //assigned the index without assigned numbers to a and b
          b = j;
        }
      }
    }
  }
  for(int num = 1;num <= 9;num++) //for loop through all of the possible values for the board
  {
    if(is_val_valid(num, a, b, sudoku) == 1) //function call to check whether the num works as the specific index on the board
    {
      sudoku[a][b] = num; //set the sudoku index to the num
      if(solve_sudoku(sudoku) == 1) //check if the board is fully filled out
      {
        return 1;
      }
    }
    sudoku[a][b] = 0; //set the index to zero for value that doesn't work

  }
  

  return 0;
  // END TODO.
}


// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





